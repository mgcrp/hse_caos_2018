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

    char host_in[1000], service_in[1000];
    while (scanf("%s %s", host_in, service_in) != EOF) {
        int ret_code = getaddrinfo(host_in, service_in, &hints, &result);
        if (ret_code) {
            printf("%s\n", gai_strerror(ret_code));
            continue;
        }

        bool is_first = true;
        unsigned short ipmin_port;
        unsigned long ipmin_binary;
        char ipmin_str[INET_ADDRSTRLEN], ipcur_str[INET_ADDRSTRLEN];

        for (temp = result; temp != NULL; temp = temp->ai_next) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)temp->ai_addr;
            void* addr = &(ipv4->sin_addr);

            unsigned long ipcur_binary = ntohl(ipv4->sin_addr.s_addr);
            inet_ntop(temp->ai_family, addr, ipcur_str, sizeof ipcur_str);
            unsigned short ipcur_port = ntohs(((struct sockaddr_in *)((struct sockaddr *)temp->ai_addr))->sin_port);

            // DEBUG
            // printf("\t%s:%d\t%x\n", ipcur_str, ipcur_port, ipcur_binary);

            if (is_first) {
                // DEBUG
                // printf("\t\tFirst came in!\n");
                is_first = false;
                strcpy(ipmin_str, ipcur_str);
                ipmin_binary = ipcur_binary;
                ipmin_port = ipcur_port;
            } else if (ipcur_binary < ipmin_binary) {
                // DEBUG
                // printf("\t\tMinimum value changed!\n");
                strcpy(ipmin_str, ipcur_str);
                ipmin_binary = ipcur_binary;
                ipmin_port = ipcur_port;
            }
        }

        printf("%s:%d\n", ipmin_str, ipmin_port);

        freeaddrinfo(result); // free the linked list
    }
}
