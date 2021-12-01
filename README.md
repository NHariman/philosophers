# philosophers
Codam's Philosophers project without the bonuses

This project is about multithreading in C.
https://www.geeksforgeeks.org/multithreading-c-2/
https://www.thegeekstuff.com/2012/05/c-mutex-examples/ 
https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/

# Introduction
Threads are also called lightweight processes. However unlike processes, they are not independent from one another.
Each thread shares their code section, data section and OS resources (open files and signals) with other threads.
Each thread DOES have their own unique program counter (PC), a register set and a stack space.

### The use of multithreading
Multithreading is useful as it improves application speed through parallel processing. ie. tabs in a browser, or threads for processing text, input, etc.

# The program

## Introduction
The point of the project is to understand how to use multithreading and mutex locks using the dining philosophers problem as example.
Each philosopher is represented by a thread and each fork by a mutex lock. Each philosopher needs two forks to start eating. A single philosopher will always starve as they cannot grab more than one fork.
After a philosopher is able to grab a fork it eats for x ms as specified by the user. After eating it drops the forks to allow the philosophers next to them to start eating.

## Arguments needed for the Philo program:
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat

## Remarks about the project
The project is heavily reliant on the system's hardware, even between imacs there can be differences in how it performs. Whatsmore, even just the type of terminal used can impact performance. For example, VSC's terminal runs slower than iterm, which runs slower than Alacrity. This should be taken into account when checking for sudden deaths that aren't intended or with very tight values ie.
`2 201 100 100` or `3 180 60 60`

When two philosophers go for the same fork at the same time they risk deadlocking, which leads to death as neither philosopher is able to grab the fork. In order to prevent this, staggering when a philosopher is allowed to grab a fork can be used to avoid grabbing at the same time. This can be done by dividing philosophers up into priority groups and staggering the time until they grab a fork with less than a ms. 3 Groups have been defined for this project, a high priority/first priority, second priority that sleeps for a short while before trying to grab a fork and third priority which sleeps a little longer before grabbing a fork.

The amount of mutex locks and the amount of code between the lock and unlock also plays a role in how fast your program is able to go. Locking and unlocking at the right time, or unlocking asap after locking can improve the speed too.

When it comes to thread racing, some races cannot be avoided without risking a slower program so some thought has been put into which data races are deemed "irrelevant". Mostly the races that occur when only a value is being checked but not changed.

In order to comply with the must report death within 10ms of the death occuring, a second thread per philosopher is activated that tracks if a philosopher should die. This will also stop running if a philosopher has eaten enough.

# Function explanations

## Usable external functions:
- memset - fill memory with a constant byte
`void *memset(void *s, int c, size_t n);`
- printf - print out arguments
- malloc
- free
- write
- usleep - suspends execution for microsecond intervals.
`int usleep(useconds_t usec);`
- gettimeofday - gets local time
`int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);`

## About usleep
```c
       int usleep(useconds_t usec);
```
The usleep() function suspends execution of the calling thread for (at least) usec microseconds.  The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.

Usleep can be very inaccurate as it's official definition is it will sleep for AT LEAST the amount of micro seconds given.
In order to make a more accurate usleep one will have to alter it to compare the time passed to actual time and sleep in microseconds until the appropriate time is reached.
The longer the usleep the more inaccurate it may become.

## the pthread functions
All these functions compile and link with `-pthread``

### creating a thread
- pthread_create ( https://man7.org/linux/man-pages/man3/pthread_create.3.html )
```c
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
```

### detach vs join
Either `pthread_join` or `pthread_detach` should be called for each created thread so the system can release the resources after thread termination.

- pthread_detach ( https://man7.org/linux/man-pages/man3/pthread_detach.3.html ),
```c
int pthread_detach(pthread_t thread);
```
marks the thread identified as detached. When a detached thread terminates its resources are automatically relseased back into the system without the need for another thread to join with the terminated thread.
A detached thread cannot be joined or be made joinable again.
A detached thread does not prevent the thread from being terminated, it merely determines the behaviour of the system when the thread terminates.

- pthread_join ( https://man7.org/linux/man-pages/man3/pthread_join.3.html ),
```c
int pthread_join(pthread_t thread, void **retval);
```
pthread_join is like the `wait()`function when creating processes. It waits for a thread specified by `thread`to terminate. If the thread has already been terminated, it will immediately return. After a succesful pthread_join call the thread is guaranteed terminated and the caller may choose what to do with cleanup after termination. 

The thread called in this function *must* be joinable.

the `retval` variable returns the return value (exit status) of the thread.

## Mutex

Much like malloc and free, init and destroy go hand in hand when it comes to using mutex locks.
A Mutex lock must always be initiated before using and destroyed after it's done being used.
- pthread_mutex_init, initialises mutex ( https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html )
```c
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
           const pthread_mutexattr_t *restrict attr);
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```
- pthread_mutex_destroy, destroys mutex ( https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html )
```c
      int pthread_mutex_destroy(pthread_mutex_t *mutex);
       int pthread_mutex_init(pthread_mutex_t *restrict mutex,
           const pthread_mutexattr_t *restrict attr);
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

Locking and unlocking mutexes allows threads that run at the same time to access the same variable without scrambling it
When a mutex locks, only that particular thread can access the data contained between the lock and the unlock mutex function
for example, if you have a thread that increments a variable first it has to lock the variable so not all threads try to change the variable at the same time.
- pthread_mutex_lock, (https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html ) 
```c
       int pthread_mutex_lock(pthread_mutex_t *mutex);
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
       int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
- pthread_mutex_unlock, (https://linux.die.net/man/3/pthread_mutex_unlock)
```c
       int pthread_mutex_lock(pthread_mutex_t *mutex);
       int pthread_mutex_trylock(pthread_mutex_t *mutex);
       int pthread_mutex_unlock(pthread_mutex_t *mutex); 
```