/*
 * GpioExtiPin.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#ifndef INC_GPIOEXTIPIN_H_
#define INC_GPIOEXTIPIN_H_

#include <InPin.h>
#include <functional>

#include <InterruptServiceManager.h>

class GpioExtiPin: protected InPin {
public:
	GpioExtiPin(GPIO_TypeDef * gpio, uint16_t pin);
	virtual ~GpioExtiPin();
	void AddEventHandler(std::function<bool()> handler);
};

#endif /* INC_GPIOEXTIPIN_H_ */
