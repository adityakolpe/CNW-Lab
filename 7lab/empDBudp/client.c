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
	


	for(;;)
	{
		int choice;
		printf("Choose:\n1. Insert\n2. search using accNo\n3. BalDeduction\n4. Exit\n");
		scanf("%d",&choice);
		sendto(sockfd,&choice,sizeof(choice),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		if(choice==4) break;
		switch(choice)
		{
			char name[50],type[50];
			int acc,bal;
			case 1:
					printf("Name:\t");
					scanf("%s",name);
					printf("Acc No:\t");
					scanf("%d",&acc);
					printf("Bal:\t");
					scanf("%d",&bal);
					printf("Type:\t");
					scanf("%s",type);

					sendto(sockfd,name,sizeof(name),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,&acc,sizeof(acc),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,&bal,sizeof(bal),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,type,sizeof(type),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					printf("Details inserted\n");
					break;
			case 2:
					printf("Acc No:\t");
					scanf("%d",&acc);

					sendto(sockfd,&acc,sizeof(acc),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

					recvfrom(sockfd,name,sizeof(name),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,&acc,sizeof(&acc),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,&bal,sizeof(&bal),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,type,sizeof(type),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);

						printf("%s\t%d\t%d\t%s\n",name,acc,bal,type);
					
					

					break;
			case 3:while(1)
					{
						recvfrom(sockfd,name,sizeof(name),MSG_WAITALL, (struct sockaddr *) &servaddr, 
					&len);
							recvfrom(sockfd,&acc,sizeof(&acc),MSG_WAITALL, (struct sockaddr *) &servaddr, 
					&len);
							recvfrom(sockfd,&bal,sizeof(&bal),MSG_WAITALL, (struct sockaddr *) &servaddr, 
					&len);
							recvfrom(sockfd,type,sizeof(type),MSG_WAITALL, (struct sockaddr *) &servaddr, 
					&len);

							printf("%s\t%d\t%d\t%s\n",name,acc,bal,type);
						}
						
					
			
		}
	}



	close(sockfd); 
	return 0; 
} 