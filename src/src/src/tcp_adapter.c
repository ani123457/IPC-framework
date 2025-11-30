#include "tcp_adapter.h"
#include "ipc_core.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int tcp_server_start(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[2048];
    char unpacked[1024];
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server listening on port %d...\n", port);

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

        int bytes = read(new_socket, buffer, 2048);
        unpack_message(buffer, bytes, unpacked);

        printf("Received: %s\n", unpacked);

        char packed[2048];
        uint32_t outlen;
        pack_message(unpacked, packed, &outlen);
        
        write(new_socket, packed, outlen);
        close(new_socket);
    }
}

int tcp_client_send(const char *server_ip, int port, const char *msg, char *response) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char packed[2048];
    uint32_t outlen;

    pack_message(msg, packed, &outlen);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, packed, outlen, 0);

    char buffer[2048];
    int bytes = read(sock, buffer, 2048);

    unpack_message(buffer, bytes, response);
    close(sock);
    return 0;
}
