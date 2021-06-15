/*A receiver side program to implement Go Back N with NACK*/

//header files
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
#define MAX 1024
#define MAX_SEQ 3
typedef unsigned int seq_nr;

//data packet
typedef struct 
{
    char data[MAX];
}packet;

typedef enum{data, ack, nak} frame_kind;

//frame structure
typedef struct
{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
}frame;
typedef enum {false, true} bool;
typedef enum {frame_arrival, time_out} event_type;

//event structure
typedef struct
{
    event_type type;
}event;

//frame buffer size
char buff[4096];
static int i = 1;  //packet seriel number


bool between(seq_nr a, seq_nr b, seq_nr c)
{
    if(((a<=b)&& b<c)||((c<a) &&(a<=b)) || ((b<c)&&(c<a)))
        return true;
    else
        return false;
}

//server side waiting for the frame to arrive
void waitForEvent(int sockfd, event_type *event)
{
    //clear the buffer
    memset(buff,0,sizeof(buff));
    read(sockfd,buff,4096); //reading into buffer
    if(strlen(buff) == 0)
    {
        *event = time_out;   //frame did not reach
    }
    else
        *event = frame_arrival; //frame arrived
}

//getting data into the packet
void getData(packet *p)
{
    char num[50];
    strcpy(num, "This is packet #");
    sprintf(num+16,"%d",i);
    strcpy(p->data, num);
    
    i++; 
}

//making the frame
void makeFrame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer, frame *f)
{
    f->kind = fk;
    f->info = buffer;
    f->seq = frame_nr;
    f->ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    
}

//sending the frame acknowledgement
void sendFrame(int sockfd, frame *f)
{
    //clear the frame buffer
    memset(buff,0,sizeof(buff));
    frame *fr = (frame *)buff;
    fr->kind = f->kind;
    fr->seq = f->seq;
    fr->ack = f->ack;
    fr->info = f->info;

    printf("Sending frame...\n");
    write(sockfd,buff,sizeof(buff));  //writing into the buffer
}

//to receive the frame
void receiveFrame(frame *f)
{
    printf("Receiving frame...\n");
    frame *fr = (frame *)buff;
    f->ack = fr->ack;
    f->info = fr->info;
    f->kind = fr->kind;
    f->seq =fr->seq;
}

//getting the data from the frame
void extractData(frame *f, packet *p)
{
    *p = f->info;
}

//printing the data
void deliverData(packet *p)
{
    printf("Received data : %s\n",p->data);
}

//receiver side code
void receiver(int sockfd)
{
    seq_nr next_frame_to_send;
    seq_nr frame_expected;
    seq_nr ack_expected;
    frame r,s;
    packet buffer[MAX_SEQ + 1];  //N
    seq_nr nbuffered;
    seq_nr i;
    event_type event;

    ack_expected = 0;
    next_frame_to_send = 0;
    frame_expected = 0;
    nbuffered = 0;

    int count = 0;
    while(count < 9)
    {
        //waiting for the event
        waitForEvent(sockfd, &event);
        if(event == frame_arrival)     //frame arrived
        {
            receiveFrame(&r);   //receive the frame
            if(r.seq == frame_expected)
            {
                count++;
                deliverData(&r.info);
                frame_expected = (frame_expected + 1) % (MAX_SEQ + 1);
            }
            packet dumPacket;
            makeFrame(ack, count-1, frame_expected, dumPacket, &s);
            sendFrame(sockfd, &s);   //dummy as return frame of NACK
        }
        else
        {
            //expecting the packet again
            printf("Frame was not received...\n");
            printf("Sending NACK %d\n",frame_expected);
            packet dummy;
            makeFrame(nak, 0, frame_expected, dummy, &s);
            sendFrame(sockfd, &s);
        }
       sleep(5);
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
	
	// attaching socket to the port 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// binding the socket 
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0) 
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

    //accepting the client requests
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
	{ 
		perror("Accept failed."); 
		exit(EXIT_FAILURE); 
	} 

    //receiver communication
	receiver(new_socket);

    //closing the socket
	close(server_fd); 
	return 0; 
}