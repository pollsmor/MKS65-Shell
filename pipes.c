#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void my_pipe(char ** args, int num_args) {
  char *program = args[num_args - 1]; //ls | wc --> would be wc
  args[num_args - 2] = NULL; //so that execvp doesn't use the | onwards as args
  int tempfile = open("tempfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0640); //temp file to write to for piping
  int stdout_backup = dup(STDOUT_FILENO);
  dup2(tempfile, STDOUT_FILENO);

  pid_t pid = fork(); //need another child to run another process

  if (pid == 0) { //is the child
    execvp(args[0], args); //will put output of this in tempfile.txt
    printf("Failed to run command. \n");
    exit(1);
  } else { //is the parent
    wait(0);
    close(tempfile);
    dup2(stdout_backup, STDOUT_FILENO);
    execlp(program, program, "tempfile.txt", NULL);
    printf("Piping failed. \n");
    exit(1);
  }
}
