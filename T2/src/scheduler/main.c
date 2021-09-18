#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structures/simulation.h"
#include "../file_manager/manager.h"

int main(int argc, char **argv)
{
  // printf("Hello T2!\n");

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
  // Read Q input value:
  if (argc == 4) {
    Q = atoi(argv[3]);
  }

  if ( access( filename, F_OK ) == 0 ) {
    // if file exists, read input file
    InputFile *input_file = read_file(filename);

    // Initialize Simulation an all other structs:
    Simulation* sim = simulation_init(Q, input_file);


    // Free input file memory:
    input_file_destroy(input_file);

    // SIMULATION START!!
    while (!is_finished(sim, 0)) {
      simulation_step(sim);
    }



    // Create output file
    FILE *fp; 
    fp  = fopen (outputname, "w");
    if (fp != NULL) {
      for (int p = 0; p < sim -> total_p; p++){
        Process* process = sim -> all_processes[p];
        fprintf(fp, "%s,%d,%d,%d,%d,%d\n",
          process -> name,
          process -> turnos_CPU,
          process -> interrupciones,
          process -> turnaround_time,
          process -> response_time,
          (process -> waiting_time + process -> ready_time));
      }
    }
    fclose (fp);

    // Free simulation memory and all of its contents:
    simulation_destroy(sim);
  
  } else {
    // if input file doesn't exist
    printf("That input file does not exist\n");
  }
}
