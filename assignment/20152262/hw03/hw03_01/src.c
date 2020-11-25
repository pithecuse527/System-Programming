#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t childs[15];
int i;

void sig_handler(int signo);
int main()
{
  i = 0;
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
          fprintf(stderr, "execl error on SIGTSTP\n");
          exit(-1);
        }
      }
      else childs[i++] = pid;
      break;
    case SIGUSR1:
      for(j=0;j<i;j++)
      {
        if(kill(childs[j], SIGUSR1) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR1\n");
          exit(-1);
        }
      }
      break;
    case SIGUSR2:
      for(j=0;j<i;j++)
      {
        if(kill(childs[j], SIGUSR2) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR2\n");
          exit(-1);
        }
      }
      i = 0;
      break;
    default:
      fprintf(stderr, "unknown signal...\n");
      exit(-1);
  }
  sleep(3);

}
