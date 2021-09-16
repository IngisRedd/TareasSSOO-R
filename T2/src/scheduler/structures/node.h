#include "process.h"

// ######## QUEUE NODE ############

typedef struct node{
    struct node *prev_node;
    struct node *next_node;
    Process* process;
} Node;

Node* node_init();
// Destroys nodes and their processes in chain:
void chain_node_destroy(Node* node);
// Every node starting from exit_node gets the process of prev_node, entry_node gets NULL:
void chain_pull_process(Node* node);
// A new node gets into the queue, must first give the process to entry_node:
void chain_push_process(Node* node);
// Pretty print state of node:
void print_node_chain(Node* node, int states);
