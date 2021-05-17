# soal-shift-sisop-modul-3-F09-2021 #

### Anggota kelompok:
Anggota | NRP
------------- | -------------
Muthia Qurrota Akyun | 05111940000019
Ifanu Antoni | 05111940000064
Dyandra Paramitha W. | 05111940000119

### Soal
1. Belum mengerjakan no.1 
2. [File Soal 2](https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/tree/master/soal2) | [Penjelasan No. 2]
3. [File Soal 3](https://github.com/dydyandra/soal-shift-sisop-modul-3-F09-2021/tree/master/soal3) | [Penjelasan No. 3]


## Penjelasan No. 1


## Penjelasan No. 2


### a. 
### b. 


### c. 
### d. 


### e. 


### Output

### Kendala yang dialami

## Penjelasan No. 3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
Ada beberapa mode yang harus dibuat agar dapat menkategorikan file, yaitu -f, -d dan *. 

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


#### Saat mode -d
#### Saat mode *



### Kendala yang dialami
