#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void * printer(void * argument){
        printf("\nHello World");
        return NULL;
}



int main(){
      pthread_t thread1;

      pthread_create(&thread1,NULL, printer, NULL);
      pthread_join(thread1,NULL);
      return 0;
}
