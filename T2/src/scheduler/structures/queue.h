#include "node.h"

// ######## QUEUE ############

typedef struct queue{
    int cant_process;
    Node* entry_node;
    Node* exit_node;
} Queue;

Queue* queue_init();
// Run one step of the simulation:
void queue_destroy(Queue* queue);
void add_new_process(Queue* queue, int id, char* name, int nFabrica);
int simulation_step(Queue* queue);

int f_calculator(Queue* queue);
int qi_calculator(int Q, Queue* queue, int fabrica, int f);

