#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <errno.h> 
#include <stdbool.h>
#include <ctype.h>
#define PORT 8080

int doRegister(int sock){
    char msg[20] = {0};
    char usr[50] = {0};
    char pwd[50] = {0};

    char *insertUser = "Insert Username: ";
    char *insertPwd = "Insert Password: ";
    int valread;

    char usrData[4096];
    for(int i = 0; i<2; i++){
        if(i == 0) strcpy(msg, insertUser);
        else if(i==1) strcpy(msg, insertPwd);

        send(sock, msg, strlen(msg), 0);
        memset(msg, 0, sizeof(msg));

        if(i == 0){
            valread = read(sock, usr, 50);
        }
        else valread = read(sock, pwd, 50);

        if(!valread) return -1;
    }


    sprintf(usrData, "%s:%s\n", usr, pwd);

    char cwd[4096], usrPath[4096];
    getcwd(cwd, sizeof(cwd));

    strcpy(usrPath, cwd);
    strcat(usrPath, "/");
    strcat(usrPath, "akun.txt");
    
    FILE *fPtr;

    fPtr = fopen(usrPath, "a");

    fputs(usrData, fPtr);
    fclose(fPtr);

    return 1;
}

int doLogin(int *flag, int sock, char *Username, char *Password){
    char msg[20] = { 0 };
    char usr[50] = {0};
    char pwd[50] = {0};
    
    char *insertUser = "Insert Username: ";
    char *insertPwd = "Insert Password: ";
    int valread;
    char usrData[4096];
    char cwd[4096];
    for(int i = 0; i<2;i++)
    {
        if(i == 0) strcpy(msg, insertUser);
        else if(i==1) strcpy(msg, insertPwd);

        send(sock, msg , strlen(msg),0);
        memset(msg,0,sizeof(msg));
        if(!i) 
        {
            valread = read(sock , usr , 50);
        }
        else valread = read(sock , pwd , 50);

        if(!valread) return -1;
    }

    sprintf(usrData,"%s:%s\n",usr,pwd);
    //printf("%s\n",namePass);


    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return -1;
    }

    char usrPath[4096];
    strcpy(usrPath, cwd);
    strcat(usrPath, "/");
    strcat(usrPath, "akun.txt");

    FILE * fPtr;

    fPtr = fopen(usrPath, "r");

    if(fPtr == NULL)
    {
        printf("Unable to create file.\n");
        return -1;
    }

    char *data;
    size_t len = 0;
    while ((getline(&data, &len, fPtr)) != -1) {

        if(!strcmp(data,usrData))
        {

            *flag = 1;
            strcpy(Username,usr);
            strcpy(Password,pwd);
        }
    }

    memset(usrPath,0,sizeof(usrPath));
    fclose(fPtr);

    return 1;
}

void *connection_handler(void *socket_desc){
    // puts("Connection accepted\n");
    int sock = *(int*)socket_desc;
    char *init = "Login or Register or Exit";
    char *message;
    char* clientmsg[2000];
    char *cmd[2048];
    char *a, *b;
    char regMessage[4096];
    char *regStatus = "Sukses!";
    int status_read;
    int auth = 0;
    char Username[4096], Password[4096];
    char loginMsg[4096];
    char *LoggedIn = "Add or Download or Delete or See or Find or Exit";
    // init = "Login or Register or Exit";

    
    char fullCmd[2048] = {0};

    memset(cmd, 0, sizeof(cmd));
    memset(fullCmd, 0, sizeof(fullCmd));
    send(sock, init, strlen(init), 0);
    while((status_read = read(sock, fullCmd, 2048)) > 0)
    {
        int count = 0;
        char *a, *b;

        char temp[2048]={0}, cmd[1024]={0}, file[1024]={0};
        // memset(temp, 0, sizeof(temp));
        // memset(cmd, 0, sizeof(cmd));
        // memset(file, 0, sizeof(file));

        strcpy(temp, fullCmd);

        for(a=strtok_r(temp, " ", &b); a!=NULL; a=strtok_r(NULL, " ", &b)){
            if(count==0) strcpy(cmd, a);
            else if(count == 1) strcpy(file, a);

            count++;
        }

        int cmdsize=strlen(cmd);
        for(int i = 0; i<cmdsize; i++){
            cmd[i] = tolower(cmd[i]);
        }
        
        if (!auth){
            if(strcmp(cmd, "register") == 0){
                if(doRegister(sock)>0){
                    strcpy(regMessage, regStatus);
                    strcat(regMessage, "\n\n");
                    strcat(regMessage, init);
                    send(sock, regMessage, strlen(regMessage), 0);
                }

                else {
                    status_read = 0;
                    break;
                }
            

            }
                else if(strcmp(cmd, "login") == 0){
                if(doLogin(&auth,sock,Username,Password) > 0){
                    int login_status = 1;
                    send(sock, &login_status, sizeof(login_status), 0);
                    char *loginStatus = "Welcome!";
                    strcpy(loginMsg, loginStatus);
                    strcat(loginMsg, "\n\n");
                    strcat(loginMsg, LoggedIn);
                }
                else{
                    int login_status = 0;
                    send(sock, &login_status, sizeof(login_status), 0);
                    char *loginFail = "Username or Password is Incorrect";
                    strcpy(loginMsg, loginFail);
                    strcat(loginMsg, "\n\n");
                    strcat(loginMsg, init);
                }
                send(sock, loginMsg, strlen(loginMsg), 0);
            }


        }
        else if (strcmp(cmd, "exit") == 0){
            status_read = 0;
            break;
        }

        else{
            char *notFound = "Invalid command";
            char invalid[4096];
            sprintf(invalid, "%s\n\n%s", notFound, init);
            send(sock, invalid, strlen(invalid), 0);
        }

            memset(cmd,0,sizeof(cmd));
            memset(fullCmd,0,sizeof(fullCmd));
    }

    if(status_read == 0){
        puts("Client has disconnected");
        fflush(stdout);
    }

    free(socket_desc);

    return 0;
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    // char *hello = "Hello from server";
    char *message;
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))){
        

        pthread_t sniffer_thread;
		int *new_sock = malloc(sizeof(int));
		*new_sock = new_socket;
		
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}

        pthread_join(sniffer_thread, NULL);
        // puts("Sukses");

    }

    if((new_socket)<0){
        perror("accepted");
        exit(EXIT_FAILURE);
    }

    return 0;
}



