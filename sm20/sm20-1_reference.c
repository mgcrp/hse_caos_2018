#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

// A part added by @mgcrp
// get port, IPv4 or IPv6:
in_port_t get_in_port(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return (((struct sockaddr_in*)sa)->sin_port);
    }

    return (((struct sockaddr_in6*)sa)->sin6_port);
}


int main(int argc, char *argv[]) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: %s HOST", argv[0]);
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    if ((status = getaddrinfo(argv[1], "http", &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    printf("IP addresses for %s:\n\n", argv[1]);

    for(p = res;p != NULL; p = p->ai_next) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        void* addr = &(ipv4->sin_addr);
        char* ipver = "IPv4";

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);

        // A part added by @mgcrp
        // printf("port is %d\n",ntohs(get_in_port((struct sockaddr *)p->ai_addr)));
        printf("*** %d\n", ntohs( ((struct sockaddr_in *)( (struct sockaddr *)p->ai_addr ))->sin_port ) );
    }

    freeaddrinfo(res); // free the linked list

    return 0;
}
