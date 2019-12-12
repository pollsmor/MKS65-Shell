#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "redirect.h"
#include "pipes.h"

void strip_leading_spaces(char *str) {
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

void strip_trailing_spaces(char *str) {
  int i = 0; //find index of where there are 2 space characters in a row
  while (i < (int)strlen(str)) {
    if (str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0')) {
      str[i] = '\0';
      return;
    }

    i++;
  }
}

//Returns a list of arguments
char ** parse_args(char *line, int *num_args) {
  char ** output = malloc(100); //space to fit all arguments
  strip_leading_spaces(line); //for example:                    ls
  strip_trailing_spaces(line); //for example: ls -al             <enter>
  char *curr = line;

  while (curr != NULL) {
    output[*num_args] = strsep(&curr, " ");
    (*num_args)++;
  }

  output[*num_args] = NULL;
  return output;
}

//Take in the list of arguments from parse_args
void exec_args(char * line, int *exited) {
  int num_args = 0;
  char lineCpy[300];
  strncpy(lineCpy, line, 300);
  char ** parsed = parse_args(line, &num_args);

  if (strcmp(parsed[0], "exit") == 0) {
    *exited = 1; //keep track of whether while loop should exit
    return;
  }

  if (strcmp(parsed[0], "cd") == 0) {
    if (parsed[2] != NULL) {
      printf("cd: too many arguments \n");
      return;
    }

    int error = chdir(parsed[1]);
    if (error != 0) printf("cd: %s \n", strerror(errno));
    return;
  }

  pid_t pid = fork();

  if (pid == 0) { //is the child
    if (strchr(lineCpy, '>') != NULL) redir_out(parsed, num_args);
    if (strchr(lineCpy, '<') != NULL) redir_in(parsed, num_args);
    if (strchr(lineCpy, '|') != NULL) my_pipe(parsed, num_args);

    else { //normal exec
      execvp(parsed[0], parsed);
      printf("%s: command not found \n", lineCpy);
      exit(0);
    }
  } else { //is the parent
    wait(NULL); //wait for child to exit first
    remove("tempfile.txt"); //if piping is done
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

void semicolon_exec(char *line, int *exited) {
  int num_commands = 0;
  char ** commands = semicolon_parse(line, &num_commands);

  for (int i = 0; i < num_commands; i++) {
    if (*exited == 1)
      return;

    exec_args(commands[i], exited);
  }

  free(commands);
}
