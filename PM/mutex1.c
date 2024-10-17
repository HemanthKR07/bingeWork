#include<stdio.h>
#include<pthread.h>

int counter = 0;
pthread_mutex_t lock;

void * evenPrinter(void * threadHere){
          while (counter <= 10){
                      if (counter % 2 == 0){
                                  pthread_mutex_lock(&lock);
                                  printf("\n%d",counter); 
                                  counter++;
                                  pthread_mutex_unlock(&lock);
                      }
          }
          return NULL;
}

void * oddPrinter(void * threadHere){
          while(counter <= 10){
                      if (counter % 2 != 0){
                                    pthread_mutex_lock(&lock);
                                    printf("\n%d",counter);
                                    counter++;
                                    pthread_mutex_unlock(&lock);
                      }
          }
          return NULL;
}


int main(){

    pthread_t even_thread, odd_thread;
    
    pthread_mutex_init(&lock, NULL);

    pthread_create(&even_thread, NULL, evenPrinter, NULL);
    pthread_create(&odd_thread, NULL, oddPrinter, NULL);

    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    pthread_mutex_destroy(&lock);


    return 0;
}
