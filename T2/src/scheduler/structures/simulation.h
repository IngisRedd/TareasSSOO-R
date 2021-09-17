#include "queue.h"
#include "../../file_manager/manager.h"

//######## SIMULATION ############

typedef struct simulation{
	Queue* queue;		// Process queue
	Process* CPU;  // Pointer to a Process runinng in the CPU
	int clock;	// Simulation clock
	int Q;			// Input Q value default = 100
	InputFile* input_file;		// Save pointer to input file data
	int np_cnt;			// new process counter
  int fp_cnt;     // finished process counter
	int* p_init_times;		// array with init_times of processes
	Process** all_processes; // array of pointers to all created processe. Lenght = input_file -> len.
	Process* new_processes[8]; // array of pointers to created processes in current step. 
} Simulation;

Simulation* simulation_init(int Q, InputFile* input_file);
void simulation_destroy(Simulation* simulation);
// Returns 1 if all processes have finished, or when clock > dev_mode:
int is_finished(Simulation* sim, int dev_mode);
// Creates a new process with its id:
Process* create_process_from_index(Simulation* sim, int index);
// Recieves an array of new processes and sorts it so they enter the queue right:
void sort_new_processes(Simulation* sim, int new_p_cnt);
// Deal with the process runing on the CPU on that step:
Process* manage_process_in_CPU(Simulation* sim);
// Enter the  new processes and the one from the CPU into the queue:
void enter_processes_into_queue(Simulation* sim, Process* p_from_CPU);
// Enter next process into CPU and set it to RUNNING:
void execute_next_process(Simulation* sim);
// Update process statistics:
void update_process_statistics(Simulation* sim);
// Update waiting process:
void update_waiting_process(Simulation* sim);
// Run one step of the simulation:
void simulation_step(Simulation* sim);
