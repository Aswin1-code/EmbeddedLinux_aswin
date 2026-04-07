#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
int main(){
    int soc;
    struct sockaddr_in add;
    char *msg = "Hello from Client";
    soc = socket(AF_INET, SOCK_STREAM, 0); //Create socket
    add.sin_family = AF_INET;
    add.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &add.sin_addr); //Localhost address
    connect(soc, (struct sockaddr *)&add, sizeof(add)); //Connect server
    send(soc, msg, strlen(msg), 0); //Send message
    printf("Message sent to server\n");
    close(soc); //Close socket
    return 0;
}
