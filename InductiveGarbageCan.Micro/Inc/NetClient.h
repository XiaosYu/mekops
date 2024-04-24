/*
 * NetClient.h
 *
 *  Created on: Mar 15, 2024
 *      Author: 纸鸢
 */

#ifndef INC_NETCLIENT_H_
#define INC_NETCLIENT_H_

#include "esp8266.h"
#include "Component.h"
#include <functional>

class NetClient: public Component {
public:
	NetClient(const char* address, int port);
	virtual ~NetClient();

	bool GetConnectionStatus();
	void SendBytes(char* bytes);
	void SendByte(unsigned char byte);

	static void ConnectWifi(char* ssid, char* pwd);

private:
	bool is_connected;
};

extern std::function<void(uint8_t data[])> callback;

#endif /* INC_NETCLIENT_H_ */
