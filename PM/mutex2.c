#include<stdio.h>
#include<pthread.h>

#define Size 10
#define thread_count 3

void sumFunction(void* threadHere){
  int thread_part = *(int*)threadHere;
  int start = thread_part * (Size / thread_count);
  int end = (thread_count + 1) * (Size / thread_count);

  for (int i=start; i<end; i++){
            sum[thread_part] += array[i];
  }
  pthread_exit(0);
}

int main(){
    
  pthread_t threads[thread_count];
  int thread_args[thread_count];

  for (int i=0; i<thread_count; i++){
      thread_args[i] = i;
      pthread_create(&theads[i],NULL, sumFunction, (void*)&thread_args[i]));
  }

  //This will wait for the threads
  for (int i=0; i<thread_count; i++){
      pthread_join(threads[i],NULL);
  }

  // Combine results
  int total_sum = 0;
  for (int i=0; i<thread_count; i++){
      total_sum += sum[i];
  }

  printf("Total sum : %d", total_sum);

  return 0;
}
