//######## ENUM ############
typedef enum processStatus{
    RUNNING,
    READY,
    WAITING,
    FINISHED,
}ProcessStatus;

//######## PROCESS ############
typedef struct process{
    int id;
    char* name;
    int nFabrica;
    ProcessStatus state;
    int turnos_CPU;         // N° turnos en CPU
    int interrupciones;     // N° de veces interrumpido por terminar quantum
    int turnaround_time;    // N° turnos en el sistema (queue + CPU)
    int response_time;      // N° turnos hasta ser atendido
    int waiting_time;       // N° turnos en estado READY o WAITING
} Process;

Process* process_init(int id, char* name, int nFabrica);
void change_state(Process* process, int state, int clock);
void process_destroy(Process* process);
// Recieves an ProcessStatus and returns the corresponding state as a string:
const char* int_to_state_string(ProcessStatus state);