#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

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

        char ipmin_str[INET_ADDRSTRLEN];
        unsigned long ipmin_binary;
        unsigned short ipmin_port;
        bool is_first = true;

        for(temp = result; temp != NULL; temp = temp->ai_next) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)temp->ai_addr;
            void* addr = &(ipv4->sin_addr);
            inet_ntop(temp->ai_family, addr, ipstr, sizeof ipstr);
            int port = ntohs( ((struct sockaddr_in *)( (struct sockaddr *)temp->ai_addr ))->sin_port );
            // printf("  %s: %s\n", ipver, ipstr);
            printf("\t%s:%d\n", ipstr, port);

            unsigned long lol = ipv4->sin_addr.s_addr;
            lol = ntohl(lol);

            if (is_first) {
                is_first = false;
                strcpy(ipstr, ipmin_str);
                ipmin_binary = lol;
                ipmin_port = port;
            } else if (lol < ipmin_binary) {
                strcpy(ipmin_str, ipstr);
                ipmin_binary = lol;
                ipmin_port = port;
            }
        }

        printf("%s:%d\n", ipmin_str, ipmin_port);

        freeaddrinfo(result); // free the linked list
    }
}
