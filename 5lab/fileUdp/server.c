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
	
	int len;
	len = sizeof(cliaddr);




	FILE *fp;
	char fname[30],word[30],str[30],buff[255],*f;
	int n,exists=0,found=0,stop=0;
	recvfrom(sockfd, fname, sizeof(fname), MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 	
	if(fp=fopen(fname,"r"))
	{
		fclose(fp);
		exists=1;
	}
	sendto(sockfd, &exists, sizeof(exists), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	for(;;)
	{
		recvfrom(sockfd, &n, sizeof(n), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		if(n==4) break;
		fp=fopen(fname,"r");
		switch(n)
		{
			case 1:
					recvfrom(sockfd, word, sizeof(word), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
					while ((fgets(str, 30, fp)) != NULL)
					{
						char *p = strstr(str,word);
						if(p)
						{
							found=1;	
							break;
						}
						
					}
					sendto(sockfd, &found, sizeof(found), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					break;
			case 2:	
					while((fgets(buff, 255, fp))!=NULL)
					{
						for(int i=0;i<strlen(buff);i++)
							for(int j=i;j<strlen(buff);j++)
								if(buff[i]>buff[j])
								{
									char temp = buff[i];
									buff[i] = buff[j];
									buff[j] = temp;
								}
						sendto(sockfd, &stop, sizeof(stop), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					}
					stop=1;
					sendto(sockfd, &stop, sizeof(stop), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					break;
			case 3: while((fgets(buff, 255, fp))!=NULL)
					{
						for(int i=0;i<strlen(buff);i++)
							for(int j=i;j<strlen(buff);j++)
								if(buff[i]>buff[j])
								{
									char temp = buff[i];
									buff[i] = buff[j];
									buff[j] = temp;
								}
						sendto(sockfd, &stop, sizeof(stop), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
						sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					}
					stop=1;
					sendto(sockfd, &stop, sizeof(stop), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
					break;
		}
	}
	
	return 0; 
} 
