#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "parse.h"
#include "redirect.h"
#include "pipes.h"

int main() {
  char input[300] = ""; //support commands up to 300 characters long
  char cwd[200];
  int status;
  int exited = 0;

  while (exited == 0) {
    printf("%s$ ", getcwd(cwd, 200));
    fgets(input, 300, stdin);
    input[strlen(input) - 1] = '\0'; //strip the newline at the end
    char ** args = parse_args(input);

    if (strcmp(args[0], "exit") == 0) {
      exited = 1; //keep track of whether while loop should exit
    }

    if (strcmp(args[0], "cd") == 0) {
      chdir(args[1]);
    }

    if (input[0] != '\0') {
      exec_args(args, &status);
      input[0] = '\0'; //clear the input so doesn't keep running
    }
  }

  return 0;
}
