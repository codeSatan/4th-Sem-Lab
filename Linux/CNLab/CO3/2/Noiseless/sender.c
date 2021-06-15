/*Sender side implementation of stop and wait protocol noiseless*/

//header files
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define ERROR -1
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
int sockfd;               // client socket file descriptor

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


//sender communicationd
void sender(void) {
    packet p;
    frame f;
    event_type event;
    int n = 5;
    for (int pktno = 1; pktno <= n; pktno++) {
        getData(&p);           // get packet from network layer
        makeFrame(&f, &p);     // create a frame
        sendFrame(&f);         // send the frame to physical layer
        waitForEvent(&event);  // wait for dummy acknowledgement
        if (event == frame_arrival) {
            printf("Received acknowledgement!\n");
        }
    }
}

/**
 * Getting data from network layer is simulated by asking user
 * for input, the entered string is considered as data
 */
void getData(packet* pkt) {
    memset(pkt, 0, sizeof(packet));
    printf("Enter a message: ");
    fgets(pkt->data, MAX_PKT, stdin);
}

/**
 * make a frame 
 */
void makeFrame(frame* frm, packet* pkt) {
    memset(frm, 0, sizeof(frame));
    frm->info = *pkt;
    frm->kind = data;
}

/**
 * Send frame to the destination machine
 */
void sendFrame(frame* f) {
    frame* fbuffer = (frame*)buffer;
    *fbuffer = *f;
    if (write(sockfd, buffer, FRAME_SIZE) == ERROR) {
        printf("Error in sending frame!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

/**
 * Wait for frame arrival
 */
void waitForEvent(event_type* event) {
    if (recv(sockfd, buffer, FRAME_SIZE, 0) == FRAME_SIZE) {
        *event = frame_arrival;
    } else {
        printf("Error in receiving data!\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

//driver code
int main() {
    // create a socket of TCP/IP type
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        perror("socket() returned error code! ");
        return EXIT_FAILURE;
    }

    // port on which the server we want to connect to is listening
    unsigned short port = PORT;

    // sockaddr_in for server we want to connect to
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;    // AF_INET implies IPv4
    server_addr.sin_port = htons(port);  // converting host BO to network BO
    server_addr.sin_addr.s_addr = inet_addr(LOCALHOST);
    bzero(&server_addr.sin_zero, 8);  // set padding to zeroes

    // connect to the server
    if ((connect(sockfd, (struct sockaddr*)&server_addr,
                 sizeof(server_addr))) == ERROR) {
        perror("connect() returned error code! ");
        close(sockfd);
        return EXIT_FAILURE;
    }
    //sender communications
    sender();
    close(sockfd);
}