#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct addrinfo hints = { 
        .ai_family = PF_INET, 
        .ai_socktype = SOCK_STREAM 
    };
    struct addrinfo* result;
    int error = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (error) {
        _exit(0);
    }
    int fd = socket(result->ai_family, result->ai_socktype, 0);
    if (fd < 0) {
        _exit(0);
    }
    error = connect(fd, result->ai_addr, result->ai_addrlen);
    if (error < 0) {
        _exit(0);
    }
    
    int num = atoi(argv[3]);
    num = htonl(num);
    if (write(fd, &num, sizeof(num)) < sizeof(num)) {
        _exit(0);
    }
    close(fd);
    freeaddrinfo(result);
}
