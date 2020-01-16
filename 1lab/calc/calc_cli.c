#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<sys/types.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 
void func(int sockfd) 
{ 
	char buff[2]; 
	int n,n1,n2,res,sendbytes,recvbytes; 
	for (;;) { 
		printf("Enter first number : "); 
		scanf("%d",&n1);
		sendbytes = send(sockfd, &n1, sizeof(n1),0); 

		printf("Enter operator : "); 
		scanf("%s",buff);
		sendbytes = send(sockfd, &buff, sizeof(buff),0); 

		printf("Enter second number : "); 
		scanf("%d",&n2);
		sendbytes = send(sockfd, &n2, sizeof(n2),0); 
 
		recvbytes = recv(sockfd, &res, sizeof(res),0); 
		printf("From Server : %d\n", res);
		
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 
} 
