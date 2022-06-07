#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

struct Message{
	int from;
	int to;
	char message[1024];
};

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

    int myid;
    struct Message msg;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
    recv(clientSocket, &msg, sizeof(struct Message), 0);
    myid = msg.from;
    printf("My ID: %d\n",myid);

	while(1){
		int toclient;
		printf("Client: \t");
        fgets(msg.message,sizeof(msg.message),stdin);
        msg.from = myid;
		// printf("Enter Client ID of the Reciever: ");
		// scanf("%d",&toclient);
		// msg.to = toclient;
		send(clientSocket, &msg, sizeof(msg), 0);
		recv(clientSocket, &msg, sizeof(struct Message), 0);
		printf("From Client: %d\t Message: %s",msg.from,msg.message);

		if(strcmp(msg.message, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
	}

	return 0;
}