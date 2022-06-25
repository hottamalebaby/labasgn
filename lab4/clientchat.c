#include<stdio.h>
#include<string.h>      //strlen
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>

int main(int argc, char *argv[])
{
        int socket_desc;
        struct sockaddr_in server;
        char *message , server_reply[2000];

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Socket not created");
        }

        server.sin_addr.s_addr = inet_addr("192.168.10.10");
        server.sin_family = AF_INET;
        server.sin_port = htons( 8888 );

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("Connection error");
                return 1;
        }

        puts("Connected\n");

        //Send data
        message = "Hello, how are you?";
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
                puts("Message failed to send");
                return 1;
        }
        puts("Data send\n");

        //Receive a reply from the server
        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
                puts("recv failed");
        }
        puts("Reply has been received\n");
        puts(server_reply);

        close(socket_desc);
        return 0;
}
