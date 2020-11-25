//  
//  sig.c
//  Assignment three for System Programming, UOU - 20152262
//  Created by Hong Geun Ji on 25/11/2020
//  VIM - Vi IMproved 8.0
//  Copyright © 2020 Hong Geun Ji. All rights reserved.
//
//  print some information based on the given signal
//  

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char current_sig[20];
void sig_handler2(int signo);

int main(int argc, char *argv[])
{
  if(argc > 2)
  {
    fprintf(stderr, "too many arguments...");
    exit(-1);
  }

  // print some information first
  strcpy(current_sig, argv[1]);
  fprintf(stdout, "\n");
  fprintf(stdout, "Start [%s] - %d", current_sig, (int)getpid());
  fprintf(stdout, "\n");

  if(signal(SIGUSR1, (void*)sig_handler2) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR1");
    exit(-1);
  }
  if(signal(SIGUSR2, (void*)sig_handler2) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR2");
    exit(-1);
  }

  for(;;) pause();   // wait for my signal

}

void sig_handler2(int signo)
{
  switch(signo)
  {
    case SIGUSR1:   // print every child process
      fprintf(stdout, "\n");
      fprintf(stdout, "Running [%s] - %d", current_sig, (int)getpid());
      fprintf(stdout, "\n");
      break;
    case SIGUSR2:   // exit every child process
      fprintf(stdout, "\n");
      fprintf(stdout, "Exit [%s] - %d", current_sig, (int)getpid());
      fprintf(stdout, "\n");
      exit(0);
    default:
      fprintf(stdout, "unknown signal for sig_handler2");
      exit(-1);
  }
}
