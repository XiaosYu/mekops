/*
 * InterruptServiceManager.h
 *
 *  Created on: Mar 28, 2024
 *      Author: 纸鸢
 */

#ifndef INC_INTERRUPTSERVICEMANAGER_H_
#define INC_INTERRUPTSERVICEMANAGER_H_

#include "main.h"
#include "gpio.h"
#include <map>
#include <functional>
#include <Component.h>

struct InterruptEvent
{
	std::function<bool()> callback;
	uint16_t pin;
	bool loop;
};

class InterruptServiceManager: public Component {
public:
	void AddInterruptCallback(uint16_t pin, std::function<bool()> callback);
	void Invoke(uint16_t pin);

	static InterruptServiceManager* Shared;
private:
	std::map<uint16_t, InterruptEvent*> dictionary;

};





#endif /* INC_INTERRUPTSERVICEMANAGER_H_ */
