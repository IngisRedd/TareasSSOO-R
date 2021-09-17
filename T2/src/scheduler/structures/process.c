#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## PROCESS ############

Process* process_init(int id, char* name, int nFabrica){
    Process* process = malloc(sizeof(Process));
    // printf("Process %d created\n", id);
    process -> id = id;
    process -> name = strdup(name);
    process -> nFabrica = nFabrica;
    process -> state = READY;
    
    // Stats:
    process -> turnos_CPU = 0; 
    process -> interrupciones = 0;
    process -> turnaround_time = 0;
    process -> response_time = 0;
    process -> waiting_time = 0;

    // printf("Just before returning Process %d created\n", id);
    return process;
}
void change_state(Process* process, int state, int clock){
    process -> state = state;
    printf("[t = %d] El proceso %s ha pasado de %s a\n",
        clock, process -> name, int_to_state_string(process -> state) );
    printf("%s.\n", int_to_state_string(state));
}

void process_destroy(Process* process){
    free(process -> name);
    printf("Process %d destroyed\n", process -> id);
    free(process);
}

const char* int_to_state_string(ProcessStatus state) {
    if (state == 0) {
        return "RUNNING";
    } else if (state == 1) {
        return "READY";
    } else if (state == 2) {
        return "WAITING";
    } else if (state == 3) {
        return "FINISHED";
    } else {
        return "ERROR";
    }
}