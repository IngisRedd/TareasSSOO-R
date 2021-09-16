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
} Process;

Process* process_init(int id, char* name, int nFabrica);
void change_state(Process* process, int state, int clock);
void process_destroy(Process* process);
const char* int_to_state_string(ProcessStatus state);