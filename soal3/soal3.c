#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <limits.h>


pthread_t tid[500];
char keepFile[2000][2000];

// to check if the path is a regular file or not
int isRegular(const char *path){
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

// to categorize file 
void *pindahFile(void *arg){
  char str[999];
  char buffer[999];
  char buffer2[999];
  char buffer3[999];
  char path[1000];
  char tempDest[1000];
  char cwd[1000];
  char fileName[1000];
  char fileExt[1000];
    
  // get current working directory
  getcwd(cwd, sizeof(cwd));

  // get path from arg
  strcpy(path, (char*) arg);

  // check if path is a file or not
  int isFile = isRegular(path);

  // if file doesn't exist
  if(access(path, F_OK) == -1){
      // printf("File %s: Sad, gagal:(\n", tempCurr);
      // pthread_exit(0);
      return (void *) 0;
  }

  // if path is not a file
  if(!isFile){
    // printf("File %s: Sad, gagal:(\n", tempCurr);
    return (void *) 0;
    // pthread_exit(0);
  }

  // get file name
  strcpy(buffer, path);
  char *token=strtok(buffer, "/");
  while(token != NULL){
      sprintf(fileName, "%s", token);
      token = strtok(NULL, "/");
  }

  strcpy(buffer, path);
  strcpy(buffer2, fileName);
  strcpy(buffer3, fileName);

  int count = 0;

  
  // get file extension
  char *token2=strtok(buffer2, ".");
  // printf("%s", token2);
  while(token2 != NULL){
      count++;
      sprintf(fileExt, "%s", token2);
      token2=strtok(NULL, ".");
    }
    // printf("%s", fileExt);

  // if file is hidden or without extension
  char dot = '.';
  char first = buffer3[0];
    // printf("%c", buffer3[0]);
  if(dot == first){
    strcpy(fileExt, "hidden");
  }

  else if (count <=1 ){
    strcpy(fileExt, "unknown");
  }

  // if file extension is in uppercase
  for (int i = 0; i < sizeof(fileExt); i++){
      fileExt[i] = tolower(fileExt[i]);
  }

  strcpy(buffer, (char*) arg);
  mkdir(fileExt, 0777); // make folder

  strcat(cwd, "/");
  strcat(cwd,fileExt);
  strcat(cwd, "/");
  strcat(cwd, fileName);
  strcpy(tempDest, cwd);

    // printf("%s", fileExt);
    // printf("%s", fileName);
  // sprintf(tempDest, "%s/%s/%s", cwd, fileExt, fileName);
  rename(buffer, tempDest);
    // stcpy(str, argv);
    // printf("File %d: Berhasil dikategorikan\n", i);
  return (void *) 1;
    // pthread_exit(0);

}

// to list files recursively 
void listRecursive(char *basePath, int *iter)
{
    // int iter = 0;
  char path[1000];
  struct dirent *dp;
  DIR *dir = opendir(basePath);

  if (!dir){
      // printf("Directory tidak ada\n");
      // printf("%s", basePath);
      return;

  }

  while ((dp = readdir(dir)) != NULL)
  {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
      {
        // sprintf(keepFile[*iter], "%s/%s", dp->d_name);

        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp->d_name);

        if(isRegular(path)){
          // copy the file/path name to an array that will be used in the thread
          strcpy(keepFile[*iter], path); 
              // printf("%s\n", keepFile[*iter]);
          *iter = *iter + 1;
        }
        else{
          listRecursive(path, iter);
        }

      }
  }
    closedir(dir);
}


int main(int argc, char *argv[]) {

  void *status;
  int flag;
  char basePath[1000];

  if (argc == 1) {
    printf("Belum memasukkan argument.\n");
    exit(1);
  }
  if (strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "*") != 0 && strcmp(argv[1], "-d")) {
    printf("Argument tidak ada.\n");
    printf("Argument yang bisa diinput: -f, -d, *\n");
    exit(1);
  }

  if (strcmp(argv[1], "-f") == 0) {
    if (argc <= 2) {
      printf("Belum ada direktori yang diinput\n");
      exit(1);
    }

    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      pthread_create(&tid[i-2], NULL, pindahFile, (void *)argv[i]);
    }
    for (int i = 0; i < (argc-2); i++) {
      // status will hold the value returned from the thread
      pthread_join(tid[i], &status); 

      // cast status as integer (previously is a void ptr)
      flag = (int) status;

      // if flag holds a value from status --> file is successful at being categorized
      if(flag) printf("File %d: Berhasil Dikategorikan\n", i+1); 

      // if flag == 0 --> file is not successful at being categorized
      else printf("File %d: Sad, gagal:(\n", i+1);
    //   if(status==0) printf("wah bisa\n");
    }
    exit(0);
  }
  else{


  int iter = 0;
 
  if(strcmp(argv[1], "-d")==0){
      if(argc != 3){
          printf("Argument salah. Hanya bisa memasukkan 1 Direktori\n");
          exit(1);
      }
      strcpy(basePath, argv[2]);

      // call function to find all paths
      listRecursive(basePath, &iter);
      
      
      pthread_t tid[iter];
      flag = 0;

      for(int i = 0; i<iter; i++){
        // create thread for every process in pindahFile
        pthread_create(&tid[i], NULL, pindahFile, (void*)keepFile[i]);
      }

      for(int i = 0; i<iter; i++){
        pthread_join(tid[i], &status);

        // cast status as integer again 
        flag = (int) status;
      }
      if(flag) printf("Direktori sudah disimpan!\n");
      if(!flag) printf("Yah, gagal disimpan:(\n");
  }

    if(strcmp(argv[1], "*")==0){
      if (argc != 2) {
        printf("Argument salah.\n");
        exit(1);
      }

      // get current working directory path
      char cwd[1000];
      getcwd(cwd, sizeof(cwd));

      // copy path as basepath for listRecursive
      strcpy(basePath, cwd);
      listRecursive(basePath, &iter);

      pthread_t tid[iter];
      // flag = 0;

      for(int i = 0; i<iter; i++){
          // printf("%s", keepFile[i])
          pthread_create(&tid[i], NULL, pindahFile, (void*)keepFile[i]);

      }

        for(int i = 0; i<iter; i++){
          pthread_join(tid[i], &status);
          // flag = (int) status;
        }
      
    }
      // pthread_t tid[argc-2];
      // pthread_create(&tid[2], NULL,&listFilesRecursively, (void *)argv[2]);
      // pthread_join(tid[2], NULL);
      
      exit(0);

  }
}