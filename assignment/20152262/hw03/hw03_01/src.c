//  
//  src.c
//  Assignment three for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 25/11/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  main source program which generates a signal
//  

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t childs[15];     // child process array
int i;                // current child process array index

void sig_handler(int signo);
int main()
{
  i = 0;    // starts from 0
  
  // add signals
  if(signal(SIGINT, (void*)sig_handler) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGINT\n");
    exit(-1);
  }
  if(signal(SIGTSTP, (void*)sig_handler) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGSTP\n");
    exit(-1);
  }
  
  if(signal(SIGUSR1, (void*)sig_handler) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR1\n");
    exit(-1);
  }
  
  if(signal(SIGUSR2, (void*)sig_handler) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR2\n");
    exit(-1);
  }

  for (;;)
    pause();   // wait for my signal
  
}

void sig_handler(int signo)
{
  int j;    // to send SIGUSR1 signal for every child
  pid_t pid;
  switch(signo)
  {
    case SIGINT:      // fork new child process
      if((pid = fork()) < 0) fprintf(stderr, "fork error\n");
      else if(pid == 0)
      {
        if(execl("./sig", "sig", "sigint", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGINT\n");
          exit(-1);
        }
      }
      else childs[i++] = pid;   // increase the child signal index
      break;
    case SIGTSTP:   // fork new child process
      if((pid = fork()) < 0) fprintf(stderr, "fork error\n");
      else if(pid == 0)
      {
        if(execl("./sig", "sig", "sigstp", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGTSTP\n");
          exit(-1);
        }
      }
      else childs[i++] = pid;  // increase the child signal index
      break;
    case SIGUSR1:
      for(j=0;j<i;j++)    // send this signal only to its child
      {
        if(kill(childs[j], SIGUSR1) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR1\n");
          exit(-1);
        }
      }
      break;
    case SIGUSR2:
      for(j=0;j<i;j++)   // send this signal only to its child
      {
        if(kill(childs[j], SIGUSR2) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR2\n");
          exit(-1);
        }
      }
      i = 0;    // as every child process terminated, reset
      break;
    default:
      fprintf(stderr, "unknown signal...\n");
      exit(-1);
  }
  sleep(3);   // give some time to each child process
}
