#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
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

//Returns a list of arguments
char ** parse_args(char *line, int *num_args) {
  char ** output = malloc(100); //space to fit all arguments
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
    chdir(parsed[1]);
    return;
  }

  pid_t pid = fork();

  if (pid == 0) { //is the child
    if (strchr(lineCpy, '>') == NULL && strchr(lineCpy, '<') == NULL && strchr(lineCpy, '|') == NULL) {
      execvp(parsed[0], parsed);
      printf("%s: command not found \n", lineCpy);
      exit(0);
    } else if (strcmp(parsed[num_args - 2], "|") == 0) { //piping
      my_pipe(parsed, num_args);
    } else { //since you are using redirection, assuming you have at least 3 args
      if (strcmp(parsed[num_args - 2], ">") == 0) { //output redirection
        redir_out(parsed, num_args);
      } else { //input redirection
        redir_in(parsed, num_args);
      }
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
