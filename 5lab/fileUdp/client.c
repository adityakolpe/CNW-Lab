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
	int sendbytes,recvbytes,stop; 
	char fname[30],word[30],buff[255];
	int exists,found;
	printf("Filename: "); 
	scanf("%s",fname);
	sendto(sockfd, fname, sizeof(fname), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

	recvfrom(sockfd, &exists, sizeof(exists), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
	if(exists==0)
		printf("FILE NOT FOUND\n");
	else
	{
		printf("FILE FOUND.\n");
		for (;;) {
			printf("\nChoose:\n1.search\n2.sort\n3.rearrange\n4.exit\n");
			scanf("%d",&n);
			sendto(sockfd, &n, sizeof(n), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			if(n==4) break;
			switch(n)
			{
				case 1:
						printf("word: \n");
						scanf("%s",word);
						sendto(sockfd, word, sizeof(word), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						recvfrom(sockfd, &found, sizeof(found), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
						if(found==1)
							printf("WORD FOUND\n");
						else
							printf("WORD NOT FOUND\n");
						break;
				case 2:	do
						{
							recvfrom(sockfd, &stop, sizeof(stop), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
							if(stop==1) break;
							recvfrom(sockfd, buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
							printf("%s\n",buff);
							printf("%d\n",stop );
						}while(1);
						break;
				case 3: do
						{
							recvfrom(sockfd, &stop, sizeof(stop), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
							if(stop==1) break;
							recvfrom(sockfd, buff, sizeof(buff), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
							printf("%s\n",buff);
							printf("%d\n",stop );
						}while(1);
						break;
			}
		}	
	}
	close(sockfd); 
	return 0; 
} 
