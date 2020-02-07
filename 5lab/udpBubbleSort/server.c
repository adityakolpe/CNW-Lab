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
	int a[num];

	n = recvfrom(sockfd, &a, sizeof(a), 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	for(int i=0;i<num;i++)
		for(int j=0;j<num;j++)
			if(a[j]>a[i])
			{
				int temp = a[i];
				a[i]=a[j];
				a[j]=temp;
			}
	
	sendto(sockfd, &a, sizeof(a), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	
	return 0; 
} 
