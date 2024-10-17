#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/wait.h>


int main(int argc, char *argv[]){
    
  for (int i=1; i<argc; i++){
        pid_t pid = fork();
        
        if (pid == 0){
              char *cmd[] = {argv[i],NULL};
              execv(argv[i],cmd);
              printf("\nExecuting the command...");
              perror("\nExecution failed.");
    }
  } 
  printf("Executed the commands, waiting for the parent now.");

  return 0;
}
