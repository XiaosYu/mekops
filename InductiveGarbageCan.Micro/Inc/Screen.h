/*
 * Screen.h
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include <Component.h>
#include <oled.h>

#include <vector>
#include <string>


struct Point
{
	uint8_t x1;
	uint8_t y1;
	uint8_t x2;
	uint8_t y2;
	unsigned char command;
	std::string args;
	uint8_t* data;
};


class Screen: public Component {
public:
	Screen();
	void PrintText(uint8_t x, uint8_t y, std::string text);
	void PrintImage(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, const uint8_t BMP[]);
	void PrintChinese(uint8_t x0, uint8_t y0, uint8_t id);
	void Clear();
	void Invoke();
private:
	std::vector<Point> positions;
	bool should_render = false;
};

#endif /* INC_SCREEN_H_ */
