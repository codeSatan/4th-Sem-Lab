/*Simplest receiver side DLL program*/

//header files
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>  
#include <string.h> 
#define PORT 1500    //port number must be same for the sender and the receiver
#define MAX 1024     //buffersize

typedef unsigned int seq_nr;

//packet data
typedef struct 
{
    char data[MAX];
}packet;

//frame type
typedef enum{data, ack, nak} frame_kind;

//frame struct : data link haeders + data packet
typedef struct
{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
}frame;

//event type
typedef enum {frame_arrival, time_out} event_type;

typedef struct
{
    event_type type;
}event;

//frame buffersize
char buff[4096];
static int i = 1;  //frame counter

//wait for the sender to send packets
void waitForEvent(int sockfd, event_type *event)
{
	//clearing the buffer
    memset(buff,0,sizeof(buff));

	//reading the frame
    read(sockfd,buff,4096);

	//frame not received
    if(strlen(buff) == 0)
    {
        *event = time_out;
    }
    else
        *event = frame_arrival;  //frame received
}

//data into packet
void getData(packet *p)
{
    strcpy(p->data, "This is packet #");
    
    i++; 
}

//creating the frame
void makeFrame(frame *f, packet p)
{
    f->info = p;
}

//sending the acknowledgement
void sendFrame(int sockfd, frame *f)
{
    printf("Sending frame...\n");
    write(sockfd, f, sizeof(f));
}

//receiver frame from sender
void receiveFrame(frame *f)
{
    printf("Receiving frame...\n");
    frame *fr = (frame *)buff;
    f->ack = fr->ack;
    f->info = fr->info;
    f->kind = fr->kind;
    f->seq =fr->seq;
}

//get data from the frame
void extractData(frame *f, packet *p)
{
    *p = f->info;
}

//sending data
void deliverData(packet *p)
{
    printf("Received data : %s\n",p->data);
}

//receiver code
void receiver(int sockfd)
{
   	frame r;
   	packet p;
   	event_type event;

   	//3 packets
   	for(int i=0;i<10;i++)
   	{
		sleep(1.5);
   		waitForEvent(sockfd, &event);
   		if(event == frame_arrival)
  		{
       		receiveFrame(&r);  //receive the frame
       		extractData(&r, &p);  //get the data
       		deliverData(&p);    //deliver data
   		}
   }
}

//driver code
int main()
{
    int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket of TCP/IP type
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// binding the socket 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	//listening for clients
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("Listen failed"); 
		exit(EXIT_FAILURE); 
	} 

	//accepting clients
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
	{ 
		perror("Accept failed."); 
		exit(EXIT_FAILURE); 
	} 

	//receiver communication
	receiver(new_socket);

	//closing socket
	close(server_fd); 
	return 0; 
}