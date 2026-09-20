#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main ()
{

    int serverSock;

    if (( serverSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("could not get our server socket fd");
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (struct sockaddr *)&serverAddr, sizeof serverAddr) < 0)
    {
        perror("could not bind to server socket and address");
        return -1;
    }

    if (listen(serverSock, 5) < 0)
    {
        perror("could not listen on server socket and ip");
        return -1;
    }

    printf("listening on port %d\n", PORT);

    while (1)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof clientAddr;
        int *clientSocket = malloc(sizeof(int));

        if ((*clientSocket = accept(serverSock, (struct sockaddr *)&clientAddr, &clientLen)) < 0)
        {
            perror("could not accept client");
            continue;
        }
        printf("client connectded\n");

        close(*clientSocket);
        printf("client disconnected\n");

        free(clientSocket);
    }
    close(serverSock);


    return 0;
}
