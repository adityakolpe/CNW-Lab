// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 
int n=0;
// Function designed for chat between client and server. 

struct bank{
	int acc,bal;
	char name[50],type[50];
}b[30];

void insertBank(char name[50],int acc,int bal,char type[50])
{
	strcpy(b[n].name,name);
	b[n].acc = acc;
	b[n].bal = bal;
	strcpy(b[n].type,type);

	n++;
}



int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char hello[] = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Socket Created\n");
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}
	printf("Bind Successful\n");
	
	int len;
	len = sizeof(cliaddr);



	for(;;)
	{
		int choice;
		recvfrom(sockfd,&choice,sizeof(choice),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		printf(" %d\n",choice);
		if(choice==4) break;
		switch(choice)
		{
			char name[50],type[50];
			int acc,bal;
			case 1:
					recvfrom(sockfd,name,sizeof(name),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,&acc,sizeof(acc),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,&bal,sizeof(bal),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,type,sizeof(type),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					insertBank(name,acc,bal,type);
					break;
			case 2:
					recvfrom(sockfd,&acc,sizeof(acc),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					for(int i=0;i<n;i++)
					{
						if(acc==b[i].acc)
						{	
							sendto(sockfd,b[i].name,sizeof(b[i].name),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,&b[i].acc,sizeof(b[i].acc),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,&b[i].bal,sizeof(b[i].bal),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,b[i].type,sizeof(b[i].type),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							break;
						}
						else
						{
							printf("Not found");
						}
					}
					break;
			case 3:
					for(int i=0;i<n;i++)
					{
						if(b[i].bal>20000)
						{
							b[i].bal=b[i].bal-4000;
							sendto(sockfd,b[i].name,sizeof(b[i].name),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,&b[i].acc,sizeof(b[i].acc),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,&b[i].bal,sizeof(b[i].bal),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
							sendto(sockfd,b[i].type,sizeof(b[i].type),MSG_CONFIRM, (const struct sockaddr *) &cliaddr, sizeof(cliaddr));
						}
					}
			
					
			
		}
	}
	
	return 0; 
} 
