#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_PROCESS_AMOUNT 20

void sig_handler(int signo);
pid_t childs[MAX_PROCESS_AMOUNT];
int i;

int main()
{

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

  for (;;) pause();   // wait for my signal

}

void sig_handler(int signo)
{
  int j;
  pid_t pid;
  switch(signo)
  {
    case SIGINT:
      if((pid = fork()) < 0) fprintf(stderr, "fork error\n");
      else if(pid == 0)
      {
        if(execl("./sig", "sig", "sigint", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGINT\n");
          exit(-1);
        }
      }
      else childs[i++] = pid;
      break;
    case SIGTSTP:
      if((pid = fork()) < 0) fprintf(stderr, "fork error\n");
      else if(pid == 0)
      {
        if(execl("./sig", "sig", "sigstp", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGINT\n");
          exit(-1);
        }
      }
      else childs[i++] = pid;
      break;
    case SIGUSR1:
      for(j=0;j<=i;j++)
      {
        if(kill(childs[j], SIGUSR1) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR1\n");
          exit(-1);
        }
      }
      break;
    case SIGUSR2:
      if(kill(0, SIGUSR2) < 0)
      {
        fprintf(stderr, "kill error on SIGUSR2\n");
        exit(-1);
      }
      break;
    default:
      fprintf(stderr, "unknown signal...\n");
      exit(-1);
  }
  sleep(3);

}
