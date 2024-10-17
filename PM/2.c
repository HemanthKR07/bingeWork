#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){

  pid_t p1 = fork();


  if (p1 < 0){
          fprintf(stderr, " Failed to create a process.");
          return 1; 
  } else if (p1 > 0){
          printf("\n\nThis is parent process.."); 
          //sleep(3); 
          printf("\nParent Done.");
          wait(NULL);
  } else if (p1 == 0){
          printf("\nThis is child process..");
          printf("\nChild Done.");

  }
  return 0;
}
