// This is a very basic file structure just like an array of structures.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MaxFname 10

typedef struct file_struct{ 
        char filename[MaxFname];
        char* data;
} File;

File* filesystem;

void init(int size){
      filesystem = malloc(size * sizeof(File));
      for (int i=0; i<size; i++){
              strcpy(filesystem[i].filename,"");
              filesystem[i].data = NULL;
      }
}


void createFiles(int size){
              int breaker = 0;
              for (int i=0; i<size; i++){
                       if (filesystem[i].data == NULL){
                                breaker = 1;
                                char filename[10];
                                printf("\nEnter filename : ");
                                scanf("%s",filename);
                         
                                filesystem[i].data = malloc(100 * sizeof(char));
                                printf("\nEnter data : ");
                  
                               strcpy(filesystem[i].filename, filename);
                               scanf("%s", filesystem[i].data);
                         
                               printf("File %s created \n ",filename);
                      }
              }
        if (breaker == 0){
                printf("File system is FULL cannot add more files to it :(\n");
        } 
}

void readFiles(int size){
          char filename[20];
          printf("Enter filename to read : ");
          scanf("%s",filename);
          for (int i=0; i<size; i++){
                      if (filesystem[i].data!=NULL && strcmp(filesystem[i].filename,filename)==0){
                                      printf("Filename : %s\n",filesystem[i].filename);
                                      printf("Data : %s\n",filesystem[i].data);
                                      return;
    }
  }
  printf("File not found :(\n");
}

void deleteFiles(int size){
            char filename[10];
            printf("Enter filename to delete : ");
            scanf("%s",filename);
                     for (int i=0; i<size; i++){ 
                            if (strcmp(filesystem[i].filename, filename)==0){
                                    free(filesystem[i].data);
                                    filesystem[i].data = NULL;
                                    printf("File %s deleted !\n",filename);
                                    return;
    }
  }
  printf("File missing :(\n");
}

int main(){

  int size;
  printf("Enter the number of files : ");
  scanf("%d",&size);

  if (size < 0){
          exit(0);
  }  else if (size > 50) {
            printf("Size belond the capacity !");
            exit(0);
  } else {
       init(size);
       int choice = 1;
  
        while (choice >= 1 && choice <= 3){
              
              printf("Enter 1 to add || 2 to read || 3 to delete : ");
              scanf("%d",&choice);
              if (choice == 1){
                        createFiles(size);
                        continue;
              } else if (choice == 2){
                          readFiles(size);
                          continue;
              } else if (choice == 3){
                          deleteFiles(size);
                          continue;
             } else {
                          printf("invalid key !");
                          exit(0); 
            }
  }
  }
  return 0;
}
