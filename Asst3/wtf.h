#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <pthread.h>
#include <netdb.h>
#define h_addr h_addr_list[0]
void error(char *msg)
{
    perror(msg);
    exit(1);
}
void erase(char* str){
    int i=0;
    for(;i<999;i++){
        str[i]='\0';
    }
}
void bomb(int n){
    if(n==1){
        printf("Invalid arguments\n");
        exit(0);
    }
    if(n==0){
        exit(0);
    }

}
char* createString(){
    char* buffer=(char*)malloc(sizeof(char)*999);
    erase(buffer);
    return buffer;
}

