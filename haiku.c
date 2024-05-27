/* haiku.c
 * Hannah Soria
 * 5/9/24
 * uses threads and mutexes to print out a haiku about mutexes
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include "my_timing.h"
#include <pthread.h>

#define NUM_THREADS 3 // define the 8 threads needed

// struct to pass data to threads
typedef struct ThreadInfo {
    int ID, beginIndex, endIndex; // thread id, the start index, and the end index
    const char *data; // data that the thread will hold
}ThreadInfo;

const char *poem = "This poem needs one\nWhat is this magical thing\nA mutex of course!"; // poem 
int begins[] = {0, 20, 46}; // start values
int ends[] = {20, 46, 66}; // end values
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // global mutex initialized once

void *threadFunc(void *arg){ // function that handles the threads duties
    ThreadInfo *thread_data = (ThreadInfo *) arg; // get thread info 
    pthread_mutex_lock(&mutex);
    for (int i = thread_data->beginIndex; i< thread_data->endIndex; i++){ // iterate throught the section of the poem this thread has
        printf("%c", thread_data->data[i]); // print each character
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL); // thread is finished and terminate
}

int main(){
    pthread_t threads[NUM_THREADS]; // get the threads
    ThreadInfo info[NUM_THREADS]; // thread info

    for (int i=0; i<NUM_THREADS; i++){ // go through the number of threads
        info[i].ID = i; // set id
        info[i].beginIndex = begins[i]; // set begins
        info[i].endIndex = ends[i]; // set end
        info[i].data = poem; // set data

        pthread_create(&threads[i], NULL, threadFunc, (void *)&info[i]); // create the threads
    }

    for (int i=0; i<NUM_THREADS;i++){ // join the threads
        pthread_join(threads[i], NULL);
    }
    return 0;

}