/* benford_par1.c
 * Hannah Soria
 * 5/9/24
 * parallel version of counting the occurrences of each number being a leading digit. It is meant so 
 * determine whether or not a set of data follows Benford's law and begins by reading in binary data file.
 * Global Counter Array Protected by Single Mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include "my_timing.h"
#include <pthread.h>

#define NUM_THREADS 8 // define the 8 threads needed

// struct to pass data to threads
typedef struct ThreadInfo {
    int ID, beginIndex, endIndex; // thread id, the start index, and the end index
    double *data; // data that the thread will hold
}ThreadInfo;

// Global variables
int global_counts[10] = {0,0,0,0,0,0,0,0,0,0};
int N = 0;
double *data;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // global mutex initialized once


// Load data from a binary file that has an int and then
// a sequence of doubles. The value of the int should indicate
// the number of doubles in the sequence.
// Load the data into global variables N and data.
int loadData(char *filename) {
  FILE *fp;

  if(filename != NULL && strlen(filename))
    fp = fopen(filename, "r");
  else
    return -1;

  if (!fp)
    return -1;

  fread( &N, sizeof(int), 1, fp );
  data = (double*)malloc( sizeof(double)*N );
  fread( data, sizeof(double), N, fp );
  fclose( fp );
  return 1; // success
}

// Return the leading Digit of n.
int leadingDigit( double n ) {
    // This is not a particularly efficient approach.
    if (fabs(n) == 1.0)
        return 1;
    else if (fabs(n) == 0.0)
        return 0;
    else if (fabs(n) < 1.0) {
        // multiply it by 10 until you get a number that is at least 1.
        // Then chop off the fractional part. All that remains is the first digit.
        double tmp = fabs(n);
        while (tmp < 1.0) {
            tmp *= 10.0;
        }
        return (int)floor( tmp );
    }
    else {
        // Divide it by 10 until you get a number smaller than 10.
        // That number will be the first digit of the original number.
        long long unsigned in = (long long unsigned) floor(fabs(n));
        while (in > 9) {
            in /= 10;
        }
        return in;
    }
} // end leadingDigit

void *threadFunc(void *arg){
    ThreadInfo *thread_data = arg; // get thread info

    // iterate through the start to the end of each threads assigned portion
    for (int i = thread_data->beginIndex; i< thread_data->endIndex; i++){
        int d = leadingDigit(thread_data->data[i]); // execute leadingDigit on the thread data
        pthread_mutex_lock(&mutex); // lock the critical section (global_counts increment)
        global_counts[d]++; // increment global counts
        pthread_mutex_unlock(&mutex); // unlock the critical section (global_counts)
    }

    pthread_exit(NULL); // thread is finished and terminates
}

/* Main routine. */
int main(int argc, char* argv[]) 
{
    double t1, t2;
    int i;

    // Start the timer after we have loaded the data.
    t1 = get_time_sec();

    // Load the data
    int succ;
    // succ = loadData( "super_short.bin" );
    succ = loadData( "medium.bin" );
    // succ = loadData( "longer.bin" );
    if (!succ) { return -1; }

    pthread_t threads[NUM_THREADS]; // array of 8 threads
    ThreadInfo info[NUM_THREADS]; // get the thread info

    int thread_size = N / NUM_THREADS; // get the thread size of each thread
    int remainder = N % NUM_THREADS; // the remainder of n left from n/num_threads
    int beginIndex = 0; // first index is at 0


    for (int i=0; i< NUM_THREADS; i++){
        info[i].ID = i; // id is set the current i so it will be 0-7
        info[i].data = data; // set the data
        info[i].beginIndex = beginIndex; // set the begin 
        info[i].endIndex = beginIndex + thread_size + (i < remainder); // if i is less than the remainder 1 is added the threadsize otherwise 0 is added to threadsize, this distributes the remainder
        beginIndex = info[i].endIndex; // begin is the same as where the previous ended

        pthread_create(&threads[i], NULL, threadFunc, (void *)&info[i]); // create the threads
    }

    // joing threads 
    for (i = 0; i < NUM_THREADS; i++)  {
        pthread_join(threads[i], NULL);
    }

    // End the timer  
    t2 = get_time_sec();

    for (i = 1; i < 10; i++) {
        printf( "There are %d %d's\n", global_counts[i], i );
    }
            
    printf("It took %f seconds for the whole thing to run\n",t2-t1); 

    // We are responsible for calling loadData, so we are responsible
    // for freeing the data array.
    free( data );
    return 0;
    } // end main

