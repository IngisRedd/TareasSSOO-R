#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//######## QUEUE NODE ############

Node* node_init(){
    Node* node = malloc(sizeof(Node));
    node -> prev_node = NULL;
    node -> next_node = NULL;
    node -> process = NULL;
    return node;
}

void chain_pull_process(Node* node){
    // printf("Vamos a pushear un proceso!\n");
    if (node -> prev_node) {
        node -> process = (node -> prev_node) -> process;
        chain_pull_process(node -> prev_node);
    } else {
        node -> process = NULL;
    }
}

void chain_push_process(Node* node){
    if (node -> next_node) {
        if (!(node -> next_node) -> process) {
            (node -> next_node) -> process = node -> process;
            node -> process = NULL;
            chain_push_process(node -> next_node);
        }
    }
}

void chain_node_destroy(Node* node){
    // if (node -> process) {
    //     process_destroy(node -> process);
    // }

    if (node -> next_node) {
        // printf(" Next Node will be destroyed\n");
        chain_node_destroy(node -> next_node);
    }
    // printf(" A Node destroyed\n");
    free(node);
}

void print_node_chain(Node* node, int states){
    if (node -> process){
        if (states) {
            printf("[ %s ]", int_to_state_string(node -> process -> state));
        } else {
            printf("[ %s ]", node -> process -> name);
        }
    } else {
            printf("[ NULL ]");
    }
    if (node -> next_node) {
        printf("-> ");
        print_node_chain(node -> next_node, states);
    } else {
        printf("\n");
    }
}
