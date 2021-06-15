/*Sender side implementation of noisy stop and wait protocol*/

//header files
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define ERROR -1
#define PORT 11111
#define LOCALHOST "127.0.0.1"

#define MAX_PKT 1024
#define FRAME_SIZE sizeof(frame)

//probability weights of events
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

seq_nr next_frame_to_send;

//sender communications
void sender(void) {
    packet p;
    frame f;
    event_type event = frame_arrival;
    next_frame_to_send = 0;
    int n = 10;
    getData(&p);  // get packet from network layer
    n--;
    while (1) {
        makeFrame(&f, &p);  // create a frame
        f.seq = next_frame_to_send;
        sendFrame(&f);         // send the frame to physical layer
        waitForEvent(&event);  // wait for dummy acknowledgement
        if (event == frame_arrival) {
            receiveFrame(&f);
            if (f.ack == next_frame_to_send) {
                printf("Acknowledgement Received!\n");
                if (n == 0) break;
                getData(&p);  // get packet from network layer
                n--;
                next_frame_to_send = (next_frame_to_send + 1) % 2;
            } else {
                // signifies timeout!
                printf("No Acknowledgement, Timeout!\n");
                printf("Sending message again!\n");
            }
        } else if (event == cksum_err) {
            printf("Checksum error in Acknowledgement Frame!\n");
            printf("Sending message again!\n");
        }
        fflush(stdin);
    }
}

/**
 * Get data 
 */
void getData(packet* pkt) {
    static int i = 1;
    memset(pkt, 0, sizeof(packet));
    // printf("\nEnter a message: ");
    // fgets(pkt->data, MAX_PKT, stdin);
    sprintf(pkt->data, "packet number %d\n", i++);
    printf("[Sending message]: %s", pkt->data);
}

/**
 * make a frame using the given packet.
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
    if (recv(sockfd, buffer, FRAME_SIZE, 0) != FRAME_SIZE) {
        printf("Error in receiving data!\n");
        close(sockfd);
        exit(EXIT_SUCCESS);
    }
    if (((frame*)buffer)->ack == next_frame_to_send) {
        int r = rand() % TOTAL_W;
        if (r < FRAME_ARRIVAL_W)
            *event = frame_arrival;        //randomness added to make the sockets noisy
        else if (r < FRAME_ARRIVAL_W + CKSUM_ERR_W)
            *event = cksum_err;
    } else {
        *event = frame_arrival;
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

//driver code
int main() {
    // create a socket and store file descriptor
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
    // sending 5 packets
    srand(time(NULL));

    //sender communications
    sender();
    close(sockfd);  //closing the sockets
}