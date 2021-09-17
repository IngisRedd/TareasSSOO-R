#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structures/simulation.h"
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
  // Read Q input value:
  if (argc == 4) {
    Q = atoi(argv[3]);
  }

  if ( access( filename, F_OK ) == 0 ) {
    // if file exists, read input file
    InputFile *input_file = read_file(filename);

    // SIMULATION START!!
    Simulation* sim = simulation_init(Q, input_file);

    Queue* queue = queue_init(50);
    queue -> p_por_fabrica_cnt[0] = 1;
    queue -> p_por_fabrica_cnt[1] = 1;
    queue -> p_por_fabrica_cnt[2] = 0;
    queue -> p_por_fabrica_cnt[3] = 1;

    printf("CALCULO qi: %d\n", qi_calculator(queue, 3));
    while (!is_finished(sim, 100)) {
      simulation_step(sim);
    }
    
    // Free input file memory:
    input_file_destroy(input_file);




    // Free simulation memory and all of its contents:
    simulation_destroy(sim);



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
