//client side implemenation of Raw Sockets

//header files
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <linux/ip.h> /* for ipv4 header */
#include <linux/udp.h> /* for udp header */
     
#define HEADER_SIZE (sizeof(struct iphdr) + sizeof(struct udphdr)) 
#define PCKT_LEN 8192   //packet length

//checksum for intigrety
unsigned short csum(unsigned short *buf, int nwords)
{       
        unsigned long sum;
        for(sum=0; nwords>0; nwords--)
                sum += *buf++;
        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        return (unsigned short)(~sum);
}

//driver Code 
int main()
{
    int sd;
    char *argv[5] = {" ","127.0.0.1","3333","127.0.0.1","8080"};
    // No data/payload just datagram
    char hello[20] = "Hello world";
    char buffer[PCKT_LEN];  //buffer

    //initialise with 0
    memset(buffer,0,sizeof(buffer));
    
    // Our own headers' structures
    struct iphdr *ip = (struct iphdr *) buffer; 
    struct udphdr *udp = (struct udphdr *) (buffer + sizeof(struct iphdr));

    //initialise to 0
    memset(buffer, 0, PCKT_LEN);
    char *data = (char *)(buffer + sizeof(struct iphdr) + sizeof(struct udphdr));
    strcpy(data, "hello from client");   //data to be sent
    //printf("%lld\n", strlen(data));
    // Source and destination addresses: IP and port

    struct sockaddr_in sin;
    int one = 1;
    const int *val = &one;

    // Create a raw socket with UDP protocol
    sd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

    //if failed to create a raw socket
    if(sd < 0)
    {
        perror("socket() error");
        exit(-1);
    }
    else
    printf("socket() - Using SOCK_RAW socket and UDP protocol is OK.\n");

    // The address family
    sin.sin_family = AF_INET;
    // Port numbers
    sin.sin_port = htons(8080);
    // IP addresses
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    // Fabricate the IP header or we can use the standard header structures but assign our own values.
     ip->ihl = 5;
     ip->version = 4;
     ip->tos = 0;
     ip->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
     ip->id = htonl (54321);	                 //Id of this packet
     ip->frag_off = 0;
     ip->ttl = 255;
     ip->protocol = IPPROTO_UDP;
     ip->check = 0;		                //Set to 0 before calculating checksum
     ip->saddr = inet_addr ("127.0.0.1");	//Spoof the source ip address
     ip->daddr = sin.sin_addr.s_addr;
	
     //Ip checksum
     ip->check = csum ((unsigned short *) buffer, ip->tot_len);

     // Fabricate the UDP header. Source port number, redundant
     udp->source= htons(atoi(argv[2]));

     // Destination port number
     udp->dest = htons(atoi(argv[4]));

     udp->len = htons(sizeof(struct udphdr));

     //Calculate the checksum for integrity

    

    // Inform the kernel do not fill up the packet structure. we will build our own...
    if(setsockopt(sd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
    {
        perror("setsockopt() error");
        exit(-1);
    }
    else
    printf("setsockopt() is OK.\n");

     
    // Send loop, send for every 2 second for 100 count
    printf("my messsage: %s\n",(buffer+ HEADER_SIZE));
    printf("Trying...\n");

    printf("Using raw socket and UDP protocol\n");

    printf("Using Source IP: %s port: %u, Target IP: %s port: %u.\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));

    int count;

    //checking if msg is received
    if(sendto(sd, buffer, ip->tot_len, MSG_CONFIRM, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto() error");
        exit(-1);
    }
    else
    {
        printf("sendto() is OK.\n");
    //sleep(2);
    }

    //closing the sockets
    close(sd);
    return 0;
}