#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        _exit(0);
    }
    struct sockaddr_in ain = {
            .sin_family = AF_INET,
            .sin_port = htons(atoi(argv[1])),
            .sin_addr.s_addr = INADDR_ANY
    };
    int val = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
    if (bind(sfd, (void*)&ain, sizeof(ain)) < 0) {
        _exit(0);
    }
    if (listen(sfd, 5) < 0) {
        _exit(0);
    }
    int result = 0, num = -1;
    while (num != 0) {
        struct sockaddr_in sa;
        socklen_t slen = sizeof(sa);
        int afd = accept(sfd, (void*) &sa, (unsigned*)&slen);
        if (afd < 0) {
            _exit(0);
        }
        if (read(afd, &num, sizeof(num)) < sizeof(num)) {
            _exit(0);
        }
        num = ntohl(num);
        result += num;
        close(afd);
    }
    close(sfd);
    printf("%d\n", result);
    fflush(stdout);
}
