/*
 * Pin.cpp
 *
 *  Created on: Mar 18, 2024
 *      Author: 纸鸢
 */

#include <Pin.h>

Pin::Pin(GPIO_TypeDef * gpio, uint16_t pin)
{
	this->gpio = gpio;
	this->pin = pin;
}

void Pin::Write(GPIO_PinState state)
{
	HAL_GPIO_WritePin(this->gpio, this->pin, state);
}

GPIO_PinState Pin::Read()
{
	GPIO_PinState result;
	result = HAL_GPIO_ReadPin(gpio, pin);
	return result;
}

