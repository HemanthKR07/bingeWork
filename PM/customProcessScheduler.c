#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>

#define Time 3

typedef struct {
    int id;
    int burst_time;
    int remain_time;
    int priority;
    time_t arrival_time;
    time_t completion_time;
    double turnaround;
} Process;



void init(int size, Process processes[]){
   for (int i=0; i<size; i++){
          processes[i].id = i+1;
          processes[i].burst_time = processes[i].remain_time =  rand() % 11;
          processes[i].priority = rand() % size;
          time(&processes[i].arrival_time);
  } 
}

void printer(int size, Process processes[]){
    for (int i=0; i<size; i++){
            printf("Process : %d || Burst Time : %d || Remaining Time : %d || Arrival Time : %ld || Priority : %d  \n" , processes[i].id, processes[i].burst_time, processes[i].remain_time,processes[i].arrival_time, processes[i].priority);
  }
}


void runfcfs(int size, Process processes[]){
    for (int i=0; i<size; i++){
            if (processes[i].remain_time > 0){
                        sleep(processes[i].remain_time);
                        processes[i].remain_time = 0;  
                        time(&processes[i].completion_time);
                        processes[i].turnaround = difftime (processes[i].completion_time , processes[i].arrival_time);
                        printf("\nProcess : %d | Burst : %d | Remain : %d | Arrival Time : %ld | Completion Time : %ld | Priority : %d | Turnaround : %.2f ", processes[i].id, processes[i].burst_time,processes[i].remain_time, processes[i].arrival_time, processes[i].completion_time ,processes[i].priority, processes[i].turnaround);
            } else {continue;}
    } 
  printf("\nAll process executed !");
  return;
}

void runroundrobin(int size, Process processes[], int processCompleted){
      while(processCompleted < size){
                  for (int i=0; i<size; i++){
                                  if (processes[i].remain_time <=0){
                                            processCompleted += 1;
                                            if (processCompleted == size){
                                                        printf("\nAll process executed !"); 
                                                        return;
                                            } else {
                                                        continue;
                                            }
                                  } else {
                                            if (processes[i].remain_time > 0 && processes[i].remain_time <= 3){
                                                                      sleep(processes[i].remain_time);
                                                                      time(&processes[i].completion_time);
                                                                      processes[i].turnaround = difftime(processes[i].completion_time, processes[i].arrival_time);
                                                                      printf("\nProcess : %d | Burst : %d | Remain : %d | Arrival Time : %ld | Completion Time : %ld | Priority : %d | Turnaround : %.2f ", processes[i].id, processes[i].burst_time,processes[i].remain_time, processes[i].arrival_time, processes[i].completion_time ,processes[i].priority, processes[i].turnaround);
                                                                      processes[i].remain_time = 0;
                                                                      processCompleted += 1;
                                                                      if (processCompleted == size){
                                                                                  printf("\nAll process executed !"); 
                                                                                  return;
                                                                      }
                                            } else {
                                                                      sleep(Time);
                                                                      processes[i].remain_time -= Time;
                                                                   //   printf("\nProcess : %d | Burst Time : %d | Remain Time : %d | Priority : %d ", processes[i].id, processes[i].burst_time, processes[i].remain_time, processes[i].priority);
                                            }
                                  }
                  }
                  if (processCompleted == size){  
                                      printf("\nAll process executed !");
                                      return; 
                  }
      }
}

void runPriority(int size, Process processes[]){
          int processCompleted = 0; 
          while(processCompleted < size){
                            int max = -1;
                            int index = -1;
                             for (int i=0; i<size; i++){
                                                if(processes[i].priority > max){    
                                                                    max = processes[i].priority;
                                                                    index = i;
                                                }
                            }
                            if(processes[index].remain_time > 0){ 
                                       sleep(processes[index].remain_time);
                                       time(&processes[index].completion_time);
                                       processes[index].turnaround = difftime(processes[index].completion_time, processes[index].arrival_time);
                                       processes[index].remain_time = 0;
                                       processCompleted += 1;
                                        printf("\nProcess : %d | Burst : %d | Remain : %d | Arrival Time : %ld | Priority : %d", index+1, processes[index].burst_time,processes[index].remain_time, processes[index].arrival_time, processes[index].priority);
                                       processes[index].priority = -1;
                            } else {
                                      processes[index].priority = -1;
                                      processCompleted += 1;
                            }
          }
          printf("\nAll process executed !");
}
;

void runmultilevel(int size, Process processes[]){
        int countsize = size;
        Process q1[size/3];  // Shortest Job First
        countsize -= size/3;
        Process q2[size/3];  // Round Robin
        countsize -= size/3;
        Process q3[countsize]; // First Come First Serve
 

// This will sort my array.
        int counter = 0;
        Process temp;
        while (counter < size-1){
                  for (int i=counter+1; i<size; i++){
                              if (processes[i].remain_time < processes[counter].remain_time){
                                                temp = processes[i];
                                                processes[i] = processes[counter];
                                                processes[counter] = temp;
                              }
                  } counter++;
  }
// Adding ptocesses to the multilevel queues 
        int i=0;
        while (i<size){
                  if(i<(size/3)){
                            for(int j=0; j<size/3; j++){
                                       q1[j] = processes[i];
                                       i++;
                            }
                  } else if (i >= size/3 && i < (size*2)/3){
                            for (int k=0; k<size/3; k++){
                                       q2[k] = processes[i];
                                       i++; 
                            }
                  } else if (i>=((size*2)/3)){
                            for (int l=0; l<=countsize; l++){
                                       q3[l] = processes[i];
                                       i++;
                            }
                  }  
        }
  // Multilevel Queue Execution starts from here.
// 1. This is shortest job first.
  printf("\nRunning SJF.."); 
  for (int i=0; i<(size/3); i++){
                sleep(q1[i].remain_time);
                q1[i].remain_time = 0;
                time(&q1[i].completion_time);
                q1[i].turnaround = difftime(q1[i].completion_time, q1[i].arrival_time);
                printf("\nQ1 : Process : %d || Burst : %d || Remain : %d || Arrival Time : %ld || Completion Time : %ld || Priority : %d || Turn Around : %ld ", q1[i].id, q1[i].burst_time, q1[i].remain_time, q1[i].arrival_time, q1[i].completion_time,q1[i].priority, q1[i].turnaround);
  }

  // 2. This is round robin
  printf("\nRunning RR.."); 
  int processCompleted = 0;
  int breaker = 0;
  int threshold = ((size * 2) / 3);
  while(processCompleted < threshold){
              for (int i=0; i < (size/3); i++){
                         if (breaker == 1){break;} else {
                                      if(q2[i].remain_time <= 0){
                                                      processCompleted += 1;
                                                      if (processCompleted == threshold){
                                                               break;
                                                               breaker = 1;
                                                      } else {
                                                               continue;
                                                      }
                                      }else {
                                                if (q2[i].remain_time > 0 && q2[i].remain_time <=3){
                                                                      sleep(q2[i].remain_time);
                                                                      time(&q2[i].completion_time);
                                                                      q2[i].turnaround = difftime(q2[i].completion_time, q2[i].arrival_time);
                                                                      q2[i].remain_time = 0;
                                                                      printf("\nQ2 : Process : %d || Burst : %d || Remain : %d || Arrival Time : %ld || Completion Time : %ld || Priority : %d ||  Turn Around : %ld || ", q2[i].id, q2[i].burst_time, q2[i].remain_time, q2[i].arrival_time, q2[i].completion_time,q2[i].priority, q2[i].turnaround);
                                                                      processCompleted += 1;
                                                  } else {
                                                                      sleep(Time);
                                                                      q2[i].remain_time -= Time;
                                                                 //     printf("\nQ1 : Process : %d || Burst : %d || Remain : %d || Arrival Time : %ld || Completion Time : %ld || Priority : %d ||  Turn Around : %ld || ", q2[i].id, q2[i].burst_time, q2[i].remain_time, q2[i].arrival_time, q2[i].completion_time, q2[i].turnaround);
                                                }
                                      } 
                                      if (processCompleted == threshold){breaker = 1; break;} }
              }
              if (breaker == 1){
                        break;
              }
  }


  // This is first come first serve queue.
      printf("\nRunning FCFS.."); 
      int processCount = 0;
      while(processCount < countsize){
                      time_t min = 999;
                      int index = -1;
                      for(int i=0; i<countsize; i++){
                                        if (q3[i].remain_time <= 0){
                                                        processCount += 1;
                                                        if (processCount == countsize){
                                                                        printf("\nAll process executed.");
                                                                        return;
                                                        } else {
                                                                        continue;
                                                        }
                                        } else {
                                                        if (q3[i].arrival_time < min){
                                                                          min = q3[i].arrival_time;
                                                                          index = i;
                                                        }
                                        }
                      } 
                      if(index == -1){
                                      continue;
                      } else {
                                      sleep(q3[index].remain_time);
                                      q3[index].remain_time = 0;
                                      time(&q3[index].completion_time);
                                      processCount += 1;
                                      q3[index].turnaround = difftime(q3[index].completion_time, q3[index].arrival_time);
                                      printf("\nQ3 : Process : %d || Burst : %d || Remain : %d || Arrival Time : %ld || Completion Time : %ld || Priority : %d ||  Turn Around : %ld ", q3[index].id, q3[index].burst_time, q3[index].remain_time, q3[index].arrival_time, q3[index].completion_time, q3[index].turnaround);
                      }
      }
}


int main(){
  int size;
  printf("Enter the number of process you want : ");
  scanf("%d",&size);
  Process processes[size];
  int processCompleted = 0;
  init(size, processes); 
  printer(size,processes);


  int choice = 1;

  while(choice > 0 && choice <=3){
            printf("\nEnter 1 for FCFS || 2 for RR || 3 for Priority || 4 for Multilevel : ");
            scanf("%d",&choice);
            switch(choice){
            case(1): 
                  printf("\n Executing FCFS now !");
                  runfcfs(size, processes);
                  continue;
            case(2):
                  printf("\nExecuting rr now !");
                  runroundrobin(size, processes, processCompleted);
                  continue;
            case(3):
                  printf("\nExecuting Priority Scheduler");
                  runPriority(size, processes);
                  continue;
            case(4):
                  printf("\nExecuting Multilevel Queue Scheduler");                      
                  runmultilevel(size, processes);
                  continue;
            default:
                  printf("\nInvalid choice !");
                  exit(0); 
            }
 }

  return 0;
}
