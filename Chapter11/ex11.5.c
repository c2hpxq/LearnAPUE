#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define NT 5

struct mybarrier {
    int n;
    pthread_mutex_t m;
    pthread_cond_t c;
};

int mybarrier_init(struct mybarrier *b, int count) {
    b->n = count;
    pthread_mutex_init(&b->m, NULL);
    pthread_cond_init(&b->c, NULL);
    return 0;
}

int mybarier_destroy(struct mybarrier *b) {
    return 0;
}

int mybarrier_wait(struct mybarrier *b) {
    pthread_mutex_lock(&b->m);
    if ((--b->n)==0) {
        pthread_cond_broadcast(&b->c);
        pthread_mutex_unlock(&b->m);
        // we can return PTHREAD_BARRIER_SERIAL_THREAD here
        return 1;
    }
    pthread_cond_wait(&b->c, &b->m);
    pthread_mutex_unlock(&b->m);
    printf("count left: %d\n", b->n);
    return 0;
}

struct mybarrier b;

void *thread_fn(void *arg) {
    int t = ((int) arg) +1;
    sleep(t);
    printf("sleep for %d, now awake&barrier...\n", t);
    mybarrier_wait(&b);
    printf("we all arrive here!\n");
    pthread_exit(0);
}

int main() {
    pthread_t tid[NT];
    mybarrier_init(&b, NT+1);
    for (int i = 0; i < NT; ++i)
        pthread_create(tid+i, NULL, thread_fn, (void *) i);
    mybarrier_wait(&b);
    printf("main thread exit\n");
    mybarier_destroy(&b);

    return 0;
}