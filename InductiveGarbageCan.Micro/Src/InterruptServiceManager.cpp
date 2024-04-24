#include "InterruptServiceManager.h"


InterruptServiceManager* InterruptServiceManager::Shared = new InterruptServiceManager();

void InterruptServiceManager::AddInterruptCallback(uint16_t pin, std::function<bool()> callback)
{
	InterruptEvent* event = new InterruptEvent();
	event->pin = pin;
	event->callback = callback;
	event->loop = true;
	this->dictionary[pin] = event;
}

void InterruptServiceManager::Invoke(uint16_t pin)
{
	auto exsist = this->dictionary.find(pin);
	if(exsist != this->dictionary.end())
	{
		auto event = (exsist->second);
		if(event->loop)
		{
			event->loop = event->callback();
		}
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	InterruptServiceManager::Shared->Invoke(pin);
}

