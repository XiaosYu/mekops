/*
 * GpioExtiPin.cpp
 *
 *  Created on: Mar 29, 2024
 *      Author: 纸鸢
 */

#include <GpioExtiPin.h>

GpioExtiPin::GpioExtiPin(GPIO_TypeDef * gpio, uint16_t pin): InPin(gpio, pin)
{
	// TODO 自动生成的构造函数存根

}

GpioExtiPin::~GpioExtiPin() {
	// TODO 自动生成的析构函数存根
}

void GpioExtiPin::AddEventHandler(std::function<bool()> handler)
{
	InterruptServiceManager::Shared->AddInterruptCallback(this->GetPin(), handler);
}

