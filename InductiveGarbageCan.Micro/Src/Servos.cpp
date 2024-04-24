/*
 * Servos.cpp
 *
 *  Created on: Apr 3, 2024
 *      Author: 纸鸢
 */

#include "Servos.h"

void SetValue(uint8_t id,uint32_t angle)
{
	//50关 200开
	switch (id)
	{
		case 1:TIM2->CCR1=angle;break;
		case 2:TIM2->CCR2=angle;break;
		case 3:TIM2->CCR3=angle;break;
		case 4:TIM2->CCR4=angle;break;
	}
}

Servos::Servos(uint8_t id) {
	// TODO 自动生成的构造函数存根
	this->id = id;
	this->Close();
}

bool Servos::GetStatus()
{
	return this->status;
}

void Servos::Open()
{
	if(!this->status)
		SetValue(this->id, 160);

	this->status = true;
}

void Servos::Close()
{
	if(this->status)
	{
		SetValue(this->id, 50);
	}

	this->status = false;
}

