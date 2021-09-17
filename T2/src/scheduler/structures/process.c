#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## PROCESS ############

Process* process_init(int id, InputFile* input_file){
    Process* process = malloc(sizeof(Process));
    printf("Process %d created\n", id);
    // printf("Process %d created\n", id);
    process -> id = id;

    char **if_p_data;   // Input file process data for this process.
    if_p_data = (input_file -> lines)[id];
    process -> name = strdup(if_p_data[0]);
    process -> nFabrica = atoi(if_p_data[2]);
    process -> state = READY;
    process -> total_bursts = atoi(if_p_data[3]);
    process -> burst_cum_times = malloc((process -> total_bursts) * sizeof(int));
    printf("Process %d created burst cum times len %d\n", id, process -> total_bursts);
    
    // Se rellena burst_cum_times con el tiempo acumulado de cada burst
    int time_cnt = 0;
    for (int i = 0; i < (process -> total_bursts); i++) {
        printf("Will read input file %d\n", 4 + i);
        time_cnt += atoi(if_p_data[4 + i]);
        process -> burst_cum_times[i] = time_cnt;
    }

    // Stats:
    process -> burst_cnt = 0; 
    process -> turnos_CPU = 0; 
    process -> interrupciones = 0;
    process -> turnaround_time = 0;
    process -> response_time = 0;
    process -> waiting_time = 0;
    process -> ready_time = 0;

    // printf("Just before returning Process %d created\n", id);
    return process;
}
void change_state(Process* p, ProcessStatus next_state, int clock){
    // Si el proceso terminó:
        if (next_state == FINISHED){
            printf("[t = %d] El proceso %s terminó y sale del sistema\n",
                clock,
                p -> name
            );
        } else {
            printf("[t = %d] El proceso %s ha pasado de %s a %s\n",
                clock,
                p -> name,
                int_to_state_string(p -> state),
                int_to_state_string(next_state)
            );
        }

    
    // Si se le acaba el cuantum y es interrumpido
        // if ((p -> state == RUNNING) && (next_state == READY)){
        //     p -> interrupciones++;
        // }
    // Si termina algún burst:
        // else if ( 
        //     ((p -> state == RUNNING) && (next_state == WAITING))
        //     || ((p -> state == WAITING) && (next_state == READY))
        //     || ((p -> state == RUNNING) && (next_state == FINISHED))
        // ){
        //     p -> burst_cnt++;
        // }

    p -> state = next_state;
}

void process_destroy(Process* process){
    free(process -> name);
    free(process -> burst_cum_times);
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