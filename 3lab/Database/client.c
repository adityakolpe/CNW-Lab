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
	for(;;)
	{
		int choice;
		printf("Choose:\n1. Insert\n2. delete\n3. Display All Book Info\n4. Search\n5. Exit\n");
		scanf("%d",&choice);
		send(sockfd,&choice,sizeof(choice),0);
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

					send(sockfd,title,sizeof(title),0);
					send(sockfd,author,sizeof(author),0);
					send(sockfd,&id,sizeof(id),0);
					send(sockfd,&pages,sizeof(pages),0);
					send(sockfd,pub,sizeof(pub),0);
					printf("Book inserted\n");
					break;
			case 2:
					printf("Id:\t");
					scanf("%d",&id);

					send(sockfd,&id,sizeof(id),0);
					printf("Book deleted\n");
					break;
			case 3:
					recv(sockfd,&n,sizeof(n),0);
					printf("SR.\tTitle\tAuthor\tID\tPages\tPub\n");
					for(int i=0;i<n;i++)
					{
						recv(sockfd,title,sizeof(title),0);
						recv(sockfd,author,sizeof(author),0);
						recv(sockfd,&id,sizeof(&id),0);
						recv(sockfd,&pages,sizeof(&pages),0);
						recv(sockfd,pub,sizeof(pub),0);

						printf("%d\t%s\t%s\t%d\t%d\t%s\n",i+1,title,author,id,pages,pub);	
					}
					break;
			case 4:
					printf("Choose:\n1. Title\n2. Author\n");
					scanf("%d",&t);
					send(sockfd,&t,sizeof(t),0);
					if(t==0)
					{
						printf("Author name:\t");
						scanf("%s",author);
						send(sockfd,author,sizeof(author),0);
					}
					else
					{
						printf("Title name:\t");
						scanf("%s",title);
						send(sockfd,title,sizeof(title),0);
					}
					recv(sockfd,&searchSuccess,sizeof(searchSuccess),0);
					if(searchSuccess==0)
						printf("Book was not found\n");
					else
						printf("Book found. ID:%d\n",searchSuccess);
					
					break;
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
