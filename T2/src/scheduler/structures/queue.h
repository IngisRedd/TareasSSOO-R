#include "node.h"

// ######## QUEUE ############

typedef struct queue{
    Node* entry_node;
    Node* exit_node;
    int Q;      // Input Q value default = 100
    int p_por_fabrica_cnt[4];
} Queue;

Queue* queue_init(int Q);
void queue_destroy(Queue* queue);
// Push a new proces into the queue:
void add_new_process(Queue* queue, Process* new_process);
// Get last item from queue and move the rest forward
Process* queue_pop(Queue* queue);
// Calculates quantum for each fabrica.
// IMPORTANTE: 
// Por falta de claridad en el enunciado, suponemos que el proceso que está entrando a la CPU tmb se considera.
int qi_calculator(Queue* queue, int nFabrica);
// Print queue full status in console. It can print process names or states
void print_queue(Queue* queue, int states);
