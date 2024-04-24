/*
 * Servos.h
 *
 *  Created on: Apr 3, 2024
 *      Author: 纸鸢
 */

#ifndef SRC_SERVOS_H_
#define SRC_SERVOS_H_

#include <Component.h>
#include <tim.h>

class Servos: public Component {
public:
	Servos(uint8_t id);

	bool GetStatus();
	void Open();
	void Close();

private:
	bool status = false;
	uint8_t id;


};

#endif /* SRC_SERVOS_H_ */
