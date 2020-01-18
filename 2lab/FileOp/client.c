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
	int n,sendbytes,recvbytes,stop; 
	char fname[30],word[30],buff[255];
	int exists,found;
	printf("Filename: "); 
	scanf("%s",fname);
	send(sockfd,fname,sizeof(fname),0);

	recv(sockfd,&exists,sizeof(exists),0);
	if(exists==0)
		printf("FILE NOT FOUND\n");
	else
	{
		printf("FILE FOUND.\n");
		for (;;) {
			printf("\nChoose:\n1.search\n2.sort\n3.rearrange\n4.exit\n");
			scanf("%d",&n);
			send(sockfd,&n,sizeof(n),0);
			if(n==4) break;
			switch(n)
			{
				case 1:
						printf("word: \n");
						scanf("%s",word);
						send(sockfd,word,sizeof(word),0);
						recv(sockfd,&found,sizeof(found),0);
						if(found==1)
							printf("WORD FOUND\n");
						else
							printf("WORD NOT FOUND\n");
						break;
				case 2:	do
						{
							recv(sockfd,&stop,sizeof(stop),0);
							if(stop==1) break;
							recv(sockfd,buff,sizeof(buff),0);
							printf("%s\n",buff);
							printf("%d\n",stop );
						}while(1);
						break;
			}
		}	
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
