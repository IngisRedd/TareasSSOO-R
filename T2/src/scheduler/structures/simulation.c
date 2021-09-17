#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## SIMULATION ############

Simulation* simulation_init(int Q, InputFile* input_file){
    Simulation* sim = malloc(sizeof(Simulation));
    
    // Initialize Queue, CPU, clock:
    sim -> queue = queue_init();
    sim -> CPU = NULL;
    sim -> Q = Q;
    sim -> clock = 0;
    sim -> np_cnt = 0;       // new process counter
    sim -> fp_cnt = 0;       // finished process counter

    sim -> input_file = input_file;
    // p_init_times contains initial times for each process.
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
    free(sim -> p_init_times);
    // printf("Simulation destroyed\n");
    free(sim);
}

int is_finished(Simulation* sim, int dev_mode){
    if (dev_mode) {
        if (sim -> clock > dev_mode) {
            return 1;
        }
    }

    // This is real
    if (sim -> fp_cnt == (sim -> input_file -> len)) {
        return 1;
    } else {
        return 0;
    }

}

Process* create_process_from_index(Simulation* sim, int i){
    char **line = sim -> input_file -> lines[i];
    Process* process = process_init(
        sim -> np_cnt,
        line[0],
        atoi(line[2])
    );
    printf("[t = %d] El proceso %s ha sido creado.\n", sim -> clock, line[0]);
    (sim -> np_cnt)++;
    
    return process;
}

void sort_new_processes(Simulation* sim, int new_p_cnt){
    // Ordenar los new_p_cnt primeros procesos del array (sim -> new_processes) por prioridad de llegada:
    // 3.1) Con menor número de fábrica f.
    // 3.2) Con menor NOMBRE PROCESO. Para esta parte deber ́as usar strcmp.
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
    Process* p_from_CPU = NULL;       // Proceso salido de la CPU
    // IF Proceso cede la CPU, pasa a WAITING, y se va al final de la cola.
        p_from_CPU = sim -> CPU;
    // ELSE IF Proceso termina su ejecución, pasa a FINISHED y sale del sistema.
    // ELSE IF Proceso consume todo su quantum, pasa a READY y se va al final de la cola.
        p_from_CPU = sim -> CPU;
    // ELSE, el proceso continua en RUNNING.
    return p_from_CPU;
}

void enter_processes_into_queue(Simulation* sim, Process* p_from_CPU){
    Queue* queue = sim -> queue;
    if (p_from_CPU) {
        add_new_process(queue, p_from_CPU);
    }

    int new_p_pos_arr[8];    // Array para guardar posiciones de los nuevos procesos.
    int new_p_cnt = 0;    // Contador de nuevos procesos, suponemos que hay máximo 8.
    
    // Vemos cuantos procesos nuevos hay que crear:
    for (int i = 0; i < (sim -> input_file-> len); i++){
        if (sim -> p_init_times[i] == sim -> clock) {
            new_p_pos_arr[new_p_cnt] = i;
            new_p_cnt++;
        }
    }

    if (new_p_cnt) {
        // Se crean los nuevos procesos:
        for (int i = 0; i < new_p_cnt; i++){
            sim -> new_processes[i] = create_process_from_index(sim, new_p_pos_arr[i]);
            printf("After creating 1 new process\n");
        }
        // Se ordenan:
        sort_new_processes(sim, new_p_cnt);
        // Se ingresan a la cola:
        for (int i = 0; i < new_p_cnt; i++){
            add_new_process(queue, sim -> new_processes[i]);
        }
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
    // WAITING a READY 
    // printf("Update waiting procesess\n");
}

void simulation_step(Simulation* sim){
    // printf("Parte el turno %d\n", sim -> clock);

    Process* p_from_CPU = NULL;       // Proceso salido de la CPU
    // 1. Si hay un proceso en la CPU:
        if (sim -> CPU) {
            p_from_CPU = manage_process_in_CPU(sim);  // Proceso salido de la CPU
        }    
    // 2. Procesos creados entran a la cola, incluyendo el proceso que salga de la CPU:
        enter_processes_into_queue(sim, p_from_CPU);
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
