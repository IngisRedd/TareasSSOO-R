#include "node.h"

// ######## QUEUE ############

typedef struct queue{
    Node* entry_node;
    Node* exit_node;
    int Q;
    int p_por_fabrica_cnt[4];
} Queue;

Queue* queue_init(int Q);
void queue_destroy(Queue* queue);
// Push a new proces into the queue:
void add_new_process(Queue* queue, Process* new_process);
// Get last item from queue and move the rest forward
Process* queue_pop(Queue* queue);
// Print queue full status in console. It can print process names or states
void print_queue(Queue* queue, int states);

// int f_calculator(Queue* queue);

