/*
 * Timer.cpp
 *
 *  Created on: Mar 31, 2024
 *      Author: 纸鸢
 */

#include <Timer.h>

Timer* Timer::Shared = new Timer();

Timer::Timer() {
	// TODO 自动生成的构造函数存根
	srand(time(NULL));
}

uint16_t Timer::RegisterTask(uint32_t time, std::function<bool()> callback)
{
	TimeTask* task = new TimeTask();

	uint16_t random_value = rand() % 10000; // 取余得到0到100000之间的随机数

	task->time = time;
	task->current = 0;
	task->callback = callback;
	task->loop = true;
	task->id = random_value;
	this->tasks.push_back(task);

	return random_value;
}


TimeTask* Timer::FindTask(uint16_t id)
{
	for(auto task: this->tasks)
	{
		if(task->id == id)
			return task;
	}
	return NULL;
}

void Timer::Cancel(uint16_t id)
{
	auto timeTask = this->FindTask(id);
	timeTask->loop = false;
}

void Timer::Start()
{
	this->should_render = true;
}


void Timer::Stop()
{
	this->should_render = false;
}

void Timer::Invoke()
{
	if(this->should_render)
	{
		bool should_delete = false;

		for(auto task: this->tasks)
		{
			if(task->loop)
			{
				task->current += 100;
				if(task->current >= task->time)
				{
					task->loop = task->callback();
					task->current = 0;
				}
			}
			else
			{
				should_delete = true;
			}
		}

		if(should_delete)
		{
			std::vector<TimeTask*> temp_tasks;
			for(auto task: this->tasks)
			{
				if(task->loop)
					temp_tasks.push_back(task);
				else {
					delete task;
				}
			}
			this->tasks.clear();
			for(auto task: temp_tasks)
				this->tasks.push_back(task);

			should_delete = false;
		}
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM1)	//如果是定时器1到期
	{
		Timer::Shared->Invoke();
	}
}


