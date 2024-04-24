/*
 * ColorSensor.h
 *
 *  Created on: Mar 31, 2024
 *      Author: 纸鸢
 */

#ifndef INC_COLORSENSOR_H_
#define INC_COLORSENSOR_H_

#include <Component.h>
#include <tcs34725.h>
#include <Timer.h>
#include <functional>

class ColorSensor: public Component {
public:
	ColorSensor();

	Sepan_RGBC DetectColor();

	static uint8_t ParseColor(uint8_t r, uint8_t g, uint8_t b);

	void Open();
	void Close();
	void AddEventHandler(std::function<void(Sepan_RGBC)> callback);
	void Invoke();

	uint16_t id = 0;

private:
	bool should_render = true;
	std::function<void(Sepan_RGBC)> callback;

};

#endif /* INC_COLORSENSOR_H_ */
