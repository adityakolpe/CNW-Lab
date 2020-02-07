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
	
	int len;
	len = sizeof(cliaddr);



	for(;;)
	{
		int choice;
		recvfrom(sockfd,&choice,sizeof(choice),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		printf(" %d\n",choice);
		if(choice==5) break;
		switch(choice)
		{
			char title[50],author[50],pub[50];
			int id,pages,t,searchSuccess;
			case 1:
					recvfrom(sockfd,title,sizeof(title),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,author,sizeof(author),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,&id,sizeof(id),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,&pages,sizeof(pages),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					recvfrom(sockfd,pub,sizeof(pub),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					insertBook(title,author,id,pages,pub);
					break;
			case 2:
					recvfrom(sockfd,&id,sizeof(id),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					deleteBook(id);
					break;
			case 3:
					sendto(sockfd, &n, sizeof(&n), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					for(int i=0;i<n;i++)
					{
						sendto(sockfd,b[i].title,sizeof(b[i].title),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd,b[i].author,sizeof(b[i].author),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd,&b[i].id,sizeof(b[i].id),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd,&b[i].pages,sizeof(b[i].pages),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd,b[i].pub,sizeof(b[i].pub),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						printf(" %s\t%s\t%d\t%d\t%s\n",b[i].title,b[i].author,b[i].id,b[i].pages,b[i].pub);

					}
					break;
			case 4:
					recvfrom(sockfd,&t,sizeof(t),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
					if(t==0)
					{
						recvfrom(sockfd,author,sizeof(author),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
						searchSuccess = searchBookAuthor(author);
					}
					else
					{
						recvfrom(sockfd,title,sizeof(title),MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
						searchSuccess = searchBookTitle(title);
					}
					sendto(sockfd, &searchSuccess, sizeof(searchSuccess), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					break;
		}
	}
	
	return 0; 
} 
