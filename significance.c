#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void sigint(int signo) {
  int file = open("log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
  dprintf(file, "I'm %d and I must leave as I've gotten a SIGINT\n", getpid());
  close(file);
  printf("\n");
  exit(0);
}

static void sigusr1(int signo) {
  printf("my parent is %d\n", getppid());
}

int main() {
  signal(SIGINT, sigint);
  signal(SIGUSR1, sigusr1);
  while (1) {
    printf("hi I'm %d\n", getpid());
    sleep(1);
  }
}
