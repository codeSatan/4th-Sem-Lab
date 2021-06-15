/*Receiver side implementation of noisy stop and wait protocol*/

//header files
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define ERROR -1
#define MAX_QUEUE 1
#define PORT 11111
#define LOCALHOST "127.0.0.1"

#define MAX_PKT 1024
#define FRAME_SIZE sizeof(frame)

// probability weights of events
#define FRAME_ARRIVAL_W 70
#define CKSUM_ERR_W 30
#define TOTAL_W (FRAME_ARRIVAL_W + CKSUM_ERR_W)

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

typedef enum {
    timeout,
    frame_arrival,
    cksum_err
} event_type;  // event type definition

char buffer[FRAME_SIZE];  // buffer to receive frame into
char checksumBuffer[FRAME_SIZE];
int sockfd;         // server socket file descriptor
int client_sockfd;  // client socket file

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

void sendCkSumErrorFrame();

void receiver(void) {
    packet p;
    frame f, ackf;
    ackf.kind = ack;
    event_type event = frame_arrival;
    seq_nr frame_expected = 0;
    while (1) {
        waitForEvent(&event);  // wait for an event to occur
        if (event == frame_arrival) {
            receiveFrame(&f);  // receive a frame
            if (f.seq == frame_expected) {
                extractData(&f, &p);  // extract the packet from the frame
                deliverData(&p);      // send the packet to network layer
                frame_expected = (frame_expected + 1) % 2;
            } else {
                printf("Wrong Frame!\n");
            }
            ackf.ack = 1 - frame_expected;
            sendFrame(&ackf);  // send acknowledgement frame
            printf("Sending Acknowledgement!\n");
        } else if (event == cksum_err) {
            printf("Checksum error in Frame!\n");
            sendCkSumErrorFrame();
        }
        fflush(stdin);
    }
}

/**
 * Wait for frame arrival
 */
void waitForEvent(event_type* event) {
    if (recv(client_sockfd, buffer, FRAME_SIZE, 0) != FRAME_SIZE) {
        printf("No more frames received!\n");
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
    int r = rand() % TOTAL_W;
    if (r < FRAME_ARRIVAL_W)
        *event = frame_arrival;
    else
        *event = cksum_err;
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

//checkSum error check
void sendCkSumErrorFrame() {
    frame f;
    f.ack = 1 - ((frame*)buffer)->seq;
    *(frame*)checksumBuffer = f;
    if (write(client_sockfd, checksumBuffer, FRAME_SIZE) == ERROR) {
        printf("Error in sending frame!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    memset(checksumBuffer, 0, FRAME_SIZE);  // clear the buffer
}

/**
 * Extract the packet from the frame
 */
void extractData(frame* frm, packet* pkt) { *pkt = frm->info; }

//printing the packets
void deliverData(packet* pkt) { printf("[Message Received]: %s", pkt->data); }

//driver code
int main() {
    // Creating a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        perror("socket() returned error code! ");
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
        perror("bind() returned error code! ");
        close(sockfd);
        return EXIT_FAILURE;
    }

    //listening for clients
    if (listen(sockfd, MAX_QUEUE) == ERROR) {
        perror("listen() returned error code! ");
        close(sockfd);
        return EXIT_FAILURE;
    }
    struct sockaddr_in client_addr;  // a sockaddr_in for client
    unsigned int addrlen = sizeof(client_addr);

    printf("Server listening!\n");

    //accepting the clients
    client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    if (client_sockfd == ERROR) {
        perror("accept() returned error code! ");
        close(sockfd);
        return EXIT_FAILURE;
    }

    printf("Connected successfully Waiting for packets!\n");
    srand(time(NULL));

    //receiver communications
    receiver();
    printf("No more frames received!\n");

    //closing the sockts
    close(sockfd);
}