/*
 * ColorSensor.cpp
 *
 *  Created on: Mar 31, 2024
 *      Author: 纸鸢
 */

#include <ColorSensor.h>

ColorSensor::ColorSensor() {
	SwicthI2c(1);
	TCS34725_Init();
	HAL_Delay(1000);
}


Sepan_RGBC ColorSensor::DetectColor()
{
	COLOR_RGBC rgb;
	COLOR_HSL hsl;
	Sepan_RGBC rgb_255A;
	TCS34725_GetRawData(&rgb);
	RGBtoHSL(&rgb, &hsl);
	RGBto255RGB(&rgb, &rgb_255A);
	return rgb_255A;
}

void ColorSensor::Open()
{
	this->should_render = true;
}

void ColorSensor::Close()
{
	this->should_render = false;
}

void ColorSensor::AddEventHandler(std::function<void(Sepan_RGBC)> callback)
{
	this->callback = callback;
}

void ColorSensor::Invoke()
{
	if(this->should_render)
	{
		auto result = this->DetectColor();
		this->callback(result);
	}
}


bool range(int8_t a, int8_t b, int8_t value)
{
	return a < value && value < b;
}

uint8_t ColorSensor::ParseColor(uint8_t red, uint8_t green, uint8_t blue)
{
	int maxVal;
	int minVal;

	if(red > green && red > blue)
	{
		auto diff_r_to_g = red - green;
		auto diff_r_to_b = red - blue;

		if(diff_r_to_g > 70 || diff_r_to_b > 70)
			return 3; //红色当作灰色
	}

	if(green > red && green > blue)
	{
		auto diff_g_to_r = green - red;
		auto diff_g_to_b = green - blue;

		if(diff_g_to_r > 150 || diff_g_to_b > 150)
			return 1; //绿色
	}

	if(blue > green && blue > red)
	{
		auto diff_b_to_r = blue - red;
		auto diff_b_to_g = blue - green;

		if(diff_b_to_r > 70 || diff_b_to_g > 70)
			return 2; //蓝色
	}

	if(red > green && red > blue && 0)
	{
		//传感器原因不考虑
		auto diff_r_to_g = red - green;
		auto diff_r_to_b = red - blue;

		if(range(40, 65, diff_r_to_b) && range(135, 170, diff_r_to_g))
			return 3; //黄色(当作灰色)
	}

	return 4;	//无效检验
}



