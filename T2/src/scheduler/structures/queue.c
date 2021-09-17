#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## QUEUE ############

Queue* queue_init(){
    Queue* queue = malloc(sizeof(Queue));
    
    queue -> entry_node = node_init();
    printf("entry node created\n");

    Node* parent_node = queue -> entry_node;
    for (int i = 0; i < 7; i++) {
        parent_node -> next_node = node_init();
        (parent_node -> next_node) -> prev_node = parent_node;
        printf("Node %i created\n", i + 1);
        parent_node = parent_node -> next_node;
    }

    queue -> exit_node = parent_node;

    return queue;
}

void queue_destroy(Queue* queue){
    chain_node_destroy(queue-> entry_node);
    printf("Queue destroyed\n");
    free(queue);
}

void add_new_process(Queue* queue, Process* new_process){
    // Si la cola está llena:
    printf("Queue va a ingresar nuevo proceso %s!\n", new_process -> name);
    if ((queue -> entry_node) -> process) {
        printf("La cola está llenaa, tendré que matar a %s!\n", new_process -> name);
        process_destroy(new_process);
    } else {
        printf("Vamos a pushear a %s al queue!\n", new_process -> name);
        (queue -> entry_node) -> process = new_process;
        chain_push_process(queue -> entry_node);
        print_queue(queue, 0);
        print_queue(queue, 1);

    }
}

Process* queue_pop(Queue* queue) {
    Process* p_from_CPU = queue -> exit_node -> process;
    chain_pull_process(queue -> exit_node);
    return p_from_CPU;

}

void print_queue(Queue* queue, int states){
    // printf("Cola de procesos:");
    print_node_chain(queue -> entry_node, states);
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