#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "../file_manager/manager.h"

int main(int argc, char **argv)
{
  printf("Hello T2!\n");

  if (argc != 3 && argc != 4) {
    printf("Expected 3 or 4 arguments, recieved %d\n", argc);
    return 0;
  }

  // Obtain input from command line
  char *filename = argv[1];
  char *outputname = argv[2];
  // Code from https://stackoverflow.com/questions/10347689/how-can-i-check-whether-a-string-ends-with-csv-in-c
  char *dot = strrchr(outputname, '.');
  if (!(dot && !strcmp(dot, ".csv"))) {
    printf("Output filename must end with .csv\n");
    return 0;
  }
  
  int Q = 100;
  if (argc == 4) {
    Q = atoi(argv[3]);
  }


  if ( access( filename, F_OK ) == 0 ) {
    // if file exists, read input file
    InputFile *file = read_file(filename);

    printf("Reading file of length %i:\n", file->len);
    for (int i = 0; i < file->len; i++)
    {
      char **line = file->lines[i];
      printf(
          "\tProcess %s from factory %s has init time of %s and %s bursts.\n",
          line[0], line[2], line[1], line[3]);
          printf("Fabrica: %d\n", (int)line[2][8]);
      // char* nombre = line[0];
      // int nFabrica = line[2];
      // Process* process = process_init(i, nombre, nFabrica);
      // printf("Process %s fabrica %d\n", process->name, process->nFabrica);
    }
    // Free input file memory:
    input_file_destroy(file);

    // Initialize Queue:

    // SIMULATION START!!





    // Create output file
    FILE *fp; 
    fp  = fopen (outputname, "w");
    if (fp != NULL) {
      fprintf(fp, "Aqui va el output \n");
    }
    fclose (fp);
  
  } else {
    // if input file doesn't exist
    printf("That input file does not exist\n");
  }
}
