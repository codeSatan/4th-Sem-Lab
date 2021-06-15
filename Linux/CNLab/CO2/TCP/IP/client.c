// Client side C program TCP/IP

//header files
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>  
#include <string.h> 
#define PORT 1500
#define MAX 1024

//for communication
void communicate(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 

	//infinite loop
	while(1) 
	{  
		memset(buff, 0, sizeof(buff)); 
		printf("Client: "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n'); 

		//write message to Server
		write(sockfd, buff, sizeof(buff)); 
		if ((strncmp(buff, "exit", 4)) == 0) 
		{ 
			printf("Closing Client side connection\n"); 
			break; 
		}

		memset(buff, 0, sizeof(buff)); 

		//reading from the Server side
		read(sockfd, buff, sizeof(buff)); 
		printf("Server: %s", buff); 
		 
	} 
} 

//driver Code
int main() 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	
	//creating sockets of TCP/IP
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); //convert to network address type
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	//connecting to the Server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	//to communicate
	communicate(sock);

	//closing the Client side
	close(sock);
	return 0; 
} 