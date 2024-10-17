#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>


int main(){
      
    pid_t p1 = fork();

    if (p1 < 0){
            fprintf(stderr, "Failed to create the process.\n");
            return 1;
  } else if (p1 == 0){
              printf("Child process's ID : %d", getpid());

              for (int i=1; i<=5; i++){
                           printf("\n%d",i); 
                           sleep(3);
              }
              printf("\n");
  } else { 
        printf("\nParent's ID : %d",getpid()); 
        wait(NULL); // This makes parent to wait for the child here.
        printf("\nParent is being executed from here onwards..");
  }


  return 0;
}
