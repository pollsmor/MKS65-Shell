#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*
char * strip_leading_spaces(char *str) {
  char *output;
  int i = 0;
  while (str[i] == ' ') {
    i++;
  }

  strncpy(output, str + i, 8);
  return output;
}
*/

void strip_leading_spaces(char *str) {
  int i = 0;
  while (str[i] == ' ')
    i++;

  char curr = str[i];
  int j = 0;
  while (curr != '\0') {
    curr = str[i + j];
    str[j] = curr;
    j++;
  }

  str[j] = '\0';
}

//Returns a list of arguments
char ** parse_args(char *line) {
  char ** output = malloc(5 * 8);
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

  printf("what");
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
  char ** output = malloc(5 * 40);
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
