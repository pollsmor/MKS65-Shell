#include <stdio.h>
#include <string.h>

int main() {
  char input[300] = ""; //support commands up to 300 characters long

  while (strcmp(input, "exit") != 0) {
    printf("$ ");
    fgets(input, 300, stdin);
    input[strlen(input) - 1] = '\0'; //strip the newline at the end
  }

  printf("You have exited this shell. \n");
  return 0;
}
