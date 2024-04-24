#include "esp8266.h"


void send_command(const char* command)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)command, strlen(command), 10000);
}

void connect_wifi(const char* ssid, const char* pass)
{
	char cmd[100];
	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pass);
	send_command(cmd);
}

void connect_server(const char* server_iP, int server_port)
{
	char cmd[100];
	sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", server_iP, server_port);
	send_command(cmd);
}

void send(const char* data)
{
	char cmd[100];
	sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(data));
	send_command(cmd);
	HAL_Delay(100);
	send_command(data);
}

void close_tcp(void)
{
	send_command("AT+CIPCLOSE\r\n");
}

