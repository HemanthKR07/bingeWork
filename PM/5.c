// This is Round Robin Algorithm with Priority Queue

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

#define Time 3 


typedef struct {
    int id;
    int burst;
    int remain_time;
    int priority;
}Process;

//void scheduler(Process processes[]){
//  int process_completed = 0;
//  for (int i=0; i<10; i++){
//      if (processes[i].remain_time <= 0){
//                                if (i==9){
//                                       printf("\n----------------------------------------------------------------------------\n ALL PROCESSES TERMINATED."); 
//                                        return; 
//                                } else {
//                                      continue;
//                                }
//      } else {
//              if (processes[i].remain_time < Time && processes[i].remain_time > 0){
//                                          sleep(processes[i].remain_time);
//                                          printf("\nProcess %d :  Burst Time : %d  | Remaining Time : %d ", processes[i].id, processes[i].burst, processes[i].remain_time);
//                                          processes[i].remain_time = 0;
//                                          process_completed += 1;
//                                          printf("|  After processing : %d ", processes[i].remain_time);
//              } else {
//                                          sleep(Time);
//                                          printf("\nProcess %d :  Burst Time : %d  | Remaining Time : %d | After Processing : %d", processes[i].id, processes[i].burst, processes[i].remain_time, processes[i].remain_time-Time);
//                                          processes[i].remain_time -= Time;
//              }
//      }
//      if (i == 9){
//            printf("\n----------------------------------------------------------------------------");
//            if (process_completed == 10){
//                       return; 
//            } else if(process_completed <= 9){
//                       i = -1;
//            }
//    }
//}   
//    printf("\n-----------------------------------------------------------------------------\nALL PROCESSES TERMINATED...");





void scheduler(Process processes[]){
  int max = -1;
  int process_completed = 0;
  int index = -1;
  for (int i=0; i<10; i++){
          // This is to find the max element 
          for (int i=0; i<10; i++){
                      if (processes[i].remain_time <= 0){continue;}
                      else {
                            if (processes[i].priority > max){
                                      max = processes[i].priority;
                                      index = i;
                            }
                      }
          } 
          if (processes[index].remain_time < Time && processes[index].remain_time > 0){
                      sleep(processes[index].remain_time); 
                      printf("\nProcess %d : Priority : %d |  Burst Time : %d  | Remaining Time : %d | After Processing : 0", processes[index].id,processes[index].priority, processes[index].burst, processes[index].remain_time);
                      processes[index].remain_time = 0;
                      processes[index].priority = 0;
                      process_completed += 1;
                      max = -1;
          } else {
                      sleep(Time);
                      printf("\nProcess %d : Priority : %d |  Burst Time : %d  | Remaining Time : %d | After Processing : %d", processes[index].id,processes[index].priority, processes[index].burst, processes[index].remain_time, processes[index].remain_time-Time);
                      processes[index].remain_time -= Time;
                      if (processes[index].remain_time <= 0){processes[i].priority = 0; process_completed += 1;max = -1;}
          }
          if (process_completed == 10){
                     printf("\n",process_completed) ;
                     printf("\n------------------------------------------------------------------------------\n ALL PROCESSES TERMINATED...");
                     return;
          } else {
                     i=-1;
                     continue;
          }
  }
  
}

int main(){
     
  Process processes[10];

  for (int i=0; i<10; i++){
         processes[i].id = i + 1;
         processes[i].burst = processes[i].remain_time = rand() % 11;
         processes[i].priority = rand() % 11;
  }

scheduler(processes);
  return 0;
}
