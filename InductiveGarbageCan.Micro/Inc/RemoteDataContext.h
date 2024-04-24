/*
 * RemoteDataContext.h
 *
 *  Created on: Mar 15, 2024
 *      Author: 纸鸢
 */

#ifndef INC_REMOTEDATACONTEXT_H_
#define INC_REMOTEDATACONTEXT_H_

#include <NetClient.h>
#include <cstring>
#include <list>
#include <vector>
#include <functional>


struct SendTask
{
	uint8_t event_type;
	uint8_t trigger_cans;
};


struct Command
{
	uint8_t command;
	uint8_t trigger_cans;
};


class RemoteDataContext: private NetClient {
public:
	RemoteDataContext(const char* address, int port);
	virtual ~RemoteDataContext();

	void AddThrowEvent(char triggerCans);
	void AddClearEvent(char triggerCans);
	void AddWarningEvent(char triggerCans);

	void AddEventHandler(std::function<void(Command)> handler);

	void Invoke();

private:
	unsigned char CombineData(unsigned char triggerEvent, unsigned char triggerCans);
	static void OnReceivedMessage(uint8_t data[]);

	char triggerCans = -1;
	char eventType = -1;

	std::list<SendTask> tasks;

	bool should_render = false;
};


extern std::vector<std::function<void(Command)>> events;



#endif /* INC_REMOTEDATACONTEXT_H_ */
