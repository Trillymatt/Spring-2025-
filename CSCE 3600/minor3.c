/* minor3.c - producer-consumer with condition variables
 * Author: Matthew Norman
 * Course: CSCE 3600
 * Description: Efficient producer-consumer program using mutexes and condition variables
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NITEMS 10 // number of items in shared buffer

// Shared variables
char shared_buffer[NITEMS]; // echo buffer
int shared_count = 0;       // item count
unsigned int prod_index = 0; // producer index
unsigned int cons_index = 0; // consumer index

// Mutex and condition variables
pthread_mutex_t mutex;
pthread_cond_t cond_not_full;
pthread_cond_t cond_not_empty;

// Function prototypes
void *producer(void *arg);
void *consumer(void *arg);

int main() {
    pthread_t prod_tid, cons_tid1, cons_tid2;

    // Initialize synchronization primitives
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_not_full, NULL);
    pthread_cond_init(&cond_not_empty, NULL);

    // Create threads
    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid1, NULL, consumer, NULL);
    pthread_create(&cons_tid2, NULL, consumer, NULL);

    // Join threads
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid1, NULL);
    pthread_join(cons_tid2, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_not_full);
    pthread_cond_destroy(&cond_not_empty);

    return 0;
}

// Producer function
void *producer(void *arg) {
    char key;
    printf("Enter text for producer to read and consumer to print (Ctrl-C to exit).\n");

    while (1) {
        scanf("%c", &key);

        pthread_mutex_lock(&mutex);

        // Wait while buffer is full
        while (shared_count == NITEMS) {
            pthread_cond_wait(&cond_not_full, &mutex);
        }

        // Add item to buffer
        shared_buffer[prod_index] = key;
        shared_count++;

        prod_index = (prod_index + 1) % NITEMS;

        // Signal consumers
        pthread_cond_signal(&cond_not_empty);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    char key;
    long unsigned int id = (long unsigned int)pthread_self();

    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait while buffer is empty
        while (shared_count == 0) {
            pthread_cond_wait(&cond_not_empty, &mutex);
        }

        // Consume item from buffer
        key = shared_buffer[cons_index];
        shared_count--;

        cons_index = (cons_index + 1) % NITEMS;

        // Signal producer
        pthread_cond_signal(&cond_not_full);

        pthread_mutex_unlock(&mutex);

        // Output key outside the critical section
        printf("consumer %lu: %c\n", id, key);
    }

    return NULL;
}