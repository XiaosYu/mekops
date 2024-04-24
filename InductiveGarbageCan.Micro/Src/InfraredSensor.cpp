/*
 * InfraredSensor.cpp
 *
 *  Created on: Apr 1, 2024
 *      Author: 纸鸢
 */

#include <InfraredSensor.h>

InfraredSensor::InfraredSensor(GPIO_TypeDef * gpio, uint16_t pin): GpioExtiPin(gpio, pin) {
	// TODO 自动生成的构造函数存根

}


bool InfraredSensor::IsDetected()
{
	bool result;
	result = this->Read();
	return !result;
}




