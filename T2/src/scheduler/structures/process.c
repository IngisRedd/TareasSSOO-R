#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## PROCESS ############

Process* process_init(int id, char* name, int nFabrica){
    Process* process = malloc(sizeof(Process));
    process -> id = id;
    process -> name = strdup(name);
    process -> nFabrica = nFabrica;
    process -> state = 0;

    return process;
}

void process_destroy(Process* process){
    free(process -> name);
    free(process);
}