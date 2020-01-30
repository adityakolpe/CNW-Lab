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
int n=0;
// Function designed for chat between client and server. 

struct book{
	int id,pages;
	char title[50],author[50],pub[50];
}b[30];

void insertBook(char title[50],char author[50],int id,int pages,char pub[50])
{
	strcpy(b[n].title,title);
	strcpy(b[n].author,author);
	b[n].id = id;
	b[n].pages = pages;
	strcpy(b[n].pub,pub);

	printf(" %s\t%s\t%d\t%d\t%s\n",title,author,id,pages,pub);
	n++;
}


void deleteBook(int id)
{
	int num=-1;
	for(int i=0;i<n;i++)
	{
		if(b[n].id==id)
		{
			num=n;
			break;
		}
	}
	for(int i=num;i<n-1;i++)
	{
		strcpy(b[num].title,b[num+1].title);
		strcpy(b[num].author,b[num+1].author);
		b[num].id = b[num+1].id;
		b[num].pages = b[num+1].pages;
		strcpy(b[num].pub,b[num+1].pub);
	}
	n--;
}

void displayAll(int sockfd)
{
	send(sockfd,&n,sizeof(n),0);
	for(int i=0;i<n;i++)
	{
		send(sockfd,b[i].title,sizeof(b[i].title),0);
		send(sockfd,b[i].author,sizeof(b[i].author),0);
		send(sockfd,&b[i].id,sizeof(b[i].id),0);
		send(sockfd,&b[i].pages,sizeof(b[i].pages),0);
		send(sockfd,b[i].pub,sizeof(b[i].pub),0);

		printf(" %s\t%s\t%d\t%d\t%s\n",b[i].title,b[i].author,b[i].id,b[i].pages,b[i].pub);

	}
}

int searchBookTitle(char title[50])
{
	for(int i=0;i<n;i++)
	{
		if(strcmp(b[i].title,title)==0)
			return n;
	}
	return 0;
}

int searchBookAuthor(char author[50])
{
	for(int i=0;i<n;i++)
	{
		if(strcmp(b[i].author,author)==0)
			return n;
	}
	return 0;
}

void func(int sockfd) 
{ 
	for(;;)
	{
		int choice;
		recv(sockfd,&choice,sizeof(choice),0);
		printf(" %d\n",choice);
		if(choice==5) break;
		switch(choice)
		{
			char title[50],author[50],pub[50];
			int id,pages,t,searchSuccess;
			case 1:
					recv(sockfd,title,sizeof(title),0);
					recv(sockfd,author,sizeof(author),0);
					recv(sockfd,&id,sizeof(id),0);
					recv(sockfd,&pages,sizeof(pages),0);
					recv(sockfd,pub,sizeof(pub),0);
					insertBook(title,author,id,pages,pub);
					break;
			case 2:
					recv(sockfd,&id,sizeof(id),0);
					deleteBook(id);
					break;
			case 3:
					displayAll(sockfd);
					break;
			case 4:
					recv(sockfd,&t,sizeof(t),0);
					if(t==0)
					{
						recv(sockfd,author,sizeof(author),0);
						searchSuccess = searchBookAuthor(author);
					}
					else
					{
						recv(sockfd,title,sizeof(title),0);
						searchSuccess = searchBookTitle(title);
					}
					send(sockfd,&searchSuccess,sizeof(searchSuccess),0);
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
