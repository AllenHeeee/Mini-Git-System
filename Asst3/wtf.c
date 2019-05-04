#include"wtf.h"
int port=0;
char* IP;
char* Port;
void connection(){
//port num goes here 
 int network_socket;
 char message[256]="hello from the other side";
 network_socket= socket(AF_INET,SOCK_STREAM,0);
 
 struct sockaddr_in server_address;


struct hostent *server;
 server=gethostbyname(IP);
 bzero((char *) &server_address, sizeof(server_address));
 server_address.sin_family = AF_INET;
 memcpy(&server_address.sin_addr,server->h_addr,server->h_length);
 server_address.sin_port=htons(port);
if(inet_pton(AF_INET,IP, &server_address.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return; 
    }

 server_address.sin_addr.s_addr=INADDR_ANY;

 int connection_status= connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address));
 if(connection_status ==-1){
 printf("error. \n");
 }

 char str[256];
 recv(network_socket, &str,sizeof(str),0);
 send(network_socket, message,strlen(message),0);
 printf("server sent data: %s\n ", str);
 close(network_socket);

}
int main (int argc,char** argv){
    IP=createString();
    Port=createString();
    int fd=open("./.configure", S_IRUSR | S_IWUSR);
    if(fd<0||(argc>2&&strcmp("configure",argv[1])==0)){
        //It means the program is call in first time
        //OR Update IP address and port
        if(argc!=4){
            bomb(1);
        }
        if(strcmp(argv[1],"configure")==0){
            close(fd);
            fd=open("./.configure", O_WRONLY | O_CREAT,0777);
            strcpy(IP,argv[2]);
            strcat(IP,"\n");
            strcpy(Port,argv[3]);
            strcat(Port,"\n");
            write(fd,IP,strlen(IP));
            write(fd,Port,strlen(Port));
            printf("Configuration SET UP Successfully\n");
            return 0;
        }else{
            bomb(1);
        }
    }else{
        //Already set up the Configuaration
        char bu[2];
        bu[1]='\0';
        while(read(fd,bu,1)!=0){
            if(bu[0]=='\n'){
                while(read(fd,bu,1)!=0){
                    if(bu[0]=='\n'){
                        port=atoi(Port);
                        break;
                    }
                    strcat(Port,bu);
                }
                break;
            }
            strcat(IP,bu);
        }
        close(fd);
        printf("IP:%s\n",IP);
        printf("Port:%d\n",port);
    }
    connection();
    return 0;
}