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
                                char filename[20];
                                char newdata[100];
                                printf("\nEnter filename : ");
                                scanf("%s",filename);
                         
                                filesystem[i].data = malloc(100 * sizeof(char));
                                printf("\nEnter data : ");
                                
                               scanf("%s",newdata);
                               if (strlen(newdata)> 11){
                                          printf("\nData limit exceeding, enter data under the limit.");
                                          return;
                                }
                               strcpy(filesystem[i].filename, filename);
                               strcpy(filesystem[i].data, newdata);
                               printf("File %s created \n ",filename);
                      }
              }
        if (breaker == 0){
                printf("File system is FULL cannot add more files to it :(\n");
        } 
}

void addFile(int size){
        for (int i=0; i<size; i++){
                    if (filesystem[i].data == NULL){
                                        char filename[20];
                                        char newdata[100];
                                        printf("Enter filename : ");
                                        scanf("%s", filename);
                                        printf("\nEnter data : ");
                                        scanf("%s",newdata);
                                        if (strlen(newdata)>11){ 
                                                    printf("Data limit exceeding, enter data under the limit.");
                                                    return;
                                        }
                                        filesystem[i].data = malloc(100 * sizeof(char));
                                        strcpy(filesystem[i].filename,filename);
                                        strcpy(filesystem[i].data,newdata);
                                        printf("File add successfully.");
                                        return;               
                    }
        }
        printf("\nFile storage is Full, couldnt add the file.");
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
                            if (filesystem[i].filename != NULL && strcmp(filesystem[i].filename, filename)==0){
                                    free(filesystem[i].data);
                                    filesystem[i].data = NULL;
                                    printf("File %s deleted !\n",filename);
                                    return;
    }
  }
  printf("File missing :(\n");
}

void updateFiledata(int size){
        char filename[20];
        int breaker = 0;
      
        printf("Enter filename to update its data : ");
        scanf("%s",filename);
        char newdata[100];

        for (int i=0; i<size; i++){
                    if (strcmp(filesystem[i].filename, filename)==0){
                                          printf("Filename : %s \n Data : %s \n", filesystem[i].filename, filesystem[i].data);
                                          printf("Enter the new data : ");
                                          
                                          scanf("%s",newdata);
                                          if (strlen(newdata)>11){
                                                      printf("Data exceeding the limit, enter data under the limit.");
                                                      return;
                                          }
                                          strcpy(filesystem[i].data,newdata);
                                          printf("Data updated ! \n");
                                          breaker = 1;
                                          return;
    }
  } 
  if (breaker == 0){
            printf("Failed to update the data.");
  }
}

 void updateFilename(int size){
            char filename[10];
            printf("Enter the present filename to update : ");
            scanf("%s", filename);
            int breaker = 0;
            for (int i=0; i<size; i++){
                              if (strcmp(filesystem[i].filename,filename)==0){
                                              printf("File found ! \n");
                                              printf("Enter the newfile name : ");
                                              scanf("%s",filename);
                                              strcpy(filesystem[i].filename,filename);
                                              printf("\nUpdated the filename !\n");
                                              breaker = 1;
                                              return;
    }
  }
    if (breaker = 0){
            printf("\nFailed to update the filename.");
  }
}

void createDuplicateFile(int size){
          char filename[10];
          printf("\nEnter filename to copy : ");
          scanf("%s",filename);
          for (int i=0; i<size; i++){
                            if (strcmp(filesystem[i].filename, filename)==0){
                                                  int j=i+1;
                                                  while(filesystem[j].data != NULL){
                                                                      j += 1;
                                                  }
                                                  printf("File found !\nEnter filename for the duplicate file : ");
                                                  scanf("%s",filename);
                                                  strcpy(filesystem[j].filename,filename);
                                                  filesystem[j].data = malloc(100 * sizeof(char));
                                                  strcpy(filesystem[j].data, filesystem[i].data);
                                                  printf("File duplication successful !\n");
                                                  return;
                            }
           }
    printf("\nFailed to duplicate the file.");
}

void getStorageInfo(int size){
        int nfiles = 0;
        int dataSize = 0;

        for (int i=0; i<size; i++){
                    if (strlen(filesystem[i].filename) > 0){
                            nfiles += 1;
                            dataSize += strlen(filesystem[i].data);
                    }
        }
        printf("\nTotal number of files : %d",nfiles);
        printf("\nRemaining space (files) : %d", size - nfiles);
        printf("\nTotal characters of data in filesystem : %d",dataSize);
}



int main(){
  int filesystemSize;
  printf("Enter the file system size : ");
  scanf("%d",&filesystemSize);

  int size;
  printf("Enter the number of files you want to enter : ");
  scanf("%d",&size);

  if (filesystemSize < 0){
          exit(0);
  }  else if (filesystemSize > 50) {
            printf("Size belond the capacity !");
            exit(0);
  } else {
       init(filesystemSize);
       int choice = 1;
       createFiles(size);

        while (choice >= 0 && choice <= 7){
              
              printf("\nEnter 1 to add || 2 to read || 3 to delete || 4 to update data || 5 to update filename || 6 to duplicate a file || 7 for Storage info || 0 to exit: ");
              scanf("%d",&choice);
              if (choice == 1){
                        addFile(filesystemSize);
                        continue;
              } else if (choice == 2){
                          readFiles(filesystemSize);
                          continue;
              } else if (choice == 3){
                          deleteFiles(filesystemSize);
                          continue;
              } else if (choice == 4){
                          updateFiledata(filesystemSize);
                          continue;
              } else if (choice == 5){
                          updateFilename(filesystemSize);
                          continue;
              } else if (choice == 6){
                       createDuplicateFile(filesystemSize);
                        continue;
              } else if (choice == 7){
                        getStorageInfo(filesystemSize);
                        continue;
              } else if (choice == 0){
                        printf("File system exiting...");
                        exit(0);
              } else {
                          printf("invalid key !");
                          exit(0); 
             }
        }
  }
  return 0;
}
