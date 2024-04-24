/*
 * InPin.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#ifndef INC_INPIN_H_
#define INC_INPIN_H_

#include <Pin.h>

class InPin: protected Pin {
public:
	InPin(GPIO_TypeDef * gpio, uint16_t pin);
	virtual ~InPin();
};

#endif /* INC_INPIN_H_ */
