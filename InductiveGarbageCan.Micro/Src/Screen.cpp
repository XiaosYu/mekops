/*
 * Screen.cpp
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#include <Screen.h>

Screen::Screen()
{
	OLED_Init();
}

void Screen::Invoke()
{
	if(this->should_render)
	{
		OLED_Clear();
		for (size_t i = 0; i < this->positions.size(); ++i)
		{
			auto position = this->positions[i];
			if(position.command == 0)
			{
				OLED_ShowString(position.x1, position.y1, (char*)position.args.c_str(), 16);
			}
		}

		this->should_render = false;
	}
}

void Screen::PrintChinese(uint8_t x0, uint8_t y0, uint8_t id)
{
	Point p;
	p.command = 2;
	p.x1 = x0;
	p.y1 = y0;
	p.x2 = id;

	this->positions.push_back(p);
	this->should_render = true;
}

void Screen::Clear()
{
	this->positions.clear();
	this->should_render = true;
}

void Screen::PrintImage(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, const uint8_t BMP[])
{
	Point p;
	p.command = 1;
	p.x1 = x0;
	p.y1 = y0;
	p.x2 = x1;
	p.y2 = y1;
	p.data = const_cast<uint8_t*>(BMP);

	this->positions.push_back(p);
	this->should_render = true;
}

void Screen::PrintText(uint8_t x, uint8_t y, std::string text)
{
	Point p;
	p.command = 0;
	p.x1 = x;
	p.y1 = y;
	p.args = text;

	this->positions.push_back(p);
	this->should_render = true;
}
