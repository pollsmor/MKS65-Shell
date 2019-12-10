#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

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
  strip_leading_spaces(line);

  while (curr != NULL) {
    output[*num_args] = strsep(&curr, " ");
    (*num_args)++;
  }

  output[*num_args] = NULL;
  return output;
}

//Take in the list of arguments from parse_args
void exec_args(char * line, int *exited, int *status) {
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
      printf("")
      exit(0);
    } else if (strcmp(parsed[num_args - 2], "|") == 0) { //piping
      char *program = parsed[num_args - 1];
      parsed[num_args - 2] = NULL; //sp that execvp doesn't use the piping stuff as an arg
      int tempfile = open("tempfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0640);
      dup2(tempfile, STDOUT_FILENO);
      execvp(parsed[0], parsed); //will put output of this in tempfile.txt
      lseek(tempfile, 0, SEEK_SET); //go back to beginning of file to read
      //execlp(program, program, "tempfile.txt", NULL);
      printf("LULULULUL \n");
      execlp("ls", "ls", NULL);

      close(tempfile);
    } else { //since you are using redirection, assuming you have at least 3 args
      if (strcmp(parsed[num_args - 2], ">") == 0) { //output redirection
        char *file = parsed[num_args - 1];
        parsed[num_args - 2] = NULL; //so that execvp doesn't use the redirection stuff as an arg
        int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0640);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execvp(parsed[0], parsed);
        printf("Failed to redirect output. \n");
        exit(0);
      } else { //input redirection
        char *file = parsed[num_args - 1];
        parsed[num_args - 2] = NULL; //so that execvp doesn't use the redirection stuff as an arg
        int fd = open(file, O_RDONLY);
        int stdin_backup = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        execvp(parsed[0], parsed);

        //dup2(stdin_backup, STDIN_FILENO);
        //close(stdin_backup);
        printf("Failed to redirect input. \n");
        exit(0);
      }
    }
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
