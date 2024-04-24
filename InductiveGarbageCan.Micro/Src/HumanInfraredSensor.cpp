/*
 * HumanInfraredSensor.cpp
 *
 *  Created on: Mar 18, 2024
 *      Author: 纸鸢
 */

#include <HumanInfraredSensor.h>

HumanInfraredSensor::HumanInfraredSensor(GPIO_TypeDef * gpio, uint16_t pin): GpioExtiPin(gpio, pin)
{

}


bool HumanInfraredSensor::IsDetected()
{
	bool result;
	result = this->Read();
	return result;
}


