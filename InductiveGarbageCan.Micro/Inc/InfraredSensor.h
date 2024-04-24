/*
 * InfraredSensor.h
 *
 *  Created on: Apr 1, 2024
 *      Author: 纸鸢
 */

#ifndef INC_INFRAREDSENSOR_H_
#define INC_INFRAREDSENSOR_H_

#include <GpioExtiPin.h>

class InfraredSensor: public GpioExtiPin {
public:
	InfraredSensor(GPIO_TypeDef * gpio, uint16_t pin);
	bool IsDetected();
};

#endif /* INC_INFRAREDSENSOR_H_ */
