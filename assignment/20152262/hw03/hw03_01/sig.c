#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char current_sig[20];
void sig_handler2(int signo);

int main(int argc, char *argv[])
{
  printf("%s\n", argv[1]);
  if(argc > 2)
  {
    fprintf(stderr, "too many arguments...");
    exit(-1);
  }

  if(signal(SIGUSR1, (void*)sig_handler2) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR1\n");
    exit(-1);
  }
  if(signal(SIGUSR1, (void*)sig_handler2) == SIG_ERR)
  {
    fprintf(stderr, "can't catch SIGUSR2\n");
    exit(-1);
  }

  if(strcmp(argv[1], "sigint") == 0)
  {
    strcpy(current_sig, "sigint");
    fprintf(stdout, "Start [%s] - %d", current_sig, (int)getpid());
  }
  else if(strcmp(argv[1], "sigtstp") == 0)
  {
    strcpy(current_sig, "sigtstp");
    fprintf(stdout, "Start [%s] - %d", current_sig, (int)getpid());
  }
  sleep(1);
  // for (;;) pause();   // wait for my signal

}

void sig_handler2(int signo)
{
  switch(signo)
  {
    case SIGUSR1:
      fprintf(stdout, "Running [%s] - %d", current_sig, (int)getpid());
      break;
    case SIGUSR2:
      fprintf(stdout, "Exit [%s] - %d", current_sig, (int)getpid());
      exit(0);
    default:
      fprintf(stdout, "unknown signal for sig_handler2\n");
      exit(-1);
  }
}
