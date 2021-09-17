#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## QUEUE ############

Queue* queue_init(int Q){
    Queue* queue = malloc(sizeof(Queue));
    
    queue -> entry_node = node_init();
    queue -> Q = Q;
    for (int i = 0; i < 4; i++) {
        queue -> p_por_fabrica_cnt[i] = 0;
    }
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
        queue -> p_por_fabrica_cnt[(new_process -> nFabrica) - 1]++;
    }
}

Process* queue_pop(Queue* queue) {
    Process* p_from_CPU = queue -> exit_node -> process;
    chain_pull_process(queue -> exit_node);
    queue -> p_por_fabrica_cnt[(p_from_CPU -> nFabrica) - 1]--;

    return p_from_CPU;
}

void print_queue(Queue* queue, int states){
    // printf("Cola de procesos:");
    print_node_chain(queue -> entry_node, states);
}
