#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## PROCESS ############

Process* process_init(int id, InputFile* input_file){
    Process* process = malloc(sizeof(Process));
    // printf("Process %d created\n", id);
    // printf("Process %d created\n", id);
    process -> id = id;

    char **if_p_data;   // Input file process data for this process.
    if_p_data = (input_file -> lines)[id];
    process -> name = strdup(if_p_data[0]);
    process -> init_time = atoi(if_p_data[1]);
    process -> nFabrica = atoi(if_p_data[2]);
    process -> state = UNBORN;
    process -> total_bursts = atoi(if_p_data[3]) * 2 - 1;
    process -> burst_cum_times = malloc((process -> total_bursts) * sizeof(int));
    // printf("Process %d created burst cum times len %d\n", id, process -> total_bursts);
    
    // Se rellena burst_cum_times con el tiempo acumulado de cada burst
    int time_cnt = 0;
    for (int i = 0; i < (process -> total_bursts); i++) {
        // printf("Will read input file %d\n", 4 + i);
        time_cnt += atoi(if_p_data[4 + i]);
        process -> burst_cum_times[i] = time_cnt;
        // printf("Time cnt: %d\n", time_cnt);


    }

    // Stats:
    process -> burst_cnt = 0; 
    process -> turnos_CPU = 0; 
    process -> interrupciones = 0;
    process -> turnaround_time = 0;
    process -> response_time = -1;
    process -> waiting_time = 0;
    process -> ready_time = 0;

    // printf("Just before returning Process %d created\n", id);
    return process;
}
void change_state(Process* p, ProcessStatus next_state, int clock){
    // Si el proceso terminó:
        if (next_state == FINISHED){
            printf("[t = %d] El proceso %s terminó y sale del sistema\n",
                clock + 1,
                p -> name
            );
        } else {
            printf("[t = %d] El proceso %s ha pasado de %s a %s\n",
                clock + 1,
                p -> name,
                int_to_state_string(p -> state),
                int_to_state_string(next_state)
            );
        }
    p -> state = next_state;
}

void process_destroy(Process* process){
    free(process -> name);
    free(process -> burst_cum_times);
    // printf("Process %d destroyed\n", process -> id);
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

void print_process(Process* process) {
    printf("Process %s:\nid: %d\ninit_time: %d\nnFabrica: %d\nstate: %s\ntotal_bursts: %d\ncurrent_bursts: %d\ntotal_burst_time: %d\nburst_cnt: %d\nturnos_CPU: %d\ninterrupciones: %d\nturnaround_time: %d\nresponse_time: %d\nwaiting_time: %d\nready_time: %d\n",
    process -> name,
    process -> id,
    process -> init_time,
    process -> nFabrica,
    int_to_state_string(process -> state),
    process -> total_bursts,       // N° total de bursts (I/O o CPU).
    process -> burst_cum_times[process -> total_bursts - 1],
    process -> turnos_CPU + process -> waiting_time,
    process -> burst_cnt,          // Contador de bursts (I/O o CPU) terminados.
    process -> turnos_CPU,         // N° turnos en CPU.
    process -> interrupciones,     // N° de veces interrumpido por terminar quantum.
    process -> turnaround_time,    // N° turnos en el sistema (queue + CPU).
    process -> response_time,      // N° turnos hasta ser atendido por primera vez.
    process -> waiting_time,       // N° turnos en estado WAITING.
    process -> ready_time       
    );
}