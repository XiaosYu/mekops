/*
 * Timer.h
 *
 *  Created on: Mar 31, 2024
 *      Author: 纸鸢
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <Component.h>
#include <vector>
#include <functional>
#include <tim.h>
#include <time.h>
#include <stdlib.h>


struct TimeTask
{
	uint16_t id;
	uint32_t time;
	uint32_t current;
	bool loop;
	std::function<bool()> callback;
};



class Timer: public Component {
public:
	Timer();

	uint16_t RegisterTask(uint32_t time, std::function<bool()> callback);
	void Cancel(uint16_t);
	TimeTask* FindTask(uint16_t id);

	void Invoke();

	void Start();
	void Stop();

	static Timer* Shared;

private:
	std::vector<TimeTask*> tasks;
	bool should_render = false;
};

#endif /* INC_TIMER_H_ */
