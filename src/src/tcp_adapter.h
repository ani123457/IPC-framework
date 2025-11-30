#ifndef TCP_ADAPTER_H
#define TCP_ADAPTER_H

int tcp_server_start(int port);
int tcp_client_send(const char *server_ip, int port, const char *msg, char *response);

#endif
