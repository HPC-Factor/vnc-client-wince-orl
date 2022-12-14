//				Package : omnithread
// omnithread.h			Created : 7/94 tjr
//
//    Copyright (C) 1994,1995,1996, 1997 Olivetti & Oracle Research Laboratory
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
// Interface to OMNI thread abstraction.
//
// This file declares classes for threads and synchronisation objects
// (mutexes, condition variables and counting semaphores).
//
// Wherever a seemingly arbitrary choice has had to be made as to the interface
// provided, the intention here has been to be as POSIX-like as possible.  This
// is why there is no semaphore timed wait, for example.
//
#pragma once
#ifndef __omnithread_h_
#define __omnithread_h_

#ifndef NULL
#define NULL (void*)0
#endif

class omni_mutex;
// Windows CE does not support semaphores, so this is a cut-down version
// class omni_condition;
// class omni_semaphore;
class omni_thread;

//
// OMNI_THREAD_EXPOSE can be defined as public or protected to expose the
// implementation class - this may be useful for debugging.  Hopefully this
// won't change the underlying structure which the compiler generates so that
// this can work without recompiling the library.
//

#ifndef OMNI_THREAD_EXPOSE
#define OMNI_THREAD_EXPOSE private
#endif

// An exception for use with SEH in CE
#define OMNI_EXC_THREAD_FATAL       0xE0000020
#define OMNI_EXC_THREAD_INVALID     0xE0000021

//
// Include implementation-specific header file.
//
#include "ce.h"

#define _OMNITHREAD_NTDLL_

//
// This exception is thrown in the event of a fatal error.
//

class _OMNITHREAD_NTDLL_ omni_thread_fatal {
public:
    int error;
    omni_thread_fatal(int e = 0) : error(e) {}
};


//
// This exception is thrown when an operation is invoked with invalid
// arguments.
//

class _OMNITHREAD_NTDLL_ omni_thread_invalid {};


///////////////////////////////////////////////////////////////////////////
//
// Mutex
//
///////////////////////////////////////////////////////////////////////////

class _OMNITHREAD_NTDLL_ omni_mutex {

public:
    omni_mutex(void);
    ~omni_mutex(void);

    void lock(void);
    void unlock(void);
    void acquire(void) { lock(); }
    void release(void) { unlock(); }
	// the names lock and unlock are preferred over acquire and release
	// since we are attempting to be as POSIX-like as possible.

    friend class omni_condition;

private:
    // dummy copy constructor and operator= to prevent copying
    omni_mutex(const omni_mutex&);
    omni_mutex& operator=(const omni_mutex&);

OMNI_THREAD_EXPOSE:
    OMNI_MUTEX_IMPLEMENTATION
};

//
// As an alternative to:
// {
//   mutex.lock();
//   .....
//   mutex.unlock();
// }
//
// you can use a single instance of the omni_mutex_lock class:
//
// {
//   omni_mutex_lock l(mutex);
//   ....
// }
//
// This has the advantage that mutex.unlock() will be called automatically
// when an exception is thrown.
//

class _OMNITHREAD_NTDLL_ omni_mutex_lock {
    omni_mutex& mutex;
public:
    omni_mutex_lock(omni_mutex& m) : mutex(m) { mutex.lock(); }
    ~omni_mutex_lock(void) { mutex.unlock(); }
};


///////////////////////////////////////////////////////////////////////////
//
// Thread
//
///////////////////////////////////////////////////////////////////////////

class _OMNITHREAD_NTDLL_ omni_thread {

public:

    enum priority_t {
	PRIORITY_LOW,
	PRIORITY_NORMAL,
	PRIORITY_HIGH
    };

    enum state_t {
	STATE_NEW,		// thread object exists but thread hasn't
				// started yet.
	STATE_RUNNING,		// thread is running.
	STATE_TERMINATED	// thread has terminated but storage has not
				// been reclaimed (i.e. waiting to be joined).
    };

    //
    // Constructors set up the thread object but the thread won't start until
    // start() is called. The create method can be used to construct and start
    // a thread in a single call.
    //

    omni_thread(void (*fn)(void*), void* arg = NULL,
		priority_t pri = PRIORITY_NORMAL);
    omni_thread(void* (*fn)(void*), void* arg = NULL,
		priority_t pri = PRIORITY_NORMAL);
	// these constructors create a thread which will run the given function
	// when start() is called.  The thread will be detached if given a
	// function with void return type, undetached if given a function
	// returning void*. If a thread is detached, storage for the thread is
	// reclaimed automatically on termination. Only an undetached thread
	// can be joined.

    void start(void);
	// start() causes a thread created with one of the constructors to
	// start executing the appropriate function.

protected:

    omni_thread(void* arg = NULL, priority_t pri = PRIORITY_NORMAL);
	// this constructor is used in a derived class.  The thread will
	// execute the run() or run_undetached() member functions depending on
	// whether start() or start_undetached() is called respectively.

    void start_undetached(void);
	// can be used with the above constructor in a derived class to cause
	// the thread to be undetached.  In this case the thread executes the
	// run_undetached member function.

    virtual ~omni_thread(void);
	// destructor cannot be called by user (except via a derived class).
	// Use exit() or cancel() instead. This also means a thread object must
	// be allocated with new - it cannot be statically or automatically
	// allocated. The destructor of a class that inherits from omni_thread
	// shouldn't be public either (otherwise the thread object can be
	// destroyed while the underlying thread is still running).

public:

    void join(void**);
	// join causes the calling thread to wait for another's completion,
	// putting the return value in the variable of type void* whose address
	// is given (unless passed a null pointer). Only undetached threads
	// may be joined. Storage for the thread will be reclaimed.

    void set_priority(priority_t);
	// set the priority of the thread.

    static omni_thread* create(void (*fn)(void*), void* arg = NULL,
			       priority_t pri = PRIORITY_NORMAL);
    static omni_thread* create(void* (*fn)(void*), void* arg = NULL,
			       priority_t pri = PRIORITY_NORMAL);
	// create spawns a new thread executing the given function with the
	// given argument at the given priority. Returns a pointer to the
	// thread object. It simply constructs a new thread object then calls
	// start.

    static void exit(void* return_value = NULL);
	// causes the calling thread to terminate.

    static omni_thread* self(void);
	// returns the calling thread's omni_thread object.
	// If the calling thread is not the main thread and
	// is not created using this library, returns 0.

    static void yield(void);
	// allows another thread to run.

    static void sleep(unsigned long secs, unsigned long nanosecs = 0);
	// sleeps for the given time.

    static void get_time(unsigned long* abs_sec, unsigned long* abs_nsec,
			 unsigned long rel_sec = 0, unsigned long rel_nsec=0);
	// calculates an absolute time in seconds and nanoseconds, suitable for
	// use in timed_waits on condition variables, which is the current time
	// plus the given relative offset.

private:

    virtual void run(void* arg) {}
    virtual void* run_undetached(void* arg) { return NULL; }
	// can be overridden in a derived class.  When constructed using the
	// the constructor omni_thread(void*, priority_t), these functions are
	// called by start() and start_undetached() respectively.

    void common_constructor(void* arg, priority_t pri, int det);
	// implements the common parts of the constructors.

    omni_mutex mutex;
	// used to protect any members which can change after construction,
	// i.e. the following 2 members:

    state_t _state;
    priority_t _priority;

    static omni_mutex* next_id_mutex;
    static int next_id;
    int _id;

    void (*fn_void)(void*);
    void* (*fn_ret)(void*);
    void* thread_arg;
    int detached;

public:

    priority_t priority(void) {

	// return this thread's priority.

	omni_mutex_lock l(mutex);
	return _priority;
    }

    state_t state(void) {

	// return thread state (invalid, new, running or terminated).

	omni_mutex_lock l(mutex);
	return _state;
    }

    int id(void) { return _id; }
	// return unique thread id within the current process.


    // This class plus the instance of it declared below allows us to execute
    // some initialisation code before main() is called.

    class _OMNITHREAD_NTDLL_ init_t {
	static int count;
    public:
	init_t(void);
    };

    friend class init_t;

OMNI_THREAD_EXPOSE:
    OMNI_THREAD_IMPLEMENTATION
};

// This doesn't seem to get called at least under the emulator
// Perhaps the compiler is broken?
// static omni_thread::init_t omni_thread_init;

#endif
