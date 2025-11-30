#include "ipc_core.h"
#include <string.h>
#include <arpa/inet.h>

int pack_message(const char *payload, char *buffer, uint32_t *out_len) {
    uint32_t len = strlen(payload);
    uint32_t net_len = htonl(len);

    memcpy(buffer, &net_len, 4);
    memcpy(buffer + 4, payload, len);

    *out_len = len + 4;
    return 0;
}

int unpack_message(const char *buffer, uint32_t buffer_len, char *out_payload) {
    if(buffer_len < 4) return -1;

    uint32_t len;
    memcpy(&len, buffer, 4);
    len = ntohl(len);

    memcpy(out_payload, buffer + 4, len);
    out_payload[len] = '\0';

    return 0;
}
