#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char * argv[]) {
    // checking if we get exactly 3 command line arguments
    if (argc != 4) { return 0; }

    // initializing stuff
    struct addrinfo * server;
    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    signal(SIGPIPE, SIG_IGN);

    // getting address info
    int ret_code = getaddrinfo(argv[1], argv[2], &hints, &server);
    if (ret_code) { return 0; }

    // initializing socket, saving it's file descriptor
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) { return 0; }

    // setting up connection
    ret_code = connect(socket_fd, server->ai_addr, server->ai_addrlen);
    if (ret_code < 0) { return 0; }

    // initializing read and write streams
    int socket_fd2 = dup(socket_fd);
    FILE * read_stream = fdopen(socket_fd, "r");
    FILE * write_stream = fdopen(socket_fd2, "w");

    // sending word from argv[3] -> to server
    ret_code = fprintf(write_stream, "%s\n", argv[3]);
    fflush(write_stream);
    if (ret_code < 0) { return 0; }

    // recieving number <- from server
    int number;
    ret_code = fscanf(read_stream, "%d", &number);
    if (ret_code < 0) { return 0; }

    // sending numbers from 0 to {number} -> to server
    for (int i = 0; i <= number; ++i) {
        ret_code = fprintf(write_stream, "%d\n", i);
        fflush(write_stream);
        if (ret_code < 0) { return 0; }
    }

    // recieving final number <- from server
    unsigned long long answer;
    ret_code = fscanf(read_stream, "%llu", &answer);
    if (ret_code < 0) { return 0; }
    printf("%llu\n", answer);

    // finishing program
    fflush(stdout);
    fclose(read_stream);
    fclose(write_stream);
    return 0;
}
