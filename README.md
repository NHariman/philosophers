# philosophers
Codam's Philosophers project without the bonuses

This project is about multithreading in C.
https://www.geeksforgeeks.org/multithreading-c-2/

##Introduction
Threads are also called lightweight processes. However unlike processes, they are not independent from one another.
Each thread shares their code section, data section and OS resources (open files and signals) with other threads.
Each thread DOES have their own unique program counter (PC), a register set and a stack space.

###The use of multithreading
Multithreading is useful as it improves application speed through parallel processing. ie. tabs in a browser, or threads for processing text, input, etc.

## Arguements needed for the Philo program:
- number_of_philosophers
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_times_each_philosopher_must_eat

##Usable external functions:
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

### the pthread functions
All these functions compile and link with `-pthread``

#### creating a thread
- pthread_create ( https://man7.org/linux/man-pages/man3/pthread_create.3.html )
```c
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
```

#### detach vs join
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

the `retval` variable returns the return value of the thread.



#### Mutex
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_unlock
