
#ifndef IPC_CORE_H
#define IPC_CORE_H

#include <stdint.h>

#define MAX_MSG_SIZE 1024

typedef struct {
    uint32_t length;
    char data[MAX_MSG_SIZE];
} Message;

// pack and unpack
int pack_message(const char *payload, char *buffer, uint32_t *out_len);
int unpack_message(const char *buffer, uint32_t buffer_len, char *out_payload);

#endif


