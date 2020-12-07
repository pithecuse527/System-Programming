//
//  main.c
//  Assignment four for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 07/12/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  print the random number with N threads (N is given by a user)
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_ARR_SIZE 50
#define MAX_PTHREAD_NUM 10
#define RAND_UPPER 10
#define RAND_LOWER 5

void *thr_fn(void *arg);
int *cursor;    // array runner
                // not sure why I have to use this for global
                // maybe bacuse it would be much easier accessing to random number array?

int main(int argc, char *argv[])
{
	int err, i;							           // err and index
	int n_thread = atoi(argv[1]);		   // the number of threads
  int size_of_arr = atoi(argv[2]);   // the size of array
  int *arr;                          // the array consisted of random numbers
  pthread_t *tid;		                 // using thread with the number of n_thread
  void **tret;							         // return val. from a thread

  // //input check
  if(n_thread > MAX_PTHREAD_NUM || n_thread < 1 || size_of_arr > MAX_ARR_SIZE || size_of_arr < n_thread)
  {
    fprintf(stderr, "usage: ./main [the number of threads (1 ~ %d)] [the size of array (%d ~ %d)]\n", MAX_PTHREAD_NUM, n_thread, MAX_ARR_SIZE);
    fprintf(stderr, "array size must be equal or bigger than the number of threads!\n");
    return -1;
  }

  // arr malloc and place the random integer (extra memory for END indicator)
  arr = malloc((size_of_arr+1) * sizeof(int));
  for(i=0; i<size_of_arr; i++)
  {
    arr[i] = rand() % (RAND_UPPER - RAND_LOWER + 1) + RAND_LOWER;
    fprintf(stdout, "%d ", arr[i]);
  }
  fprintf(stdout, "\n\n");
  arr[++i] = NULL;    // THIS IS THE END

  cursor = arr;       // cursor starts from arr[0]
  tid = malloc(n_thread * sizeof(pthread_t));   // tid malloc and create threads
  for(i=0; i<n_thread; i++)
  {
    pthread_create(&tid[i], NULL, thr_fn, (void*)(i+1));
  }

  // main function should wait while every threads are alive
  for(i=0; i<n_thread; i++)
  {
    err = pthread_join(tid[i], NULL);
    if(err != 0)
		{
			fprintf(stderr, "join error on thread %d\n", i);
			return -1;
		}
  }

	return 0;
}

void *thr_fn(void *arg)
{
  pthread_t tid = pthread_self();
  int sleep_time;

  // while the cursor points something
  while(*cursor)
  {
    sleep_time = *cursor;   // save the sleeping time
    cursor++;               // while the thread sleep, cursor should move forward for the other threads
    sleep(sleep_time);
    fprintf(stdout, "(0x%x) - element[%d] : %d\n", (unsigned int)tid, cursor, sleep_time);
  }

  pthread_exit(0);
}
