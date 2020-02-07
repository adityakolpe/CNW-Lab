// Client side implementation of UDP client-server model 
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
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Socket Created\n");

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len;
	int num;
	printf("Enter number of ele:\t"); 
	scanf("%d",&num);
	int a[num],res[num];
	sendto(sockfd, &num, sizeof(num), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 

	printf("Enter elements\n");
	for(int i=0;i<num;i++)
		scanf("%d",&a[i]);

	sendto(sockfd, &a, sizeof(a), 
		MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
		
	n = recvfrom(sockfd, &a, sizeof(a), 
				MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len); 
	for(int i=0;i<num;i++)
		printf("%d\t",a[i]);
	printf("\n");

	close(sockfd); 
	return 0; 
} 
