// //######## ENUM ############
// typedef enum processStatus{
//     RUNNING,
//     READY,
//     WAINTING,
//     FINISHED
// }ProcessStatus;

// //######## PROCESS ############
// typedef struct process{
//     int id;
//     char* name;
//     int nFabrica;
//     ProcessStatus estado;
// } Process;

// Process* process_init(int id, char* name, int nFabrica);
// void change_state(Process* process, int state);
// void process_destroy(Process* process);

// //######## QUEUE ############

// typedef struct queue{
//     int cant_process;
//     Process** line;
// } Queue;

// Queue* queue_init();
// void queue_destroy(Queue* queue);
// int f_calculator(Queue* queue);
// int qi_calculator(int Q, Queue* queue, int fabrica, int f);
