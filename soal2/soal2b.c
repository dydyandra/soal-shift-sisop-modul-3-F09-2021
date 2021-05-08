#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define VER 4
#define HOR 6
// #define MAX_SIZE 4*6

int awal[VER][HOR];
int input[VER][HOR];
long long hasil[VER][HOR];


struct args{
  int i;
  int j;
};

// factorial function
long long fact(long long n) {
    if (n == 0) return 1 ;
    return n * fact(n - 1) ;
}

// permutation function
long long permutasi(int n,int r) {
   return fact(n)/fact(n-r);
}


// comparing matrix A with matrix B
void *banding(void *arg){
    struct args *data = arg;

    int i = data->i;
    int j = data->j;

    for(int n = 0; n<VER; n++){
        for(int m = 0; m<HOR; m++){
            // case 1: if 0 --> 0
            if(awal[i][j] == 0 || input[i][j] == 0){ 
                // hasil[i][j] = 0;
                hasil[i][j] = 0;
            }

            // case 2: if (a>=b) --> a!/(a-b)!
            else if(awal[i][j]>=input[i][j]){
                hasil[i][j] = permutasi(awal[i][j], input[i][j]);
            }

            // case 3: if (b>a) --> a!
            else if (input[i][j] > awal[i][j]){
                hasil[i][j] = fact(awal[i][j]);
            }

            // else{
            //     hasil[i][j] = 0;
            // }
        }
    }
        
}

int main(){

    int k, m;
    int counter = 0;

    // get matrix A from 2a using shared memory
    pthread_t tid[VER][HOR];
    key_t key = 1199;
    int *val;
    int shmid = shmget(key, sizeof(int)*VER*HOR, IPC_CREAT | 0666);
    val = shmat(shmid, 0, 0);

    printf("Matrix A:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            printf("%d\t", val[i*HOR + j]);
            awal[i][j] = val[i*HOR + j];
        }
        printf("\n");
    }

    // scan new matrix
    printf("Input Matrix B:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            scanf("%d", &input[i][j]);
        }
    }

    // print new matrix
    printf("Matrix B:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            printf("%d\t", input[i][j]);
        }
        printf("\n");
    }


//   tid = (pthread_t*) malloc (sizeof(pthread_t) * argc) ;
    // creating thread for every calculation in the matrix
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
        
            struct args *ind = (struct args *)malloc(sizeof(struct args));

            ind->i=i;
            ind->j=j;

            pthread_create(&tid[i][j], NULL, banding, (void*)ind);
        // counter++;
        }
    }

    
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            pthread_join(tid[i][j], NULL);
        }
    // printf("\n");
    }

    printf("Matrix hasil dari A & B:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            printf("%llu\t", hasil[i][j]);
        }
        printf("\n");
    }

    shmdt(val);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;


}
