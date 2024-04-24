/*
 * Pin.h
 *
 *  Created on: Mar 18, 2024
 *      Author: 纸鸢
 */

#ifndef INC_PIN_H_
#define INC_PIN_H_

#include <gpio.h>
#include "Component.h"

class Pin: public Component{
public:
	Pin(GPIO_TypeDef * gpio, uint16_t pin);

protected:
	void Write(GPIO_PinState state);
	GPIO_PinState Read();
	uint16_t GetPin()
	{
		return this->pin;
	}

private:
	GPIO_TypeDef * gpio;
	uint16_t pin;

};




#endif /* INC_PIN_H_ */
