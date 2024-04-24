/*
 * HumanInfraredSensor.h
 *
 *  Created on: Mar 18, 2024
 *      Author: 纸鸢
 */

#ifndef INC_HUMANINFRAREDSENSOR_H_
#define INC_HUMANINFRAREDSENSOR_H_

#include "GpioExtiPin.h"

class HumanInfraredSensor: public GpioExtiPin
{
public:
	HumanInfraredSensor(GPIO_TypeDef * gpio, uint16_t pin);
	bool IsDetected();

};




#endif /* INC_HUMANINFRAREDSENSOR_H_ */
