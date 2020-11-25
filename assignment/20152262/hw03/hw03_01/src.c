#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void sig_handler(int signo);

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
  exit(0);
}

void sig_handler(int signo)
{
  pid_t pid;
  if((pid=fork())<0) fprintf(stderr, "fork error");
  else if(pid == 0)
  {
    switch(signo)
    {
      case SIGINT:
        if(execl("./sig", "sig", "sigint", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGINT\n");
          exit(-1);
        }
        printf("!!%d!!\n", signo);
        break;
      case SIGTSTP:
        if(execl("./sig", "sig", "sigstp", (char *)0) < 0)
        {
          fprintf(stderr, "execl error on SIGINT\n");
          exit(-1);
        }
        break;
      case SIGUSR1:
        if(kill(0, SIGUSR1) < 0)
        {
          fprintf(stderr, "kill error on SIGUSR1\n");
          exit(-1);
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
    // wait();
  }
  else sleep(3);
}
