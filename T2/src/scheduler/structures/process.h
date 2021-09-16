//######## ENUM ############
typedef enum processStatus{
    RUNNING,
    READY,
    WAINTING,
    FINISHED
}ProcessStatus;

//######## PROCESS ############
typedef struct process{
    int id;
    char* name;
    int nFabrica;
    ProcessStatus state;
} Process;

Process* process_init(int id, char* name, int nFabrica);
void change_state(Process* process, int state);
void process_destroy(Process* process);