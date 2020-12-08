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

// element for a linked list
typedef struct element {
  int e_val;
  int e_index;
  struct element *e_next;
} element;

struct element* element_alloc(int v, int i);
void* thr_fn(void *arg);

element *cursor;          // the array consisted of random number elements
pthread_mutex_t locker;   // mutex locker for *arr

int main(int argc, char *argv[])
{
	int err, i;							           // err and index
	int n_thread = atoi(argv[1]);		   // the number of threads
  int size_of_arr = atoi(argv[2]);   // the size of array
  pthread_t *arr_tid;		             // thread array pointer
  int t_int;                         // temp integer to make a random number
  element *arr_head;                 // element linked list head pointer

  //input check
  if(n_thread > MAX_PTHREAD_NUM || n_thread < 1 || size_of_arr > MAX_ARR_SIZE || size_of_arr < n_thread)
  {
    fprintf(stderr, "usage: ./main [the number of threads (1 ~ %d)] [the size of array (%d ~ %d)]\n", MAX_PTHREAD_NUM, n_thread, MAX_ARR_SIZE);
    fprintf(stderr, "array size must be equal or bigger than the number of threads!\n");
    return -1;
  }

  // arr_head and cursor ready
  arr_head = element_alloc(0, 0);
  cursor = arr_head;

  // mutex locker ready
  pthread_mutex_init(&locker, NULL);

  // elements are linked as a linked list
  for(i=0; i<size_of_arr; i++)
  {
    t_int = rand() % (RAND_UPPER - RAND_LOWER + 1) + RAND_LOWER;    // random number ready
    cursor -> e_next = element_alloc(t_int, i+1);   // malloc next element with the given rand number and the index
    cursor = cursor -> e_next;                      // cursor goes forward
    fprintf(stdout, "%d ", cursor -> e_val);           // print the random numbers
  }
  fprintf(stdout, "\n\n");

  cursor = arr_head -> e_next;    // relocate the cursor to first element
  arr_tid = malloc(n_thread * sizeof(pthread_t));   // malloc for thread array

  // thread create
  for(i=0; i<n_thread; i++)
  {
    err = pthread_create(&arr_tid[i], NULL, thr_fn, NULL);
    if(err != 0)
    {
      fprintf(stderr, "error on thread create %d\n", i);
    }
  }

  // main function should wait while every threads are alive
  for(i=0; i<n_thread; i++)
  {
    err = pthread_join(arr_tid[i], NULL);
    if(err != 0)
    {
      fprintf(stderr, "join error on thread %d\n", i);
      return -1;
    }
  }

  // mem. free
  cursor = arr_head -> e_next;
  while(cursor)
  {
    arr_head = cursor;
    cursor = cursor -> e_next;
    free(arr_head);
  }

	return 0;
}

struct element* element_alloc(int v, int i)
{
  struct element *ep;
  if ((ep = malloc(sizeof(element))))
  {
    ep -> e_val = v;
    ep -> e_index = i;
    ep -> e_next = NULL;
  }
  else
  {
    fprintf(stderr, "malloc failed!\n");
    return NULL;
  }
  return ep;
}

void* thr_fn(void *arg)
{
  pthread_t tid = pthread_self();     // thread id
  int t_sleep;      // time for sleep
  int i_element;   // index of element

  while(cursor)
  {
    pthread_mutex_lock(&locker);
    t_sleep = cursor -> e_val;
    i_element = cursor -> e_index;
    cursor = cursor -> e_next;
    pthread_mutex_unlock(&locker);
    sleep(t_sleep);
    fprintf(stdout, "%x - element[%d] : %d\n", (unsigned int)tid, i_element, t_sleep);
  }

  pthread_exit(0);
}
