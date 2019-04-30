#include <arpa/inet.h>      // Internet stuff
#include <netdb.h>          // Internet stuff
#include <netinet/in.h>     // Internet stuff
#include <signal.h>         // Used to ignore SIGPIPE
#include <stdio.h>          // Ints and other stuff
#include <stdlib.h>         // Used for _exit() calls
// #include <string.h>
#include <sys/types.h>      // Internet stuff
#include <sys/socket.h>     // Internet stuff
// #include <unistd.h>

int main(int argc, char * argv[]) {
    if (argc != 2) { return 0; }
    int sum = 0, number_in;
    signal(SIGPIPE, SIG_IGN);

    // initializing socket, saving it's file descriptor
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) { return 0; }

    int value = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(socket_fd));
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &value, sizeof(socket_fd));

    // describing address
    unsigned short port_in = strtol(argv[1], NULL, 10);
    struct sockaddr_in address = { .sin_addr.s_addr = INADDR_ANY, .sin_family = AF_INET, .sin_port = htons(port_in) };

    // bind
    int ret_code;
    ret_code = bind(socket_fd, (struct sockaddr *) &address, sizeof(address));
    if (ret_code < 0) { return 0; }

    // listen
    ret_code = listen(socket_fd, 5);
    if (ret_code < 0) { return 0; }

    while (42) {
        int size = sizeof(address);
        int single_conn_fd = accept(socket_fd, (struct sockaddr *) &address, (socklen_t *)&size);
        if (single_conn_fd < 0) { _exit(0); }

        ret_code = read(single_conn_fd, &number_in, sizeof(number_in));
        if (ret_code < sizeof(number_in)) { _exit(0); }

        if (number_in != 0) {
            sum += ntohl(number_in);
            close(single_conn_fd);
        } else {
            close(single_conn_fd);
            break;
        }
    }

    printf("%d\n", sum);
    fflush(stdout);
    close(socket_fd);
    return 0;
}
