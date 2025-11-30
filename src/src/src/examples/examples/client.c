#include "../src/tcp_adapter.h"
#include <stdio.h>

int main() {
    char response[1024];
    tcp_client_send("127.0.0.1", 6000, "Hello IPC!", response);

    printf("Response: %s\n", response);
    return 0;
}
