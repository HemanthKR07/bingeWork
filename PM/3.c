#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<boolean.h>

#define MAX 5
#define IO 3
#define Time 3

typedef enum {
  READY,
  RUNNING,
  WAITING,
  TERMINATED 
},State;

typedef struct {
  int id,
  State state,
  int remain_time,
  int io_request
}, Process;


void printer(Process *process){
              printf("Process : %d", process->id);
              switch (process->state){
                      case READY : printf("READY\n"); break;
                      case WAITING : printf("WAITING\n"); break;
                      case RUNNING : printf("RUNNING\n"); break;
                      case TERMINATED : printf("TERMINATED\n");break;
              }
}





void scheduler(Process processes[], int max){

      int all_terminated = false;
      int io_count[max] = {0};

      while(!all_terminated){
              for (int i=0; i<max; i++){
                          if (processes[i].state == TERMINATED){
                                          continue;
                          }
                          all_terminated = false; 
                          
                          if (processes.state == READY){
                                        processes.state = RUNNING;
                                        printer(&process[i]);
                                        sleep(Time);
                                        processes[i].remain_time -= Time;

                                        if (processes[i].remain_time > 0 && processes[i].remain_time % IO == 0){
                                                        processes[i].io_request = 1;
                                                        processes[i].state = WAITING;
                                                        io_count[i] = remain_time;
                                                        printf("Process  %d has requested for IO op, will wait for %d", processes[i].id, processes[i].remain_time);
                                        } else if (processes[i].remain_time <=0){
                                                        processes[i].state = TERMINATED;
                                                        printf("Process %d Terminated", processes[i].id);
                                        }
                          }
                          if (processes.state == WAITING){
                                        io_count[i]--;
                                        if (io_count[i] <= 0){
                                                        processes[i].state = READY;
                                                        processes[i].io_request = 0;
                                                        printf("Process %d from WAITING to READY STATE.",processes[i].id);
                                        }
                          }
              }
      }
}

int main(){
      
  Process processes[MAX];

  for (int i=0; i<MAX; i++){
            processes[i].id = i + 1;
            processes[i].state = READY;
            processes[i].remain_time = 10;
            processes[i].io_request = 0;
}

scheduler(processes, MAX);

  return 0;
}
