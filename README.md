# soal-shift-sisop-modul-3-F09-2021 #

### Anggota kelompok:
Anggota | NRP
------------- | -------------
Muthia Qurrota Akyun | 05111940000019
Ifanu Antoni | 05111940000064
Dyandra Paramitha W. | 05111940000119

### Soal
2. [File Soal 2](https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/tree/master/soal2) | [Penjelasan No. 2]
3. [File Soal 3](https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/tree/master/soal3) | [Penjelasan No. 3]


## Penjelasan No. 1
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini. 

Di dalam proyek itu, Keverk diminta: 
### a. Membuat fitur register dan login. 
Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. 

### b. Membuat database files.tsv
Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. Folder FILES otomatis dibuat saat server dijalankan. 

### c. Membuat fitur menambah file baru
Client nanti akan melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru yang ditambahkan.

### d. Membuat fitur download
Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. 

### e. Membuat fitur menghapus file pada Server.
### f. Membuat fitur see dimana client bisa melihat semua files pada files.tsv
### g. Membuat fitur pencarian
### h. Membuat log 

## Penjelasan No. 2
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:

### a. Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. 
Pertama, mendeklarasikan variabel terlebih dahulu 
```
int matrixA[VER][HORX];
int matrixB[HORX][HOR];
int matrixC[VER][HOR];

struct args{
  int i;
  int j;
};
```
Kemudian menginputkan matriks 4x3 dN 3x6 menggunakan looping 
```
printf("Input Matrix 1:\n");
  for(int i = 0; i<VER; i++){
      for(int j = 0; j<HORX; j++){
          scanf("%d", &matrixA[i][j]);
      }
  }

  printf("Input Matrix 2:\n");
  for(int i = 0; i<HORX; i++){
      for(int j = 0; j<HOR; j++){
          scanf("%d", &matrixB[i][j]);
      }
  }
```
Matriks akan disimpan ke dalam struct, kemudian thread digunakan untuk menjalankan fungsi mult() untuk menghitung hasil perkalian dua matriks tersebut 
```
void *mult(void* arg){
  struct args *data = arg;

  int i = data->i;
  int j = data->j;

  for(int k=0; k<HORX; k++){
    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
  }

  pthread_exit(0);

}
```
Hasil dari perkalian dua matriks tersebut diprint 
```
void *mult(void* arg){
  struct args *data = arg;

  int i = data->i;
  int j = data->j;

  for(int k=0; k<HORX; k++){
    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
  }

  pthread_exit(0);

}
```
Mengalokasikan Shared Memory agar hasil dari perkalian matrix dapat digunakan pada soal b
```
  int shmid = shmget(key, sizeof(int)*VER*HOR, IPC_CREAT | 0666);
  val = shmat(shmid, 0, 0);
```

### Output
Menjalankan program dengan perintah berikut
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/gccsoal2.png">
Kemudian menginputkan matriks 4x3 dan matriks 3x6
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/soal2a.png">
Lalu akan ditampilkan hasil perkalian dari dua matriks tersebut
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/soal2a_2.png">

### b. Membuat program dengan menggunakan matriks output dari program sebelumnya (soal2a) dengan shared memory. 
Matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya (dari paling besar ke paling kecil)

Pertama, mendeklarasikan variabel terlebih dahulu 
```
int awal[VER][HOR];
int input[VER][HOR];
long long hasil[VER][HOR];

struct args{
  int i;
  int j;
};
```
Deklarasi untuk hasil perhitungan menggunakan long long karena untuk berjaga-jaga apabila hasil perhitungannya besar
Kemudian mengalokasikan Shared Memory lalu Meng-assign matriks dari Shared Memory kepada matrix A
```
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
```
Menginputkan matriks B
```
    printf("Input Matrix B:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            scanf("%d", &input[i][j]);
        }
    }
```
Kemudian thread dijalankan untuk memanggil fungsi banding()
```
pthread_create(&tid[i][j], NULL, banding, (void*)ind);
```
Di dalam fungsi banding() terdapat 3 case, yang pertama yaitu, apabila terdapat 0 maka hasilnya juga akan 0
```
            if(awal[i][j] == 0 || input[i][j] == 0){ 
                // hasil[i][j] = 0;
                hasil[i][j] = 0;
            }
```
Untuk case yang kedua, apabila matriks A lebih besar atau sama dengan matriks B, maka akan memanggil fungsi permutasi()
```
            else if(awal[i][j]>=input[i][j]){
                hasil[i][j] = permutasi(awal[i][j], input[i][j]);
            }
```
Untuk case yang ketiga, apabila matriks B lebih besar daripada matriks A, maka yang dipanggil adalah fungsi fact()
```
            else if (input[i][j] > awal[i][j]){
                hasil[i][j] = fact(awal[i][j]);
            }
```
Setelah itu, hasil perhitungan akan di print
```
    printf("Matrix hasil dari A & B:\n");
    for(int i = 0; i<VER; i++){
        for(int j = 0; j<HOR; j++){
            printf("%llu\t", hasil[i][j]);
        }
        printf("\n");
    }
```
Kemudian yang terakhir adalah menutup Shared Memory
```
    shmdt(val);
    shmctl(shmid, IPC_RMID, NULL);
```

### Output
Menjalankan program dengan perintah berikut
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/soal2b.png">
Kemudian menginputkan matriks B sehingga hasil perhitungannya sebagai berikut
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/soal2b_2.png">

### c. Mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” menggunakan IPC Pipes
Pertama memanggil pipe terlebih dahulu
```
    if(pipe1 == -1){
        perror("bad pipe1");
        exit(1);
    }
```
Kemudian memanggil fungsi yang menjalankan command pertama
```
    pid = fork();
    if(pid == -1){
        perror("fork1 error");
        exit(1);
    }
    else if(pid == 0){
        ps();
    }
```
Menjalankan command pertama yaitu `ps aux` untuk meng-list semua proses dan penggunaan status dan sumber daya
```
void ps(){

    // replace standard output with the writing end of pipe 1
    close(STDOUT);
    dup(fd1[1]);
    
    // close pipe
    close(fd1[0]);
    close(fd1[1]);

    // execute command ps
    command(1);
    
    //if execute doesn't work
    perror("could not execute ps");
    _exit(1);

}
```
Menjalankan command kedua yaitu `sort -nrk 3,3` untuk melakukan sort
```
void sortnrk(){
    
    //input from reading end of pipe 1
    close(STDIN);
    dup(fd1[0]);  

    // output to writing end of pipe 2
    close(STDOUT);
    dup(fd2[1]);

    // close pipe
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    // execute command sort
    command(2);

    // if execute doesn't work
    perror("could not execute sort -nrk 3,3");
    _exit(1);

}
```
Menjalankan command ketiga yaitu `head -5` untuk menampilkan 5 data teratas yang memakan resource 
```
void head(){

    // input from reading end of pipe 2
    close(STDIN);
    dup(fd2[0]);  

    // close pipe
    close(fd2[0]);
    close(fd2[1]);

    // execute command head -5
    command(3);

    // if execute doesn't work
    perror("could not execute head -5");
    _exit(1);

}
```

### Output
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal2/soal2c.png">

### Kendala yang dialami

## Penjelasan No. 3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
Ada beberapa mode yang harus dibuat agar dapat menkategorikan file, yaitu -f, -d dan *. 
Menjalankan command ketiga yaitu `sort -nrk 3,3`
```
void sortnrk(){
    
    //input from reading end of pipe 1
    close(STDIN);
    dup(fd1[0]);  

    // output to writing end of pipe 2
    close(STDOUT);
    dup(fd2[1]);

    // close pipe
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);

    // execute command sort
    command(2);

    // if execute doesn't work
    perror("could not execute sort -nrk 3,3");
    _exit(1);

}
```

### Untuk penyelesaian 3a,3b,3c ada 2 fungsi utama yang digunakan, yaitu untuk mengecek tipe file/direktori, dan untuk mengkategorikan file.
Untuk penyelesaian 3a,3b,3c ada 2 fungsi utama yang digunakan, yaitu untuk mengecek tipe file/direktori, dan untuk mengkategorikan file.

##### Fungsi untuk mengecek tipe file, apakah file merupakan file Regular atau tidak:
```c
int isRegular(const char *path){
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}
```
Untuk fungsi ini menggunakan *struct stat* yang berisi beberapa elemen. Untuk mengecek apakah file merupakan tipe reguler (bukan merupakan folder), menggunakan salah satu elemen *struct* yaitu st_mode. 

##### Fungsi untuk mengkategorikan file
```c
void *pindahFile(void *arg){
  char str[999];
  char buffer[999];
  char buffer2[999];
  char buffer3[999];
  char buffer4[999];
  char path[1000];
  char tempDest[1000];
  char cwd[1000];
  char fileName[1000];
  char fileExt[1000];
  char fileExt2[1000];

  getcwd(cwd, sizeof(cwd));
  strcpy(path, (char*) arg);
  int isFile = isRegular(path);

  if(access(path, F_OK) == -1){
      // printf("File %s: Sad, gagal:(\n", tempCurr);
      // pthread_exit(0);
      return (void *) 0;
  }

  if(!isFile){
    // printf("File %s: Sad, gagal:(\n", tempCurr);
    return (void *) 0;
    // pthread_exit(0);
  }

  strcpy(buffer4, path);

  char *fileExt3;
  char dot1 = '.';
  fileExt3 = strchr(buffer4, dot1);
  // printf("%s", fileExt3);

  strcpy(buffer, path);
  char *token=strtok(buffer, "/");
  while(token != NULL){
      sprintf(fileName, "%s", token);
      token = strtok(NULL, "/");
  }

  strcpy(buffer, path);
  strcpy(buffer2, fileName);
  strcpy(buffer3, fileName);
  // strcpy(buffer4, fileName);


  int count = 0;

  char *token2=strtok(buffer2, ".");
  // printf("%s", token2);
  sprintf(fileExt2, "%s", token2);

  
  while(token2 != NULL){
      count++;
      // printf("%d", count);
    //   printf("%s\n", token2);
      sprintf(fileExt, "%s", token2);
    //   printf("%s", fileExt);
      token2=strtok(NULL, ".");
    }
    // printf("%s", fileExt);
  char dot = '.';
  char first = buffer3[0];
//   printf("%s", fileExt2);
    // printf("%c", buffer3[0]);
  if(dot == first){
    strcpy(fileExt, "hidden");
  }

  else if(count >= 3){
    strcpy(fileExt, fileExt3+1);
  }

  else if (count <=1 ){
    strcpy(fileExt, "unknown");
  }

  for (int i = 0; i < sizeof(fileExt); i++){
      fileExt[i] = tolower(fileExt[i]);
  }

  strcpy(buffer, (char*) arg);
  mkdir(fileExt, 0777);

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
```
Beberapa hal yang dibutuhkan di dalam fungsi yaitu *path* *current working directory* dan *path* argumen yang diinputkan oleh User. 
- Yang pertama harus dilakukan yaitu mengecek apakah file dapat diakses, dan mengecek jenis tipe file atau bukan. 
```c
  getcwd(cwd, sizeof(cwd));
  strcpy(path, (char*) arg);
  int isFile = isRegular(path);

  if(access(path, F_OK) == -1){
      // printf("File %s: Sad, gagal:(\n", tempCurr);
      // pthread_exit(0);
      return (void *) 0;
  }

  if(!isFile){
    // printf("File %s: Sad, gagal:(\n", tempCurr);
    return (void *) 0;
    // pthread_exit(0);
  }
```
Apabila path ternyata tidak dapat diakses, dan/atau path ternyata bukan merupakan path *file* reguler, akan mengembalikan nilai 0 (untuk false) ke dalam fungsi *main*, dan keluar dari fungsi kategori. 

- Yang kedua yaitu untuk mendapatkan ekstensi yang akan digunakan sebagai nama folder. Dengan menggunakan *strchr*, akan mengembalikan nilai dimana "." pertama yang ditemukan akan dipotong. 
```c
  strcpy(buffer4, path);

  char *fileExt3;
  char dot1 = '.';
  fileExt3 = strchr(buffer4, dot1);
```

- Yang ketiga yaitu mendapatkan nama-nama file dengan melakukan *delimiter* "/". Untuk melakukan ini menggunakan *strtok*, dan *looping* untuk memotong string dan menghilangkan *delimiter*. 
```c
  strcpy(buffer, path);
  char *token=strtok(buffer, "/");
  while(token != NULL){
      sprintf(fileName, "%s", token);
      token = strtok(NULL, "/");
  }
 ```
 
 - Yang keempat yaitu untuk menghitung berapa kali kemunculan "." pada nama file (yang dihitung yaitu berapa banyak string yang telah displit), dan untuk mencari nama file sendiri tanpa adanya ekstensi. Untuk melakukan ini menggunakan *strtok*, dan *looping* untuk memotong string dan menghilangkan *delimiter*. Adapun menggunakan `count`` untuk menghitung kemunculan "." pada path/string. 
 ```c
  strcpy(buffer, path);
  strcpy(buffer2, fileName);
  strcpy(buffer3, fileName);
  // strcpy(buffer4, fileName);


  int count = 0;

  char *token2=strtok(buffer2, ".");
  // printf("%s", token2);
  sprintf(fileExt2, "%s", token2);

  
  while(token2 != NULL){
      count++;
      // printf("%d", count);
    //   printf("%s\n", token2);
      sprintf(fileExt, "%s", token2);
    //   printf("%s", fileExt);
      token2=strtok(NULL, ".");
    }
 ```
 - Mengecek file akan dimasukkan ke kategori mana. 
 ```c
  char dot = '.';
  char first = buffer3[0];

  if(dot == first){
    strcpy(fileExt, "hidden");
  }

  else if(count >= 3){
    strcpy(fileExt, fileExt3+1);
  }

  else if (count <=1 ){
    strcpy(fileExt, "unknown");
  }
```

Case default (dari looping saat memisahkan string dengan delimiter ".") yaitu apabila mengkategorikan file sesuai ekstensi dimana kemunculan "." hanya satu kali (misal: file `get.sh` akan dikategorikan ke folder yang bernama `sh`). 

Case pertama yaitu untuk mengkategorikan file-file *hidden* agar bisa masuk ke folder ``hidden``. Apabila terdapat "." pada index pertama (yang mengindikasi file-, fileExt (yang akan menyimpan nama folder) akan menyimpan "hidden" sehingga akan dibuat folder "hidden" untuk file-file berjenis *hidden*. 

Case kedua yaitu apabila kemunculan "." lebih dari 1 (count lebih dari sama dengan 3 dikarenakan yang dihitung banyak token bukan "."). Apabila ekstensi lebih dari 1, akan masuk ke folder dengan titik terdepan. fileExt akan menyimpan nilai pada langkah ke-2, dan membuatkan folder sesuai string yang didapat pada langkah ke-2. 

Case ketiga yaitu apabila tidak ada ekstensi (count kurang dari 1), sehingga fileExt akan menyimpan "unknown" sehingga akan dibuat folder "unknown" untuk file-file tanpa ekstensi. 

- Langkah kelima yaitu merubah ekstensi menjadi tidak *case sensitive* dengan cara menjadikan semua ekstensi *lower case*. 
```c

  for (int i = 0; i < sizeof(fileExt); i++){
      fileExt[i] = tolower(fileExt[i]);
  }
```

- Langkah keenam yaitu membuat folder (dengan menggunakan `mkdir`) dan melakukan pemindahan file dari path awal ke path baru. 
```c
 strcpy(buffer, (char*) arg);
  mkdir(fileExt, 0777);

  strcat(cwd, "/");
  strcat(cwd,fileExt);
  strcat(cwd, "/");
  strcat(cwd, fileName);
  strcpy(tempDest, cwd);

  rename(buffer, tempDest);
  return (void *) 1;

``` 
### Untuk nomor 3b, dan 3c juga menggunakan fungsi yang sama yaitu untuk melakukan *listing* file secara rekursif. 

```c
void listFilesRecursively(char *basePath, int *iter)
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
          strcpy(keepFile[*iter], path);
              // printf("%s\n", keepFile[*iter]);
          *iter = *iter + 1;
        }
        else{
          listFilesRecursively(path, iter);
        }

      }
  }
    closedir(dir);
}
```
Untuk fungsi sendiri didapatkan dari modul 2. Ada beberapa modifikasi yaitu untuk memasukkan setiap path ke dalam thread masing-masing, maka setiap path *file* akan disimpan ke dalam suatu array untuk digunakan lagi dalam fungsi `pindahFile`. 
```c
        if(isRegular(path)){
          strcpy(keepFile[*iter], path);
              // printf("%s\n", keepFile[*iter]);
          *iter = *iter + 1;
        }
```
Apabila path/direktori masih berupa folder, akan terus dilakukan rekursif hingga menemukan list path yang berupa *file* reguler. 

### a. Mengkategorikan file menggunakan mode -f, dimana pengguna bisa mengkategorikan file sesuai argumen path yang diinginkan. 
```c
  if (strcmp(argv[1], "-f") == 0) {
    if (argc <= 2) {
      printf("Argument salah. Kurang direktori\n");
      exit(1);
    }

    pthread_t tid[argc-2];
    for (int i = 2; i < argc; i++) {
      pthread_create(&tid[i-2], NULL, pindahFile, (void *)argv[i]);
    }
    for (int i = 0; i < (argc-2); i++) {
      pthread_join(tid[i], &status);
      flag = (int) status;
      if(flag) printf("File %d: Berhasil Dikategorikan\n", i+1);
      else printf("File %d: Sad, gagal:(\n", i+1);
    }
    exit(0);
  }
```

Apabila argumen yang diberikan oleh User yaitu -f dan argumen path yang sesuai, akan dimasukkan ke dalam thread, dan akan mengeksekusi fungsi `pindahFile` di atas (untuk mengkategori file). 

Sesuai dengan banyak thread, thread akan dijalankan secara bersamaan menggunakan pthread_join. Ada perbedaan pada `pthread_join` yaitu pada parameter kedua. Parameter kedua yaitu `status` yang bertipe pointer akan mengembalikan nilai 0 atau 1 dari fungsi `pindahFile`. Tujuannya adalah untuk mengetahui apakah file berhasil dikategorikan atau tidak. Apabila berhasil, akan mengembalikan nilai 1 dari fungsi `pindahFile` dan 0 jika gagal. Nilai yang didapat akan dicasting menjadi integer, dan kemudian apabila `flag = 1`, akan menghasilkan output bahwa file (sesuai index argumen) berhasil dikategorikan. Apabila tidak, akan menghasilkan output bahwa file gagal dikategorikan. 

### b. Mengkategorikan file menggunakan mode -d, dimana pengguna bisa mengkategorikan 1 direktori saja. 
```c
int iter = 0;

  if(strcmp(argv[1], "-d")==0){
      if(argc != 3){
          printf("Argument salah\n");
          exit(1);
      }
      strcpy(basePath, argv[2]);
      listFilesRecursively(basePath, &iter);


      pthread_t tid[iter];
      flag = 0;

      for(int i = 0; i<iter; i++){
          pthread_create(&tid[i], NULL, pindahFile, (void*)keepFile[i]);
      }

        for(int i = 0; i<iter; i++){
          pthread_join(tid[i], &status);
          flag = (int) status;
        }

      if(flag) printf("Direktori sudah disimpan!\n");
      if(!flag) printf("Yah, gagal disimpan:(\n");
  }
```
Apabila argumen yang diberikan oleh User yaitu -d dan argumen path yang sesuai yaitu hanya 1, yang pertama dilakukan yaitu memanggil fungsi ` listFilesRecursively` untuk melisting dan menyimpan setiap *path* file dalam array. Setelah itu, setiap elemen pada array akan dibuat thread untuk mengeksekusi fungsi `pindahFile` seperti pada 3a, dan sesuai dengan jumlah *path* pada array akan dijalankan secara paralel menggunakan `pthread_join`. Sama seperti 3a, parameter kedua yaitu `status` yang bertipe pointer untuk mengembalikan nilai 0 atau 1 untuk mengindikasi apakah direktori berhasil dikategorikan atau tidak. 

### c. Mengkategorikan file menggunakan \*, dimana pengguna bisa mengkategorikan semua file dalam *current working directory*
```c
  if(strcmp(argv[1], "*")==0){
      if (argc != 2) {
        printf("Argument salah\n");
        exit(1);
      }

      char cwd[1000];
      getcwd(cwd, sizeof(cwd));
      strcpy(basePath, cwd);
      listFilesRecursively(basePath, &iter);

      pthread_t tid[iter];
      flag = 0;

      for(int i = 0; i<iter; i++){
          // printf("%s", keepFile[i])
          pthread_create(&tid[i], NULL, pindahFile, (void*)keepFile[i]);
          pthread_join(tid[i], &status);

      }

    //   if(flag) printf("Direktori sudah disimpan!\n");
    //   if(!flag) printf("Yah, gagal disimpan:(\n");

    }
 ```
 Apabila argumen yang diberikan yaitu "\*" yang pertama dilakukan yaitu menyimpan *path* *current working directory* dikarenakan akan mengkategorikan file pada direktori yang sedang digunakan. Sama seperti nomor **3b**, akan memanggil `listFilesRecursively` terlebih dahulu untuk menyimpan setiap path file di dalam array, yang kemudian akan dibuat thread masing-masing untuk mengeksekusi fungsi `pindahFile`. Adapun kemudian thread akan dijalankan secara paralel untuk mengkategorikan file. 

### d. Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.
Untuk nomor **3d** sudah dijelaskan pada penjelasan fungsi `pindahFile` di atas, dimana terdapat beberapa case untuk menyimpan nilai ke dalam variable `fileExt`. 
### e. Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.
Sudah dijelaskan pada penjelasan *a, b, c*, dimana semua *path* akan dijadikan *thread* masing-masing, dan akan dieksekusikan secara paralel. 
### Output
#### Saat mode -f
Apabila memasukkan argumen path seperti di gambar akan memberikan output berikut. 
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/soal3outputf.png">

Isi folder apabila menjalankan program dengan mode -f. 
Folder kategori yang terbentuk yaitu sh (untuk path ke-2 yang berekstensi .sh) dan unknown (dikarenakan untuk path ke-1 tidak memiliki ekstensi)
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/soal3folderf.png">

#### Saat mode -d
Apabila memasukkan argumen path seperti di gambar akan memberikan output berikut. 
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/soal3outputd.png">

Isi folder apabila menjalankan program dengan mode -d. 
Yang memiliki ekstensi lebih dari 1, akan dikategorikan ke dalam folder sesuai dengan titik terdepan saja (seperti .tar.gz). 
Yang merupakan *file* hidden akan masuk ke dalam folder hidden, dan yang tidak memiliki ekstensi masuk ke dalam folder unknown. 
File yang dikategorikan juga telah didapatkan dari hasil rekursif pada path. 
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/soal3folderd.png">

Isi folder hidden: 

<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/folderhidden.png">

#### Saat mode *
Isi folder apabila menjalankan program dengan mode \*. 
Karena mengkategorikan file dalam current working directory, terlihat bahwa file-file seperti soal3.zip, dan soal3.c juga ikut terkategori pada folder sesuai dengan ekstensi. 
<img src="https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/blob/master/screenshot/soal3/soal3folderbintang.png">

### Kendala yang dialami
- Untuk mengeluarkan output "File %d: Berhasil Dikategorikan" dikarenakan membutuhkan index dari argumen. Ternyata untuk melakukan pthread_join bisa me-returnkan suatu nilai dari fungsi asalkan dalam tipe pointer. [Referensi](https://stackoverflow.com/questions/2251452/how-to-return-a-value-from-pthread-threads-in-c)
