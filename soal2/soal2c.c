#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define STDIN 0
#define STDOUT 1


int fd1[2];
int fd2[2];

void command(int n){
    if (n==1){
        char *ps[] = {"ps", "aux", NULL};
        execv("/bin/ps", ps);
    }

    else if(n==2){
        char *sort[] = {"sort", "-nrk", "3,3", NULL};
        execv("/bin/sort", sort);
    }

    else if (n==3){
        char *head[] = {"head", "-5", NULL};
        execv("/bin/head", head);
    }
}

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

int main(){
    int pid;
    
    int pipe1 = pipe(fd1);
    if(pipe1 == -1){
        perror("bad pipe1");
        exit(1);
    }

    // fork to execute ps
    pid = fork();
    if(pid == -1){
        perror("fork1 error");
        exit(1);
    }
    else if(pid == 0){
        ps();
    }

    int pipe2 = pipe(fd2);
    if(pipe2 == -1){
        perror("bad pipe2");
        exit(1);
    }

    // fork to sort
    pid = fork();
    if(pid == -1){
        perror("fork2 error");
        exit(1);
    }
    else if (pid == 0){
        sortnrk();
    }

    close(fd1[0]);
    close(fd1[1]);

    // fork to execute head -5
    pid = fork();
    if(pid == -1){
        perror("fork3 error");
        exit(1);
    }
    else if (pid == 0){
        head();
    }

    // close unused
    close(fd2[0]);
    close(fd2[1]);
    close(fd1[0]);
    close(fd1[1]);

    return 0;

}



