//				Package : omnithread
// omnithread/nt.cc		Created : 6/95 tjr
//
//    Copyright (C) 1995, 1996, 1997 Olivetti & Oracle Research Laboratory
//
//    This file is part of the omnithread library
//
//    The omnithread library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
//    02111-1307, USA
//

//
// Implementation of OMNI thread abstraction for CE threads
// This is only partial - no support for condition variables or semaphores.
//

#include <stdlib.h>
#include "omnithreadce.h"

#define DB(x) // x 

static void get_time_now(unsigned long* abs_sec, unsigned long* abs_nsec);

DWORD exc_args[9];


///////////////////////////////////////////////////////////////////////////
//
// Mutex
//
///////////////////////////////////////////////////////////////////////////


omni_mutex::omni_mutex(void)
{
    InitializeCriticalSection(&crit);
}

omni_mutex::~omni_mutex(void)
{
    DeleteCriticalSection(&crit);
}

void
omni_mutex::lock(void)
{
    EnterCriticalSection(&crit);
}

void
omni_mutex::unlock(void)
{
    LeaveCriticalSection(&crit);
}





///////////////////////////////////////////////////////////////////////////
//
// Thread
//
///////////////////////////////////////////////////////////////////////////


//
// Static variables
//

int omni_thread::init_t::count = 0;

omni_mutex* omni_thread::next_id_mutex;
int omni_thread::next_id = 0;
static DWORD self_tls_index;

//
// Initialisation function (gets called before any user code).
//

omni_thread::init_t::init_t(void)
{
    if (count++ != 0)	// only do it once however many objects get created.
	return;

    DB(cerr << "omni_thread::init: NT implementation initialising\n");

    self_tls_index = TlsAlloc();

    if (self_tls_index == 0xffffffff) {
	    //throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }

    next_id_mutex = new omni_mutex;

    //
    // Create object for this (i.e. initial) thread.
    //

    omni_thread* t = new omni_thread;

    t->_state = STATE_RUNNING;

    /*
    if (!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(),
			 GetCurrentProcess(), &t->handle,
			 0, FALSE, DUPLICATE_SAME_ACCESS))
	throw omni_thread_fatal(GetLastError());
    */
    // On CE:
    t->handle = GetCurrentThread();

    t->nt_id = GetCurrentThreadId();

    DB(cerr << "initial thread " << t->id() << " NT thread id " << t->nt_id
       << endl);

    if (!TlsSetValue(self_tls_index, (LPVOID)t)) {
	    // throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }

    if (!SetThreadPriority(t->handle, nt_priority(PRIORITY_NORMAL)))
    {
        //throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }
}

//
// Wrapper for thread creation.
//

extern "C" unsigned
omni_thread_wrapper(LPVOID ptr)
{
    omni_thread* me = (omni_thread*)ptr;

    DB(cerr << "omni_thread_wrapper: thread " << me->id()
       << " started\n");

    if (!TlsSetValue(self_tls_index, (LPVOID)me)) {
	    //throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }

    //
    // Now invoke the thread function with the given argument.
    //

    if (me->fn_void != NULL) {
	(*me->fn_void)(me->thread_arg);
	omni_thread::exit();
    }

    if (me->fn_ret != NULL) {
	void* return_value = (*me->fn_ret)(me->thread_arg);
	omni_thread::exit(return_value);
    }

    if (me->detached) {
	me->run(me->thread_arg);
	omni_thread::exit();
    } else {
	void* return_value = me->run_undetached(me->thread_arg);
	omni_thread::exit(return_value);
    }

    // should never get here.

    return 0;
}


//
// Constructors for omni_thread - set up the thread object but don't
// start it running.
//

// construct a detached thread running a given function.

omni_thread::omni_thread(void (*fn)(void*), void* arg, priority_t pri)
{
    common_constructor(arg, pri, 1);
    fn_void = fn;
    fn_ret = NULL;
}

// construct an undetached thread running a given function.

omni_thread::omni_thread(void* (*fn)(void*), void* arg, priority_t pri)
{
    common_constructor(arg, pri, 0);
    fn_void = NULL;
    fn_ret = fn;
}

// construct a thread which will run either run() or run_undetached().

omni_thread::omni_thread(void* arg, priority_t pri)
{
    common_constructor(arg, pri, 1);
    fn_void = NULL;
    fn_ret = NULL;
}

// common part of all constructors.

void
omni_thread::common_constructor(void* arg, priority_t pri, int det)
{
    _state = STATE_NEW;
    _priority = pri;

    next_id_mutex->lock();
    _id = next_id++;
    next_id_mutex->unlock();

    thread_arg = arg;
    detached = det;	// may be altered in start_undetached()

    /*
    cond_semaphore = CreateSemaphore(NULL, 0, SEMAPHORE_MAX, NULL);

    if (cond_semaphore == NULL)
	throw omni_thread_fatal(GetLastError());
    */

    cond_next = cond_prev = NULL;
    cond_waiting = FALSE;

    handle = NULL;
}




//
// Destructor for omni_thread.
//

omni_thread::~omni_thread(void)
{
    DB(cerr << "destructor called for thread " << id() << endl);
    if ((handle !=NULL) && !CloseHandle(handle)) {
	    // throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }
}


//
// Start the thread
//

void
omni_thread::start(void)
{
    omni_mutex_lock l(mutex);

    if (_state != STATE_NEW) {
	    // throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }

    handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)omni_thread_wrapper,
			  (LPVOID)this, CREATE_SUSPENDED, &nt_id);

    
    if (handle == NULL) {
	    // throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }

    if (!SetThreadPriority(handle,  _priority)) {
	    // throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
    }

    if (ResumeThread(handle) == 0xffffffff) {
	// throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);

    }

    _state = STATE_RUNNING;
}


//
// Start a thread which will run the member function run_undetached().
//

void
omni_thread::start_undetached(void)
{
    if ((fn_void != NULL) || (fn_ret != NULL)) {
	 //   throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }

    detached = 0;
    start();
}


//
// join - simply check error conditions & call WaitForSingleObject.
//

void
omni_thread::join(void** status)
{
    mutex.lock();

    if ((_state != STATE_RUNNING) && (_state != STATE_TERMINATED)) {
        mutex.unlock();
        // throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }

    mutex.unlock();
    
    if (this == self()) {
        // throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }
    
    if (detached) {
        // throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }

    DB(cerr << "omni_thread::join: doing WaitForSingleObject\n");

    if (WaitForSingleObject(handle, INFINITE) != WAIT_OBJECT_0) {
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);
	    // throw omni_thread_fatal(GetLastError());
    }

    DB(cerr << "omni_thread::join: WaitForSingleObject succeeded\n");

    if (status)
      *status = return_val;

    delete this;
}


//
// Change this thread's priority.
//

void
omni_thread::set_priority(priority_t pri)
{
    omni_mutex_lock l(mutex);

    if (_state != STATE_RUNNING) {
	    // throw omni_thread_invalid();
        RaiseException(OMNI_EXC_THREAD_INVALID, 0, 0, 0);
    }

    _priority = pri;

    if (!SetThreadPriority(handle, nt_priority(pri))) {
	    // throw omni_thread_fatal(GetLastError());
        exc_args[0] = GetLastError();
        RaiseException(OMNI_EXC_THREAD_FATAL, 0, 1, exc_args);    }
}


//
// create - construct a new thread object and start it running.  Returns thread
// object if successful, null pointer if not.
//

// detached version

omni_thread*
omni_thread::create(void (*fn)(void*), void* arg, priority_t pri)
{
    omni_thread* t = new omni_thread(fn, arg, pri);
    t->start();
    return t;
}

// undetached version

omni_thread*
omni_thread::create(void* (*fn)(void*), void* arg, priority_t pri)
{
    omni_thread* t = new omni_thread(fn, arg, pri);
    t->start();
    return t;
}


//
// exit() _must_ lock the mutex even in the case of a detached thread.  This is
// because a thread may run to completion before the thread that created it has
// had a chance to get out of start().  By locking the mutex we ensure that the
// creating thread must have reached the end of start() before we delete the
// thread object.  Of course, once the call to start() returns, the user can
// still incorrectly refer to the thread object, but that's their problem.
//

void
omni_thread::exit(void* return_value)
{
    omni_thread* me = self();

    if (me)
      {
	me->mutex.lock();

	me->_state = STATE_TERMINATED;

	me->mutex.unlock();

	DB(cerr << "omni_thread::exit: thread " << me->id() << " detached "
	   << me->detached << " return value " << return_value << endl);

	if (me->detached) {
	  delete me;
	} else {
	  me->return_val = return_value;
	}
      }
    else
      {
	DB(cerr << "omni_thread::exit: called with a non-omnithread. Exit quietly." << endl);
      }
    ExitThread(0);
}


omni_thread*
omni_thread::self(void)
{
    LPVOID me;

    me = TlsGetValue(self_tls_index);

    if (me == NULL) {
      DB(cerr << "omni_thread::self: called with a non-ominthread. NULL is returned." << endl);
    }
    return (omni_thread*)me;
}


void
omni_thread::yield(void)
{
    Sleep(0);
}


#define MAX_SLEEP_SECONDS (DWORD)4294966	// (2**32-2)/1000

void
omni_thread::sleep(unsigned long secs, unsigned long nanosecs)
{
    if (secs <= MAX_SLEEP_SECONDS) {
	Sleep(secs * 1000 + nanosecs / 1000000);
	return;
    }

    DWORD no_of_max_sleeps = secs / MAX_SLEEP_SECONDS;

    for (DWORD i = 0; i < no_of_max_sleeps; i++)
	Sleep(MAX_SLEEP_SECONDS * 1000);

    Sleep((secs % MAX_SLEEP_SECONDS) * 1000 + nanosecs / 1000000);
}


void
omni_thread::get_time(unsigned long* abs_sec, unsigned long* abs_nsec,
		      unsigned long rel_sec, unsigned long rel_nsec)
{
    get_time_now(abs_sec, abs_nsec);
    *abs_nsec += rel_nsec;
    *abs_sec += rel_sec + *abs_nsec / 1000000000;
    *abs_nsec = *abs_nsec % 1000000000;
}


int
omni_thread::nt_priority(priority_t pri)
{
    switch (pri) {

    case PRIORITY_LOW:
	return THREAD_PRIORITY_LOWEST;

    case PRIORITY_NORMAL:
	return THREAD_PRIORITY_NORMAL;

    case PRIORITY_HIGH:
	return THREAD_PRIORITY_HIGHEST;
    }

    // throw omni_thread_invalid();
    return 0; /* keep msvc++ happy */
}


static void
get_time_now(unsigned long* abs_sec, unsigned long* abs_nsec)
{
    static int days_in_preceding_months[12]
	= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    static int days_in_preceding_months_leap[12]
	= { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

    SYSTEMTIME st;

    GetSystemTime(&st);
    *abs_nsec = st.wMilliseconds * 1000000;

    // this formula should work until 1st March 2100

    DWORD days = ((st.wYear - 1970) * 365 + (st.wYear - 1969) / 4
		  + ((st.wYear % 4)
		     ? days_in_preceding_months[st.wMonth - 1]
		     : days_in_preceding_months_leap[st.wMonth - 1])
		  + st.wDay - 1);

    *abs_sec = st.wSecond + 60 * (st.wMinute + 60 * (st.wHour + 24 * days));
}
