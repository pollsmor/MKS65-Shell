#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//Returns a list of arguments
char ** parse_args(char * line) {
  char ** output = malloc(5 * 8);
  char *curr = line;

  int i = 0;
  while (curr != NULL) {
    output[i] = strsep(&curr, " ");
    i++;
  }

  return output;
}

//Take in the list of arguments from parse_args
void exec_args(char ** parsed, int *status) {
  pid_t pid = fork();

  if (pid == 0) { //is the child
    execvp(parsed[0], parsed);
    exit(0);
  } else { //is the parent
    wait(status); //wait for child to exit first
    return;
  }
}

char ** semicolon_parse(char * line, int *commands) {
  char ** output = malloc(5 * 40);
  char *curr = line;

  int i = 0;
  while (curr != NULL) {
    output[i] = strsep(&curr, "; ");
    i++;
    *commands++;
  }

  return output;
}
