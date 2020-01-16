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
	int n,sendbytes,recvbytes,pos; 
	for (;;) { 
		printf("Number of elements: "); 
		scanf("%d",&n);
		sendbytes = send(sockfd, &n, sizeof(n),0); 
		
		int a[n];
		printf("Enter elements\n");
		for (int i=0;i<n;i++)
			scanf("%d",&a[i]);
		sendbytes = send(sockfd,&a,sizeof(a),0);

		int ele;
		printf("Ele to be found:\n");
		scanf("%d",&ele);
		sendbytes = send(sockfd,&ele,sizeof(ele),0);

		recvbytes = recv(sockfd,&pos,sizeof(pos),0);
		if(pos==-1)
			printf("Ele not found\n");
		else
			printf("Ele found at %d\n",pos );
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
