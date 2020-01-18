#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include<string.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	FILE *fp;
	char fname[30],word[30],str[30],buff[255],*f;
	int n,exists=0,found=0,stop=0;
	recv(sockfd,fname,sizeof(fname),0);
	if(fp=fopen(fname,"r"))
	{
		fclose(fp);
		exists=1;
	}
	send(sockfd,&exists,sizeof(exists),0);
	for(;;)
	{
		recv(sockfd,&n,sizeof(n),0);
		if(n==4) break;
		fp=fopen(fname,"r");
		switch(n)
		{
			case 1:
					recv(sockfd,word,sizeof(word),0);
					while ((fgets(str, 30, fp)) != NULL)
					{
						char *p = strstr(str,word);
						if(p)
						{
							found=1;	
							break;
						}
						
					}
					send(sockfd,&found,sizeof(found),0);
					break;
			case 2:	
					while((fgets(buff, 255, fp))!=NULL)
					{
						for(int i=0;i<strlen(buff);i++)
							for(int j=i;j<strlen(buff);j++)
								if(buff[i]>buff[j])
								{
									char temp = buff[i];
									buff[i] = buff[j];
									buff[j] = temp;
								}
						send(sockfd,&stop,sizeof(stop),0);
						send(sockfd,buff,sizeof(buff),0);
					}
					stop=1;
					send(sockfd,&stop,sizeof(stop),0);
					break;
		}
	}
} 

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 
