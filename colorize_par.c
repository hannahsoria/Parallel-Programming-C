/* colorize_par.c
 * Hannah Soria
 * 5/9/24
 * reads an image and applies a pixel-wise operator to it, uses parallelism to reduce the computation time
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include <pthread.h>
#include "my_timing.h"
#include <time.h>

#define NUM_THREADS 1

typedef struct{
	Pixel *src; // pointer to a pixel struct
	int beginIndex; // where the thread starts
	int endIndex; // where the thread ends
} PixelInfo;

// function that utilizes threading, 
void *threadFunc(void *arg){ // arg is a pointer to PixelInfo struct

	PixelInfo *arr=(PixelInfo *) arg; // pointer to array

	for (int i=arr->beginIndex;i<arr->endIndex;i++){ // iterate from the begin to end indices
		(arr->src)[i].r = (arr->src)[i].r > 128 ? (220+(arr->src)[i].r)/2 : (30+(arr->src)[i].r)/2; // modify the r pixels 
		(arr->src)[i].g = (arr->src)[i].g > 128 ? (220+(arr->src)[i].g)/2 : (30+(arr->src)[i].g)/2; // modify the g pixels
		(arr->src)[i].b = (arr->src)[i].b > 128 ? (220+(arr->src)[i].b)/2 : (30+(arr->src)[i].b)/2; // modify the b pixels
	}

	pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
	Pixel *src;
	int rows, cols, colors;
	int i;
	double t1, t2;

	// check usage
	if( argc < 2 ) {
		printf("Usage: %s <image filename>\n", argv[0]);
		exit(-1);
	}

	// read image and check for errors
	src = ppm_read( &rows, &cols, &colors, argv[1] );
	if( !src ) {
		printf("Unable to read file %s\n", argv[1]);
		exit(-1);
	}

	PixelInfo info[NUM_THREADS];
	pthread_t thread[NUM_THREADS];

	int thread_size = (rows*cols)/NUM_THREADS; // divide the pixels up to each of the threads
	for(int i=0; i<NUM_THREADS; i++){
		info[i].src = src; // info struct is set the the image that has been read in
		info[i].beginIndex = (thread_size/NUM_THREADS)*i; // calculate the start index
		info[i].endIndex = (thread_size/NUM_THREADS)*(i+1); // calculate end index (i+1) avoids an overlap
	}

    t1 = get_time_sec(); // get the time of start

	for (int i=0; i<NUM_THREADS; i++){ // loop through all of the threads
		pthread_create(&thread[i], NULL, threadFunc, &info[i]); // create the threads
	}

	for (int i=0; i<NUM_THREADS; i++){ // loop through all of the threads
		pthread_join(thread[i], NULL); // join the threads
	}

    t2 = get_time_sec(); // get the time of the end
	printf("It took %f seconds for the whole thing to run\n",t2-t1); 

	// write out the image
	ppm_write( src, rows, cols, colors, "bold.ppm" );

	free(src);
	return(0);
}

	
