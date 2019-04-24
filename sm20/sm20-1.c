#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    struct addrinfo * temp;
    struct addrinfo * result;
    struct addrinfo hints = { .ai_family = AF_INET, .ai_socktype = SOCK_STREAM };
    char host_in[1000], service_in[1000];

    while (scanf("%s %s", &host_in, &service_in) != EOF) {
        printf("%s___%s\n", host_in, service_in);

        int ret_code;

        ret_code = getaddrinfo(host_in, service_in, &hints, &result);
        if (ret_code) {
            printf("%s\n", gai_strerror(ret_code));
            continue;
        }
    }
}
