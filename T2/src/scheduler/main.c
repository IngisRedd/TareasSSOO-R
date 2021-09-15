#include <stdio.h>
#include "structs.h"
#include "../file_manager/manager.h"

int main(int argc, char **argv)
{
  printf("Hello T2!\n");

  InputFile *file = read_file("input.txt");

  printf("Reading file of length %i:\n", file->len);
  for (int i = 0; i < file->len; i++)
  {
    char **line = file->lines[i];
    printf(
        "\tProcess %s from factory %s has init time of %s and %s bursts.\n",
        line[0], line[2], line[1], line[3]);
        printf("Fabrica: %d\n", (int)line[2][8]);
    char* nombre = line[0];
    int nFabrica = line[2];
    Process* process = process_init(i, nombre, nFabrica);
    printf("Process %s fabrica %d\n", process->name, process->nFabrica);
  }
}
