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
	


	for(;;)
	{
		int choice;
		printf("Choose:\n1. Insert\n2. delete\n3. Display All Book Info\n4. Search\n5. Exit\n");
		scanf("%d",&choice);
		sendto(sockfd,&choice,sizeof(choice),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		if(choice==5) break;
		switch(choice)
		{
			char title[50],author[50],pub[50];
			int id,pages,t,n,searchSuccess;
			case 1:
					printf("Title of the Book:\t");
					scanf("%s",title);
					printf("Author:\t");
					scanf("%s",author);
					printf("Accession Number (id):\t");
					scanf("%d",&id);
					printf("Pages:\t");
					scanf("%d",&pages);
					printf("Publisher:\t");
					scanf("%s",pub);

					sendto(sockfd,title,sizeof(title),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,author,sizeof(author),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,&id,sizeof(id),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,&pages,sizeof(pages),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					sendto(sockfd,pub,sizeof(pub),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					printf("Book inserted\n");
					break;
			case 2:
					printf("Id:\t");
					scanf("%d",&id);

					sendto(sockfd,&id,sizeof(id),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					printf("Book deleted\n");
					break;
			case 3:
					recvfrom(sockfd,&n,sizeof(n),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
					printf("SR.\tTitle\tAuthor\tID\tPages\tPub\n");
					for(int i=0;i<n;i++)
					{
						recvfrom(sockfd,title,sizeof(title),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,author,sizeof(author),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,&id,sizeof(&id),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,&pages,sizeof(&pages),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
						recvfrom(sockfd,pub,sizeof(pub),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);

						printf("%d\t%s\t%s\t%d\t%d\t%s\n",i+1,title,author,id,pages,pub);	
					}
					break;
			case 4:
					printf("Choose:\n1. Title\n2. Author\n");
					scanf("%d",&t);
					sendto(sockfd,&t,sizeof(t),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					if(t==0)
					{
						printf("Author name:\t");
						scanf("%s",author);
						sendto(sockfd,author,sizeof(author),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					}
					else
					{
						printf("Title name:\t");
						scanf("%s",title);
						sendto(sockfd,title,sizeof(title),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					}
					recvfrom(sockfd,&searchSuccess,sizeof(searchSuccess),MSG_WAITALL, (struct sockaddr *) &servaddr, 
				&len);
					if(searchSuccess==0)
						printf("Book was not found\n");
					else
						printf("Book found. ID:%d\n",searchSuccess);
					
					break;
		}
	}



	close(sockfd); 
	return 0; 
} 
