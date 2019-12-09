#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void strip_leading_spaces(char *str) {
  printf("str: %s \n", str);
  int i = 0; //find index of the first character that isn't whitepsace
  while (str[i] == ' ')
    i++;

  char curr = str[i];
  int j = 0;
  while (curr != '\0') {
    curr = str[i + j];
    str[j] = curr;
    j++;
  }
}

//Returns a list of arguments
char ** parse_args(char *line) {
  char ** output = malloc(100); //space to fit all arguments
  char *curr = line;
  strip_leading_spaces(line);

  int i = 0;
  while (curr != NULL) {
    output[i] = strsep(&curr, " ");
    i++;
  }

  return output;
}

//Take in the list of arguments from parse_args
void exec_args(char * line, int *exited, int *status) {
  char ** parsed = parse_args(line);
  if (strcmp(parsed[0], "exit") == 0) {
    *exited = 1; //keep track of whether while loop should exit
    return;
  }

  if (strcmp(parsed[0], "cd") == 0) {
    chdir(parsed[1]);
    return;
  }

  pid_t pid = fork();

  if (pid == 0) { //is the child
    execvp(parsed[0], parsed);
    exit(0);
  } else { //is the parent
    wait(status); //wait for child to exit first
    free(parsed);
    return;
  }
}

char ** semicolon_parse(char *line, int *num_commands) {
  char ** output = malloc(500);
  char *curr = line;

  while (curr != NULL) {
    output[*num_commands] = strsep(&curr, ";");
    (*num_commands)++;
  }

  return output;
}

void semicolon_exec(char *line, int *exited, int *status) {
  int num_commands = 0;
  char ** commands = semicolon_parse(line, &num_commands);

  for (int i = 0; i < num_commands; i++) {
    if (*exited == 1)
      return;

    exec_args(commands[i], exited, status);
  }

  free(commands);
}
