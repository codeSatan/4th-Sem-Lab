//server side implementation of raw socket protocols

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
#include <linux/udp.h> /* for upd header */

#define ADDR_TO_BIND "127.0.0.1"
#define PORT_TO_BIND 8080

#define MSG_SIZE 8192
#define HEADER_SIZE (sizeof(struct iphdr) + sizeof(struct udphdr))

//driver code
int main(void) 
{
    int raw_socket;
    struct sockaddr_in sockstr, cliaddr,source_socket_address, dest_socket_address;
    socklen_t socklen;
    
    int retval = 0; /* the return value (give a look when an error happens)*/

    char msg[MSG_SIZE];
    ssize_t msglen; /* return value from recv() */

    /* creating a raw socket with UDP protocols*/
    if ((raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) {
        perror("Socket creation failure\n");
        return 1; /* here there is no clean up -- retval was not used */
    }

    //socket details
    sockstr.sin_family = AF_INET;
    sockstr.sin_port = htons(PORT_TO_BIND);
    sockstr.sin_addr.s_addr = inet_addr(ADDR_TO_BIND);
    socklen = (socklen_t) sizeof(sockstr);
    memset(&cliaddr,0,sizeof(cliaddr));
    
    //binding sockets
    if (bind(raw_socket, (struct sockaddr*) &sockstr, socklen) == -1) {
        perror("bind failed\n");
        retval = 1; /* '1' means "Error" */
        goto _go_close_socket;
    }

    int len = sizeof(cliaddr);

    //receive the message from the client
    msglen = recvfrom(raw_socket, (char *)msg, MSG_SIZE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len);  
    
    //custom structs 
    struct iphdr *ip_packet = (struct iphdr *)msg;
    struct udphdr *udp = (struct udphdr *)(msg + sizeof(struct iphdr));

    //source socket address
    memset(&source_socket_address, 0, sizeof(source_socket_address));
    source_socket_address.sin_addr.s_addr = ip_packet->saddr;
    
    //destination socket address
    memset(&dest_socket_address, 0, sizeof(dest_socket_address));
    dest_socket_address.sin_addr.s_addr = ip_packet->daddr;
    
    //retriving all the information from the packet by client
    printf("Incoming Packet: \n");
    printf("Packet Size (bytes): %d\n",ntohs(ip_packet->tot_len));
    printf("Source Address: %s\n", (char *)inet_ntoa(source_socket_address.sin_addr));
    printf("Destination Address: %s\n", (char *)inet_ntoa(dest_socket_address.sin_addr));
    printf("Total length: %d\n", ip_packet->tot_len);
    printf("Identification: %d\n\n", ntohs(ip_packet->id)); //packet ID
    printf("UDP Layer: \n");

    //convert to byte ordering from network ordering
    printf("Source: %d\n", ntohs(udp->source));
    printf("Destination: %d\n", ntohs(udp->dest));
    printf("Length: %d\n", ntohs(udp->len));   

    if (msglen <= HEADER_SIZE) /* msg  can't be lesser than header! */
        printf("No msg!\n");
    else 
    {
        msg[msglen] = '\0'; /* we need a null character at the end*/
        printf("Client's message: %s\n",
               msg + HEADER_SIZE);
    }

//failed to establish connection
_go_close_socket:
    close(raw_socket);

    return retval;
}