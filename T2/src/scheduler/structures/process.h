#include "../../file_manager/manager.h"

//######## ENUM ############
typedef enum processStatus{
    RUNNING,
    READY,
    WAITING,
    FINISHED,
    UNBORN,
}ProcessStatus;

//######## PROCESS ############
typedef struct process{
    int id;
    char* name;
    int init_time;
    int nFabrica;
    ProcessStatus state;
    int total_bursts;       // N° total de bursts (I/O o CPU).
    int* burst_cum_times;   // Arreglo de largo total_bursts, con el tiempo acumulado de cada burst.
    int burst_cnt;          // Contador de bursts (I/O o CPU) terminados.
    int turnos_CPU;         // N° turnos en CPU.
    int interrupciones;     // N° de veces interrumpido por terminar quantum.
    int turnaround_time;    // N° turnos en el sistema (queue + CPU).
    int response_time;      // N° turnos hasta ser atendido por primera vez.
    int waiting_time;       // N° turnos en estado WAITING.
    int ready_time;         // N° turnos en estado READY.
} Process;

Process* process_init(int id, InputFile* input_file);
void change_state(Process* process, ProcessStatus state, int clock);
void process_destroy(Process* process);
// Recieves an ProcessStatus and returns the corresponding state as a string:
const char* int_to_state_string(ProcessStatus state);