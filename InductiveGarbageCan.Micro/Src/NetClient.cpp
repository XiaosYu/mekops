/*
 * NetClient.cpp
 *
 *  Created on: Mar 15, 2024
 *      Author: 纸鸢
 */

#include <NetClient.h>


NetClient::NetClient(const char* address, int port) {
	connect_server(address, port);
	this->is_connected = true;
}

NetClient::~NetClient() {
	if(this->is_connected)
	{
		close_tcp();
	}
}

bool NetClient::GetConnectionStatus(){
	return this->is_connected;
}

void NetClient::ConnectWifi(char* ssid, char* pwd){
	connect_wifi(ssid, pwd);
}

void NetClient::SendBytes(char* bytes){
	send(bytes);
}

void NetClient::SendByte(unsigned char byte){
	unsigned char data[2] = {byte, '\0'};
	send((char*)data);
}
