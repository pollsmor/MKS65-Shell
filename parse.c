#include <stdlib.h>
#include <string.h>

//Returns a list of arguments
char ** parse_args(char * line) {
  char ** output = malloc(5 * sizeof(char *));
  char *curr = line;

  int i = 0;
  while (curr != NULL) {
    output[i] = strsep(&curr, " ");
    i++;
  }

  return output;
}
