/*
 * RemoteDataContext.cpp
 *
 *  Created on: Mar 15, 2024
 *      Author: 纸鸢
 */

#include <RemoteDataContext.h>

std::vector<std::function<void(Command)>> events;

RemoteDataContext::RemoteDataContext(const char* address, int port): NetClient(address, port)
{

}

RemoteDataContext::~RemoteDataContext() {}

void RemoteDataContext::AddThrowEvent(char triggerCans){
	SendTask task;
	task.trigger_cans = triggerCans;
	task.event_type = 1;
	this->tasks.push_back(task);
	this->should_render = true;
}

void RemoteDataContext::AddClearEvent(char triggerCans){
	SendTask task;
	task.trigger_cans = triggerCans;
	task.event_type = 2;
	this->tasks.push_back(task);
	this->should_render = true;
}

void RemoteDataContext::AddWarningEvent(char triggerCans){
	SendTask task;
	task.trigger_cans = triggerCans;
	task.event_type = 0;
	this->tasks.push_back(task);
	this->should_render = true;
}

void RemoteDataContext::Invoke()
{
	if(this->should_render)
	{
		for (std::list<SendTask>::iterator it = this->tasks.begin(); it != this->tasks.end(); ++it)
		{
			auto data = this->CombineData((*it).event_type, (*it).trigger_cans);
			this->SendByte(data);
		}
		this->tasks.clear();
		this->should_render = false;
	}
}

void RemoteDataContext::AddEventHandler(std::function<void(Command)> handler)
{
	events.push_back(handler);
}

unsigned char RemoteDataContext::CombineData(unsigned char triggerEvent, unsigned char triggerCans){
    unsigned char byte;

    byte = 0b11100000;

    byte |= (triggerEvent << 2);
    byte |= triggerCans;

	return byte;
}
