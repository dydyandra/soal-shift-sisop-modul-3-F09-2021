#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define PORT 8080

void getData(int sock, char *buffer, char *cmd)
{
    memset(buffer,0,2048);
    memset(cmd,0,2048);
    for(int i = 0; i<2;i++)
    {
        read( sock , buffer, 2048);
        printf("%s\n",buffer );
        memset(buffer,0,2048);
        scanf("%s",cmd);
        send(sock , cmd , strlen(cmd) , 0 );
        memset(cmd,0,2048);
    }
}


  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }


    char cmd[2048];
    int menu = 1, loop = 0, auth = 0;
    // send(sock , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");
    while(1){


        if (menu){
            valread = read( sock , buffer, 1024);
            printf("%s\n",buffer );
            memset(buffer, 0, 2048);
        }
        menu = 1;

        memset(cmd, 0, sizeof(cmd));

        int count = 0;
        char *c, *d;

        char temp[2048] = {0}, fullCmd[1024] = {0}, file[1024] = {0};
        memset(fullCmd, 0, sizeof(fullCmd));
        scanf(" %[^\n]",fullCmd);
        // strcpy(temp, fullCmd);
        

        strcpy(temp, fullCmd);

        for(c=strtok_r(temp, " ", &d); c!=NULL; c=strtok_r(NULL, " ", &d)){
            if(count==0) strcpy(cmd, c);
            else if(count == 1) strcpy(file, c);

            count++;
        }


        send(sock, fullCmd, strlen(fullCmd), 0);
        int cmdsize=strlen(cmd);
        for(int i = 0; i<cmdsize; i++){
            cmd[i] = tolower(cmd[i]);
        }

        if((strcmp(cmd, "register")==0) && !auth){

            getData(sock, buffer, cmd);        

        }

        else if((strcmp(cmd, "login")==0) && !auth){

            getData(sock, buffer, cmd);    
            read(sock, &auth, sizeof(auth));    

        }

        else if ((strcmp(cmd, "exit")==0)) {
            printf("Disconnected\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        memset(cmd, 0, sizeof(cmd));
        

        

    }
    return 0;
}