#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// //######## PROCESS ############

// Process* process_init(int id, char* name, int nFabrica){
//     Process* process = calloc(1, sizeof(Process));
//     process -> id = id;
//     process -> name[255] = name;
//     process -> nFabrica = nFabrica;
//     process -> estado = 0;

//     return process;
// }
// void process_destroy(Process* process){
//     free(process);
// }

// //######## QUEUE ############

// Queue* queue_init(){
//     Queue* queue = calloc(1, sizeof(Queue));
//     queue -> line = calloc(8, sizeof(Process*));
//     queue -> cant_process = 0;
// }
// void queue_destroy(Queue* queue){
//     for (int p=0; p<queue->cant_process;p++){
//         process_destroy(queue->line[p]);
//     }
//     free(queue);
// }

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