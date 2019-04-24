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
    char host_in[1000], service_in[1000], ipstr[INET_ADDRSTRLEN];

    while (scanf("%s %s", &host_in, &service_in) != EOF) {
        int ret_code;

        ret_code = getaddrinfo(host_in, service_in, &hints, &result);
        if (ret_code) {
            printf("%s\n", gai_strerror(ret_code));
            continue;
        }

        for(temp = result; temp != NULL; temp = temp->ai_next) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)temp->ai_addr;
            void* addr = &(ipv4->sin_addr);
            inet_ntop(temp->ai_family, addr, ipstr, sizeof ipstr);
            int port = ntohs( ((struct sockaddr_in *)( (struct sockaddr *)temp->ai_addr ))->sin_port );
            // printf("  %s: %s\n", ipver, ipstr);
            printf("%s:%d\n", ipstr, port);

            printf("%X\n", ntohl( addr.s_addr );
        }

        freeaddrinfo(result); // free the linked list
    }
}
