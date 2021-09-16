#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## QUEUE ############

Queue* queue_init(){
    Queue* queue = malloc(sizeof(Queue));
    
    queue -> entry_node = node_init();
    // printf("entry node created\n");

    Node* parent_node = queue -> entry_node;
    for (int i = 0; i < 7; ++i) {
        parent_node -> next_node = node_init();
        (parent_node -> next_node) -> prev_node = parent_node;
        // printf("Node %i created\n", i);
        parent_node = parent_node -> next_node;
    }

    queue -> exit_node = parent_node;
    
    return queue;
}

void queue_destroy(Queue* queue){
    chain_node_destroy(queue-> entry_node);
    // printf("Queue destroyed\n");
    free(queue);
}

void add_new_process(Queue* queue, int id, char* name, int nFabrica){
    Process* new_process = process_init(id, name, nFabrica);
    // Si la cola está llena:
    if ((queue -> entry_node) -> process) {
        
    } else {
        (queue -> entry_node) -> process = new_process;
        chain_push_process(queue -> entry_node);

    }
}

int simulation_step(Queue* queue){
    return 1;
}


// //######## Auxiliares #########

// int f_calculator(Queue* queue){
//     int* fabricas[queue->cant_process];
//     int fabs = 0;
//     int in = 0;
//     int f = 0;
//     for (int p=0; p<queue->cant_process; p++){
//         for (int f=0; f<queue->cant_process;f++){
//             if (fabricas[f] == queue->line[p]->nFabrica){
//                 in = 1;
//             }
//         }
//         if (in == 0){
//             fabricas[fabs]=p;
//             fabs+=1;
//         } else {
//             f+=1;
//         }
//     }
//     return f;
// }

// int qi_calculator(int Q, Queue* queue, int fabrica, int f){
//     int ni = 0;
//     for (int p=0; p<queue->cant_process; p++){
//         if (queue->line[p]->nFabrica == fabrica){
//             ni+=1;
//         }
//     }
//     int qi = Q/(ni*f);
//     return qi;
// }