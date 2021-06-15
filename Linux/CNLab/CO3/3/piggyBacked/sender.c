#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h>
#define PORT 8080 
#define MAX 1024
#define MAX_SEQ 3
typedef unsigned int seq_nr;
typedef struct 
{
    char data[MAX];
}packet;



typedef enum{data, ack, nak} frame_kind;

typedef struct
{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
}frame;
typedef enum {false, true} bool;
typedef enum {frame_arrival, time_out} event_type;

typedef struct
{
    event_type type;
}event;

char buff[4096];
static int i = 1;

void inc(seq_nr *val)
{
    seq_nr x = *val;
     *val = (x+1) %(1+MAX_SEQ);
}

bool between(seq_nr a, seq_nr b, seq_nr c)
{
    if(((a<=b)&& b<c)||((c<a) &&(a<=b)) || ((b<c)&&(c<a)))
        return true;
    else
        return false;
}

void waitForEvent(int sockfd, event_type *event)
{
    memset(buff,0,sizeof(buff));
    read(sockfd,buff,4096);
    if(strlen(buff) == 0)
    {
        *event = time_out;
    }
    else
        *event = frame_arrival;
}

void getData(packet *p)
{
    char num[50];
    strcpy(num, "This is packet #");
    sprintf(num+16,"%d",i);
    strcpy(p->data, num);
    
    i++; 
}

void makeFrame(seq_nr frame_nr, seq_nr frame_expected, packet buffer[], frame *f)
{
    f->info = buffer[frame_nr];
    f->seq = frame_nr;
    f->ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
    
    //f->kind = ack;
}

void sendFrame(int sockfd, frame *f)
{
    memset(buff,0,sizeof(buff));
    frame *fr = (frame *)buff;
    fr->kind = f->kind;
    fr->seq = f->seq;
    fr->ack = f->ack;
    fr->info = f->info;
    printf("Sending frame...\n");
    printf("%s\n",fr->info.data);
    write(sockfd,buff,sizeof(buff));
}

void receiveFrame(frame *f)
{
    printf("Received acknowledgement...\n");
    frame *fr = (frame *)buff;
    f->ack = fr->ack;
    f->info = fr->info;
    f->kind = fr->kind;
    f->seq =fr->seq;

}

int randn()
{
    srand(time(0));
    return rand()%10 + 1;
}

void extractData(frame *f, packet *p)
{
    *p = f->info;
}

void deliverData(packet *p)
{
    printf("Received data : %s\n",p->data);
}

void sender(int sockfd)
{
   seq_nr next_frame_to_send = 0;
   seq_nr ack_expected = 0;
   seq_nr frame_expected = 0;
   frame r,s;
   packet buffer[MAX_SEQ+1];
   seq_nr nbuffered = 0;
   seq_nr itr;
   event_type event;
   int pos = -1, rcount = 0, scount = 0;
//    getData(&buffer[0]);
//    getData(&buffer[1]);
//    getData(&buffer[2]);
//    getData(&buffer[3]);

   while(rcount < 9 || scount < 9)
   {
       if(nbuffered < MAX_SEQ)
       {
          getData(&buffer[next_frame_to_send]);
          nbuffered++; 
       }
       int x = randn();
       if(x <= 3)
       {
           printf("Sending frame...\n");
           memset(buff,0,sizeof(buff));
           write(sockfd, buff, sizeof(buff));
       }
       else{
       makeFrame(next_frame_to_send, frame_expected, buffer, &s);
       sendFrame(sockfd, &s);
       }
       inc(&next_frame_to_send);

       waitForEvent(sockfd, &event);

       if(event == frame_arrival)
       {
           receiveFrame(&r);
           if(r.seq == frame_expected)
           {
               deliverData(&r.info);
               inc(&frame_expected);
               rcount++;
           }
           while(between(ack_expected, r.ack, next_frame_to_send))
           {
               nbuffered--;
               //pos = inc(pos);
                inc(&ack_expected);
                scount++;
                
            //printf("#######%d#####\n",ack_expected);
           }
           
       }
       
       else
       {
           sleep(3);
           printf("Timed out!! Resending...\n");
           next_frame_to_send = ack_expected;
           for(itr = 1; itr <= nbuffered; itr++)
            {
                makeFrame(next_frame_to_send, 0, buffer, &s);
                sendFrame(sockfd, &s);
                inc(&next_frame_to_send); 
            }
       }
       
       
       
   }
   

}

int main()
{
   int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	sender(sock);
	close(sock);
	return 0; 
}