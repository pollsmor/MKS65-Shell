#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"

int main() {
  //printf("\033[H\033[J"); //clear the shell - oops, this breaks the test_cmds file
  char input[300] = ""; //support commands up to 300 characters long
  char cwd[200];
  int exited = 0;

  while (!exited) {
    printf("%s$ ", getcwd(cwd, 200));
    fgets(input, 300, stdin);
    input[strlen(input) - 1] = '\0'; //strip the newline at the end

    if (input[0] != '\0') { //only run all this stuff if the user actually typed something in
      if (strchr(input, ';') == NULL) { //no semicolons, only 1 command
        exec_args(input, &exited);
      } else { //there are semicolons
        semicolon_exec(input, &exited);
      }

      input[0] = '\0'; //clear the input so doesn't keep running
    }
  }

  return 0;
}
