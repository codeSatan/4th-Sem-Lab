// Server side C program TCP/IP

//header files
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 1500
#define MAX 1024

//to communicate
void communicate(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 

	// infinite loop for chat
	while(1) 
	{ 
		memset(buff, 0, sizeof(buff)); 

		// read the message from client 
		read(sockfd, buff, sizeof(buff)); 
		printf("Client: %s\nServer: ", buff); 
		memset(buff, 0, sizeof(buff)); 
		n = 0; 

		// copy server message in the buffer 
		while ((buff[n++] = getchar()) != '\n');
			

		// writing to the client
		write(sockfd, buff, sizeof(buff)); 

		// exit condition
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Closing Server Side connection...\n"); 
			break; 
		} 
	} 
} 

//driver Code
int main() 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket TCP/IP
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("Socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	//Forcefully attaching socket to Port
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// binding the Socket
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("Bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	//listening for Client requests
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("Listen failed"); 
		exit(EXIT_FAILURE); 
	} 

	//accepting the requests
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("Accept failed."); 
		exit(EXIT_FAILURE); 
	} 

	//to communicate
	communicate(new_socket);

	//closing the server side
	close(server_fd); 
	return 0; 
}
