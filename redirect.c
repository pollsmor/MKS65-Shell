#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void redir_out(char ** args, int num_args) {
  char *file = args[num_args - 1];
  args[num_args - 2] = NULL; //so that execvp doesn't use the > and later stuff as args
  int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0640);
  dup2(fd, STDOUT_FILENO);
  close(fd);
  execvp(args[0], args);
  printf("Failed to redirect output. \n");
  exit(1);
}

void redir_in(char ** args, int num_args) {
  char *file = args[num_args - 1];
  args[num_args - 2] = NULL; //so that execvp doesn't use the redirection stuff as an arg
  int fd = open(file, O_RDONLY);
  dup2(fd, STDIN_FILENO);
  close(fd);
  execvp(args[0], args);
  printf("Failed to redirect input. \n");
  exit(1);
}

void redir_in_out(char ** args, int num_args) {
  char *output_file = args[num_args - 1];
  int fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0640);
  dup2(fd, STDOUT_FILENO);
  close(fd);

  args[num_args - 2] = NULL;
  redir_in(args, num_args - 2);
}
