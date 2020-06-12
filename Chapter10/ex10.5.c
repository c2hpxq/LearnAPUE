#include "apue.h"
#include <time.h>
#include <pthread.h>

typedef void timer_function(void *);

struct event {
    time_t t;
    timer_function *f;
};

#define CAPACITY 32

struct event_queue {
    int head;
    int size;
    struct event queue[CAPACITY];
    pthread_mutex_t m;
};

struct event_queue eq;

static int eqinit() {
    eq.head = 0;
    eq.size = 0;
    pthread_mutex_init(&eq.m, NULL);
    return 0;
}

static void allow_alarm() {
    sigset_t s;
    sigprocmask(0, NULL, &s);
    sigaddset(&s, SIGALRM);
    sigprocmask(SIG_SETMASK, &s, NULL);
}

static void disallow_alarm() {
    sigset_t s;
    sigprocmask(0, NULL, &s);
    sigdelset(&s, SIGALRM);
    sigprocmask(SIG_SETMASK, &s, NULL);
}

static struct event dequeue();

static void fire_expired_alarm() {
    while (eq.size) {
        int dt = eq.queue[eq.head].t - time(NULL);
        if (dt<=0) {
            dequeue().f(NULL);
        }
        else {
            alarm(dt);
            break;
        }
    }
}

static int enqueue(struct event e) {

    /* prevent race between enqueue & sig alarm handler */
    disallow_alarm();
    pthread_mutex_lock(&eq.m);
    if (eq.size==CAPACITY) {
        pthread_mutex_unlock(&eq.m);
        return -1;
    }
    int next = (eq.head+eq.size)%CAPACITY;
    int i;
    for (i = eq.head; i != next; i = (i+1)%CAPACITY)
        if (eq.queue[i].t>e.t) {
            eq.queue[i] = e;
            int j;
            for (j = i; j != next; j = (j+1)%CAPACITY)
                eq.queue[i+1] = eq.queue[i];
            break;
        }
    if (i==next)
        eq.queue[i] = e;
    eq.size++;
    fire_expired_alarm();
    pthread_mutex_unlock(&eq.m);
    allow_alarm();
    return 0;
}

static struct event dequeue() {
    struct event e;
    pthread_mutex_lock(&eq.m);
    e = eq.queue[eq.head];
    eq.head = (eq.head+1)%CAPACITY;
    eq.size--;
    pthread_mutex_unlock(&eq.m);
    return e;
}

static void timer_fire(int signo) {
    struct event e = dequeue();
    time_t t;
    time(&t);
    printf("current time: %ld\n", t);
    printf("expected time: %ld\n", e.t);
    e.f(NULL);
    fire_expired_alarm();

}

int timer_init() {
    eqinit();
    allow_alarm();
    signal(SIGALRM, timer_fire);
    return 0;
}

int timer_set(int t, timer_function* f) {
    struct event e;
    e.t = time(NULL)+t;
    e.f = f;
    if (enqueue(e)<0) {
        printf("timer queue full...\n");
        return -1;
    }
    return 0;
}

void hello(void *i) {
    static int ntriggered = 0;
    printf("hello %d\n", ++ntriggered);
}

int main() {
    timer_init();
    int i;
    for (i = 0; i <= CAPACITY; ++i)
        timer_set(5, hello);
    for (;;)
        pause();

    return 0;
}