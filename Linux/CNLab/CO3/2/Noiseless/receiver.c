/*Receiver side implementation of stop and wait protocol noiseless*/

//header files
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define ERROR -1
#define MAX_QUEUE 1
#define PORT 11111
#define LOCALHOST "127.0.0.1"

#define MAX_PKT 1024
#define FRAME_SIZE sizeof(frame)

typedef unsigned int seq_nr;  // sequence or ack numebr

typedef struct {
    char data[MAX_PKT];
} packet;  // packet definition

typedef enum { data, ack, nak } frame_kind;  // frame kind definition

typedef struct {
    frame_kind kind;  // what kind of frame
    seq_nr seq;       // sequence number
    seq_nr ack;       // acknowledgement number
    packet info;      // the network layer packet
} frame;              // frame definition

typedef enum { frame_arrival } event_type;  // event type definition

char buffer[FRAME_SIZE];  // buffer to receive frame into
int sockfd;               // server socket file descriptor
int client_sockfd;        // client socket file descriptor
 
// function prototypes
void waitForEvent(event_type* event);
void getData(packet* pkt);
void makeFrame(frame* frm, packet* pkt);
void sendFrame(frame* frm);
void receiveFrame(frame* frm);
void extractData(frame* frm, packet* pkt);
void deliverData(packet* pkt);
void sender(void);
void receiver(void);

void receiver(void) {
    packet p;
    frame f, ackf;
    ackf.kind = ack;
    event_type event;
    while (1) {
        waitForEvent(&event);  // wait for an event to occur
        if (event == frame_arrival) {
            receiveFrame(&f);     // receive a frame
            extractData(&f, &p);  // extract the packet from the frame
            deliverData(&p);      // send the packet to network layer
            sendFrame(&ackf);     // send acknowledgement frame
        }
    }
}

/**
 * Wait for frame arrival
 */
void waitForEvent(event_type* event) {
    if (recv(client_sockfd, buffer, FRAME_SIZE, 0) == FRAME_SIZE) {
        *event = frame_arrival;
    } else {
        printf("No more frames received!\n");
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
}

/**
 * Receieve the frame that has been written into the buffer
 */
void receiveFrame(frame* frm) {
    frame* fbuffer = (frame*)buffer;
    *frm = *fbuffer;
    memset(buffer, 0, FRAME_SIZE);  // clear the buffer
}

/**
 * Send frame to the destination machine
 */
void sendFrame(frame* f) {
    frame* fbuffer = (frame*)buffer;
    *fbuffer = *f;
    if (write(client_sockfd, buffer, FRAME_SIZE) == ERROR) {
        printf("Error in sending frame!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, FRAME_SIZE);  // clear the buffer
}

/**
 * Extract the packet from the frame
 */
void extractData(frame* frm, packet* pkt) {
    *pkt = frm->info;
}

//print the data
void deliverData(packet* pkt) { printf("Received message: %s", pkt->data); }

//driver code
int main() {
    // Creating a socket of TCP/IP type
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        perror("socket() error ");
        return EXIT_FAILURE;
    }

    // port to which we will bind the socket
    unsigned short port = PORT;

    // create a sockaddr_in for server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;    // AF_INET implies IPv4
    server_addr.sin_port = htons(port);  // converting host BO to network BO
    server_addr.sin_addr.s_addr = INADDR_ANY;  // listen on all interfaces
    bzero(&server_addr.sin_zero, 8);           // set padding to zeroes

    // binding the socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
        ERROR) {
        perror("bind failed");
        close(sockfd);
        return EXIT_FAILURE;
    }

    //listening for clients
    if (listen(sockfd, MAX_QUEUE) == ERROR) {
        perror("listen failed");
        close(sockfd);
        return EXIT_FAILURE;
    }
    struct sockaddr_in client_addr;  // a sockaddr_in for client
    unsigned int addrlen = sizeof(client_addr);

    printf("Server listening!\n");

    //accepting clients
    client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    if (client_sockfd == ERROR) {
        perror("accept() failed ");
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Connected successfully Waiting for packets!\n");
    //receiver communications
    receiver();
    printf("No more frames received!\n");
    close(sockfd); //close socket
}