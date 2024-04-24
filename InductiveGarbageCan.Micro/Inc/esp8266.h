#ifndef __ESP8266_H__
#define __ESP8266_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include "usart.h"


void send_command(const char* command);
void connect_wifi(const char* ssid, const char* pass);
void connect_server(const char* serverIP, int server_port);
void send(const char* data);
void close_tcp(void);

#ifdef __cplusplus
}
#endif


#endif
