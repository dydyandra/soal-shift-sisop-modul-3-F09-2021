#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define VER 4
#define HORX 3
#define HOR 6


int matrixA[VER][HORX];
int matrixB[HORX][HOR];
int matrixC[VER][HOR];

struct args{
  int i;
  int j;
};

void *mult(void* arg){
  struct args *data = arg;

  int i = data->i;
  int j = data->j;

  for(int k=0; k<HORX; k++){
    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
  }

  pthread_exit(0);

}

int main(){

  for(int i = 0; i<VER; i++){
      for(int j = 0; j<HORX; j++){
          scanf("%d", &matrixA[i][j]);
      }
  }


  for(int i = 0; i<HORX; i++){
      for(int j = 0; j<HOR; j++){
          scanf("%d", &matrixB[i][j]);
      }
  }

  // for(int i = 0; i<VER; i++){
  //   for(int j = 0; j<HORX; j++){
  //     printf("%d\t", matrixA[i][j]);
  //   }
  //   printf("\n");
  // }

  pthread_t tid[VER*HOR];
  key_t key = 1199;
  int *val;
  
  struct args *data = (struct args *)malloc(sizeof(struct args));
  int counter = 0;
  for(int i = 0; i<VER; i++){
    for(int j = 0; j<HOR; j++){

      struct args *ind = (struct args *)malloc(sizeof(struct args));

      ind->i=i;
      ind->j=j;

      pthread_create(&tid[counter], NULL, mult, (void*)ind);
      counter++;
    }
  }


  for(int i = 0; i<VER*HOR; i++){
      pthread_join(tid[i], NULL);

  }


  for(int i = 0; i<VER; i++){
    for(int j = 0; j<HOR; j++){
      printf("%d\t", matrixC[i][j]);
    }
    printf("\n");
  }

  int shmid = shmget(key, sizeof(int)*VER*HOR, IPC_CREAT | 0666);
  val = shmat(shmid, 0, 0);

  
  for(int i = 0; i<VER; i++){
    for(int j = 0; j<HOR; j++){
      val[i*HOR + j] = matrixC[i][j];
      // printf("%d", val[i*HOR+j]);
    }
    // printf("\n");
  }

  // shmdt(val);
  // shmctl(shmid, IPC_RMID, NULL);

  return 0;

}






