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

// Driver code 
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
	
	int len, n,num,res; 

	len = sizeof(cliaddr); //len is value/resuslt 

	n = recvfrom(sockfd, &num, sizeof(num), 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Client : %d\n", num); 
	int x,sum=0;
	x=num;
	while(num>0)
	{
		sum=10*sum+num%10;
		num=num/10;
	}
	if(x==sum) res=1;
	else res=0;

	sendto(sockfd, &res, sizeof(&res), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	
	return 0; 
} 
