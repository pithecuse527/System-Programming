//
//  main.c
//  Assignment four for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 07/12/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  print some digits from 1 to given number by using therad
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_fn(void *arg);

int main(int argc, char *argv[])
{
	int err, i;							// err and index
	pthread_t tid1, tid2;		// using two threads
	void *tret;							// return val. from a thread
	int until = atoi(argv[1]);		// change the given number to int

	if(argc > 2)
	{
		fprintf(stderr, "usage: main [ the number of threads ]");
		return -1;
	}

	if(until % 2)		// if the given number is not a even number, add 1
	{
		until++;
		fprintf(stdout, "The given number is not a even, but I'll make it as even -> %d\n\n", until);
	}

	// loop until the index reaches the given number(argv)
	// join right away to print inorder
	for(i=1; i<until; i+=2)
	{
		// fprintf(stdout, "!%d!\n", i);
		err = pthread_create(&tid1, NULL, thr_fn, (void*)i);		// creat the thread1
		if(err != 0)		// shut this down when error detected
		{
			fprintf(stderr, "create error on thread %d\n", i);
			return -1;
		}
		err = pthread_join(tid1, &tret);
		if(err != 0)
		{
			fprintf(stderr, "join error on thread %d\n", i);
			return -1;
		}

		err = pthread_create(&tid2, NULL, thr_fn, (void*)(i+1));		// creat the thread2
		if(err != 0)		// shut this down when error detected
		{
			fprintf(stderr, "error on thread %d\n", i+1);
			return -1;
		}
		err = pthread_join(tid2, &tret);
		if(err != 0)
		{
			fprintf(stderr, "join error on thread %d\n", i+1);
			return -1;
		}
	}

	fprintf(stdout, "Complete all number\n");
	return 0;
}

void *thr_fn(void *arg)
{
	int num = (int)arg;		// number ready

	if(!(num % 2))				// if the given arg is even number,
	{
		fprintf(stdout, "even_thread : %d\n", num);
		pthread_exit(0);		// exit with 0 on even
	}
	fprintf(stdout, "odd_thread : %d\n", num);
	pthread_exit((void*)1);			// exit with 1 on odd
}
