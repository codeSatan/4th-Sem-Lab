//client side implementation of UDP server-client model

//header files
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 6969  //port number must be same for both server and client
#define MAX 1024

//to communicate
void communicate(int sockfd, struct sockaddr_in servaddr) 
{ 
	char buff[MAX]; 
	int n, len; 

	//infinite loop
	while(1) 
	{  
		memset(buff, 0, sizeof(buff)); 
		printf("Client: "); 
		n = 0; 

		//copy
		while ((buff[n++] = getchar()) != '\n'); 

		//to send message to the server
		sendto(sockfd, (const char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		
		//exit conditions
		if((strncmp(buff, "exit", 4)) == 0) 
		{ 
			printf("Closing Client side connection\n"); 
			break; 
		} 

		memset(buff, 0, sizeof(buff)); 

		//receive message from the server
		recvfrom(sockfd, (char *)buff, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
		printf("Server: %s", buff);
		
	} 
} 

//driver Code
int main() 
{ 
	int sockfd; 
	
	struct sockaddr_in	 servaddr; 

	// Creating socket file UDP
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); //convert to the network address type
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	//to communicate
	communicate(sockfd, servaddr);

	//closing client side connection
	close(sockfd); 
	return 0; 
}