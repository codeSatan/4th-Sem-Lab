/*Simplest sender side DLL program */

//header files
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<stdlib.h>
#define PORT 1500    //port number must be same for the sender and the receiver 
#define MAX 1024      //buffersize

typedef unsigned int seq_nr;

//data packet from the network layer
typedef struct 
{
    char data[MAX];
}packet;


typedef enum{data, ack, nak} frame_kind;

//frame to be sent : data link headers + data packet 
typedef struct
{
    frame_kind kind;  
    seq_nr seq;
    seq_nr ack;
    packet info;
}frame;

//event type
typedef enum {frame_arrival, time_out} event_type;

//event
typedef struct
{
    event_type type;
}event;

char buff[4096];
static int i = 1; //packet tracker

//waiting the program
void waitForEvent(int sockfd, event_type *event)
{
    //clearing the buffer
    memset(buff,0,sizeof(buff));

    //reading
    read(sockfd,buff,4096);

    //acknowledgement not received
    if(strlen(buff) == 0)
    {
        *event = time_out;
    }

    //acknowledgement received
    else
        *event = frame_arrival;
}

//packet data reader
void getData(packet *p)
{
    char num[50];
    strcpy(num, "This is packet #");
    sprintf(num+16,"%d",i);
    strcpy(p->data, num);
    
    //packet id
    i++; 
}

//making the frame with data and headers
void makeFrame(frame *f, packet p)
{
    f->info = p;
}

//sending the frames
void sendFrame(int sockfd, frame *f)
{
    //clearing the buffer
    memset(buff,0,sizeof(buff));

    //information embedded into the frame struct
    frame *fr = (frame *)buff;
    fr->kind = f->kind;
    fr->seq = f->seq;
    fr->ack = f->ack;
    fr->info = f->info;

    printf("Sending the Frame...\n");
    //sending packet
    write(sockfd,buff,sizeof(buff));
}

//received the Frame
void receiveFrame(frame *f)
{
    printf("Receiving the Frame ...\n");
    frame *fr = (frame *)buff;
    f->ack = fr->ack;
    f->info = fr->info;
    f->kind = fr->kind;
    f->seq =fr->seq;

}

//getting the data
void extractData(frame *f, packet *p)
{
    *p = f->info;
}

//printing the data received
void deliverData(packet *p)
{
    printf("Received data : %s\n",p->data);
}

//sending the frames
void sender(int sockfd)
{
    frame s;
    packet p;
    for(int i=0;i<10;i++)
    {
        sleep(1.5); //timer for sending the packet
        getData(&p); //to get data
        makeFrame(&s,p); //creating the frame
        sendFrame(sockfd, &s); //sending the frame
    }
  
}

//driver code
int main()
{
    int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	 
    //stream type/ TCP-IP type socket created
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT);  //covert ti network type
	
	// Convert IPv4 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

    //connecting to the receiver (server)
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}

    //packet sender
	sender(sock);
    //closing the socket
	close(sock);
	return 0; 
}