#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char ** argv) {
    (void)argc;

    struct addrinfo * result;
    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };

    signal(SIGPIPE, SIG_IGN);

    int err = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (err) {
        fprintf(stderr, "cannot get addr info\n");
        return 0;
    }

    int sfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        fprintf(stderr, "cannot create socket\n");
        return 0;
    }

    int ret = connect(sfd, result->ai_addr, result->ai_addrlen);
    if (ret < 0) {
        fprintf(stderr, "cannot connect to server\n");
        return 0;
    }
    freeaddrinfo(result);

    int sfd2 = dup(sfd);
    FILE * rf = fdopen(sfd, "r");
    FILE * wf = fdopen(sfd2, "w");

    ret = fprintf(wf, "%s\n", argv[3]);
    fflush(wf);
    if (ret < 0) {
        fprintf(stderr, "cannot write to socket\n");
        return 0;
    }

    int k;
    ret = fscanf(rf, "%d", &k);
    if (ret < 0) {
        fprintf(stderr, "cannot read from socket\n");
        return 0;
    }

    for (int i = 0; i <= k; ++i) {
        ret = fprintf(wf, "%d", i);
        fflush(wf);
        if (ret < 0) {
            fprintf(stderr, "cannot write to socket\n");
            return 0;
        }
    }

    unsigned long long val;
    ret = fscanf(rf, "%llu", &val);
    if (ret < 0) {
        fprintf(stderr, "cannot read from socket\n");
        return 0;
    }

    printf("%llu\n", val);
    fflush(stdout);
    fclose(rf);
    fclose(wf);
    return 0;
}
