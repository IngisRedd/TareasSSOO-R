#include "simulation.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

//######## SIMULATION ############

Simulation* simulation_init(int Q, InputFile* input_file){
    Simulation* sim = malloc(sizeof(Simulation));
    
    // Initialize Queue, CPU, clock:
    printf("Sim will create queue\n");
    sim -> queue = queue_init(Q);
    // printf("after creating queue\n");
    sim -> CPU = NULL;
    sim -> clock = 0;
    sim -> total_p = input_file -> len;
    sim -> np_cnt = 0;       // new process counter
    sim -> fp_cnt = 0;       // finished process counter

    // all_processes contains pointers to all created processes:
    printf("Sim will create all %d process\n", sim -> total_p);
    sim -> all_processes = malloc((input_file -> len) * sizeof(Process*));
    for (int i = 0; i < sim -> total_p; i++) {
        printf("Sim will create process %d\n", i);
        sim -> all_processes[i] = process_init(i, input_file);
        printf("Sim after create process %d\n", i);
    }

    // p_init_times contains initial times for each process:
    sim -> p_init_times = malloc((input_file -> len) * sizeof(int));
    for (int i = 0; i < input_file -> len; i++)
    {
      char **line = input_file -> lines[i];
    //   printf(
    //       "\tProcess %s from factory %s has init time of %d and %s bursts.\n",
    //       line[0], line[2], atoi(line[1]), line[3]);
      sim -> p_init_times[i] = atoi(line[1]);
    }
    
    return sim;
}

void simulation_destroy(Simulation* sim){
    queue_destroy(sim-> queue);
    // Destroy all processes:
    for (int i = 0; i < sim -> total_p; i++) {
        printf("Process %s will be destroyed\n", sim -> all_processes[i] -> name);
        process_destroy((sim -> all_processes)[i]);
    }
    free(sim -> all_processes);
    free(sim -> p_init_times);
    
    printf("Simulation destroyed\n");
    free(sim);
}

int is_finished(Simulation* sim, int dev_mode){
    if (dev_mode) {
        if (sim -> clock > dev_mode) {
            return 1;
        }
    }

    // This is real
    if (sim -> fp_cnt == sim -> total_p) {
        return 1;
    } else {
        return 0;
    }

}

void sort_new_processes(Simulation* sim, int new_p_cnt){
    int x, y, min;
    Process* tmp;
    for(x = 0; x < new_p_cnt; x++) {
        min = x;
        for(y = x + 1; y < new_p_cnt; y++) {
            if(sim -> new_processes[min] -> nFabrica > sim -> new_processes[y] -> nFabrica) {
                min = y;
            } else if (sim -> new_processes[min] ->nFabrica == sim -> new_processes[y] -> nFabrica){
                int name_compare;
                name_compare = strcasecmp(sim -> new_processes[min] -> name, sim -> new_processes[y] -> name);
                if (name_compare > 0){
                    min = y;
                }
            }
        }
        tmp = sim -> new_processes[min];
        sim -> new_processes[min] = sim -> new_processes[x];
        sim -> new_processes[x] = tmp;
    }
}

Process* manage_process_in_CPU(Simulation* sim){
    // Process* p_in_CPU = sim -> CPU;     // Proceso en la CPU.
    Process* p_out_of_CPU = NULL;       // Proceso salido de la CPU.

    // IF Proceso cede la CPU, pasa a WAITING, y se va al final de la cola.

        p_out_of_CPU = sim -> CPU;
    // ELSE IF Proceso termina su ejecución, pasa a FINISHED y sale del sistema.
    // ELSE IF Proceso consume todo su quantum, pasa a READY y se va al final de la cola.
        p_out_of_CPU = sim -> CPU;
    // ELSE, el proceso continua en RUNNING.
    return p_out_of_CPU;
}

void enter_processes_into_queue(Simulation* sim, Process* p_out_of_CPU){
    Queue* queue = sim -> queue;
    if (p_out_of_CPU) {
        add_new_process(queue, p_out_of_CPU);
    }

    // Se ingresan los nuevos procesos al sistema:
    int new_p_cnt = 0;    // Contador de nuevos procesos, suponemos que hay máximo 8.
    for (int i = 0; i < (sim -> total_p); i++){
        if (sim -> p_init_times[i] == sim -> clock) {
            Process* new_p = sim -> all_processes[i];
            sim -> new_processes[new_p_cnt] = new_p;
            printf("[t = %d] El proceso %s ha sido creado.\n", sim -> clock, new_p -> name);

            (sim -> np_cnt)++;
            new_p_cnt++;
        }
    }

    // Si hay + de 1 nuevo proceso, se ordenan:
    if (new_p_cnt > 1) {
        sort_new_processes(sim, new_p_cnt);
        printf("after sorting new processes\n");
    }
    // Se ingresan a la cola:
    for (int i = 0; i < new_p_cnt; i++){
        add_new_process(queue, sim -> new_processes[i]);
    }
}

void execute_next_process(Simulation* sim){
    //  se elige uno para que pase a RUNNING.
    // Si no hay ninguno:
    if (!(sim -> CPU)) {
        printf("[t = %d] No hay ningun proceso ejecutando en la CPU.\n", sim -> clock);
    }

}

void update_process_statistics(Simulation* sim){
    //  Si un proceso salió de la CPU, se considera como su hubiera estado RUNNING.
    // printf("Update statistics\n");
}

void update_waiting_process(Simulation* sim){
    Node* node = sim -> queue -> entry_node;
    for (int n = 0; n < 7; n++){
        if (node -> process != NULL && node -> process -> state == WAITING){
            int next_burst_time = node -> process -> burst_cum_times[node -> process -> burst_cnt];
            int total_burst_time = node -> process -> turnos_CPU + node -> process -> waiting_time;
            if (next_burst_time == total_burst_time){
                node -> process -> state = READY;
            }
        }
        if (node -> next_node != NULL){
            Node* next_node = node -> next_node; 
            node = next_node;
        }
    }
}

void simulation_step(Simulation* sim){
    // printf("Parte el turno %d\n", sim -> clock);

    Process* p_out_of_CPU = NULL;       // Proceso salido de la CPU
    // 1. Si hay un proceso en la CPU:
        if (sim -> CPU) {
            p_out_of_CPU = manage_process_in_CPU(sim);  // Proceso salido de la CPU
        }    
    // 2. Procesos creados entran a la cola, incluyendo el proceso que salga de la CPU:
        enter_processes_into_queue(sim, p_out_of_CPU);
    // 3. Si no hay un proceso en la CPU:
        if (!(sim -> CPU)) {
            execute_next_process(sim);
        }
    // 4. Se actualizan las estadísticas de los procesos:
        update_process_statistics(sim);
    // 5. Los procesos WAITING que terminaron su I/O Burst (Bi) pasan a READY:
        update_waiting_process(sim);
    // printf("Se  terminó el turno %d\n", sim -> clock);
    (sim -> clock)++;
}


int qi_calculator(Queue* queue, int nFabrica){
    int ni;
    int f = 0;
    ni = queue -> p_por_fabrica_cnt[nFabrica - 1];
    for (int fb = 0; fb < 4; fb++){
        if (queue -> p_por_fabrica_cnt[fb] != 0){
            f++;
        }
    }
    int qi = (queue -> Q)/(ni*f);
    return qi;
}