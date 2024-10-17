#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
#include<stdlib.h>

#define MAX 10

int main(){
    
  int pipeData[3];
  pid_t pid;

  if (pipe(pipeData) == -1){
         perror("Error at PIPE");
         return -1;
  }
  
  pid = fork();

  if (pid < 0){
          fprintf(stderr, "Error while creating the process");
          return -1;
  } else if (pid > 0){
          close(pipeData[0]);
          
          srand(time(NULL));

          for (int i=0; i<MAX; i++){
                    int random = rand() % 100;
                    write(pipeData[1],&random, sizeof(rand));
                    printf("\nParent : %d ", random);
                    sleep(2);
          }
          
          close(pipeData[1]);

  } else {
          close(pipeData[1]);
          
          for(int i=0; i<MAX; i++){
                    int data;
                    read(pipeData[0],&data, sizeof(data));
                    printf("\nChild : %d",data);
          }
          close(pipeData[0]);
  }

  return 0;
}
