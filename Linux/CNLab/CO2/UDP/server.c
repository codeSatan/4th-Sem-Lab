// Server side implementation of UDP client-server model 

//header files
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 6969
#define MAX 1024 


//communication among the server and client
void communicate(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	struct sockaddr_in cliaddr;
	int len = sizeof(cliaddr); 
	// infinite loop for chat
	while(1) 
	{ 
		memset(buff, 0, sizeof(buff)); 

		// read the message from client a
		recvfrom(sockfd, (char *)buff, MAX, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		
		printf("Client: %s\nServer: ", buff); 
		memset(buff, 0, sizeof(buff)); 
		n = 0; 
		// copy 
		while ((buff[n++] = getchar()) != '\n'); 


		// and send that buffer to client 
		sendto(sockfd, (const char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
		
		//exit conditiond
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Closing Server Side Connection...\n"); 
			break; 
		} 
	} 
} 

//driver code
int main() 
{ 
	int sockfd; 
	 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket  UDP
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Binding the socket 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("Bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	

	//to communicate
	communicate(sockfd);

	//closing the server side of Socket
	close(sockfd);
	
	return 0; 
}