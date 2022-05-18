#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int arraySize, threadsNum; // Array size and the number of threads

  // Opening parameters file and reading parameters
  FILE *fileParameters = fopen("parameters.txt", "r");
  if (fileParameters == NULL) {
    printf("Failed to open parameters file\n");
    fclose(fileParameters);
    exit(ERROR_OPEN_PARAMETERS);
  } else {
    fscanf(fileParameters, "%d %d", &arraySize, &threadsNum);
    fclose(fileParameters);
  }

  // Creating an array

  return 0;
}