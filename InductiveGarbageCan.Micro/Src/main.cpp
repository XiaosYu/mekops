/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "RemoteDataContext.h"
#include "HumanInfraredSensor.h"
#include "Screen.h"

#include "Timer.h"
#include "ColorSensor.h"
#include <InfraredSensor.h>
#include <MainScreen.h>
#include <Servos.h>
#include <Process.h>


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
void delay(uint32_t time)
{
	while(time--)
	{
		auto t = 7200;
		while(t--);
	}
}

bool infrared_interrupt(Process* process, Servos* servos, InfraredSensor* infraredSensor, Timer* timer, MainScreen* screen, RemoteDataContext* wifi, int8_t n)
{
	if(process->humanable && process->status == ProcessClose)
	{
		if(servos->GetStatus())
		{
			delay(1300);
			if(infraredSensor->IsDetected())
			{
				//溢满
				if(process->servos_task_id != 0)
					timer->Cancel(process->servos_task_id);
				screen->DisplayText("The cans is overflow");
				process->overflow = true;
				process->status = 0x10;
				wifi->AddWarningEvent(n);
			}
			else
			{
				//未溢满
				servos->Close();
				if(process->servos_task_id != 0)
					timer->Cancel(process->servos_task_id);
				process->status = ProcessDetectionStep;
				screen->DisplayText("The cans is closed");
				delay(500);
				screen->DisplayText("Please put the garbage on the sensor");
			}
		}
	}
	return true;
}


int main(void)
{
	//初始化管脚
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_RTC_Init();
    MX_I2C2_Init();
    MX_TIM1_Init();
    MX_I2C1_Init();
    MX_TIM2_Init();

    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);


	//标志变量区
	auto process = new Process();


	//初始化屏幕
	auto screen = new MainScreen();


	//初始化wifi
	screen->DisplayText("Loading wifi and connected to server");
	auto wifi = new RemoteDataContext("10.135.62.151", 520);
	HAL_Delay(5000);


	//发送清空指令
	wifi->AddClearEvent(0);


	//引用Timer对象并启动全局定时器
	auto timer = Timer::Shared;
	timer->Start();

	//初始化舵机
	auto green_servos = new Servos(3);	//绿色垃圾桶对应舵机, 标志pzdj2, food PA2	PA7
	auto gray_servos = new Servos(4);	//灰色垃圾桶对应舵机, 标志pzdj3, residual PA3	PA6
	auto blue_servos = new Servos(2);	//蓝色垃圾桶对应舵机, 标志pzdj1, recyclable PA1   PA5


	screen->DisplayText("Please put the garbage on the sensor");

	//为颜色传感器配置触发回调函数(当颜色传感器可用时)
	auto colorSensor = new ColorSensor();	//初始化颜色传感器
	timer->RegisterTask(200, [&colorSensor, &process, &screen, &wifi, &gray_servos, &green_servos, &blue_servos]()	//调用颜色传感器的感知模块
	{
		if(process->humanable && process->status == ProcessDetectionStep && !process->overflow)
		{
			colorSensor->Invoke();
		}
		else if(process->overflow)
		{
			gray_servos->Open();
			green_servos->Open();
			blue_servos->Open();
			screen->DisplayText("The cans is overflow");
			return false;
		}
		return true;
	});
	colorSensor->AddEventHandler([&wifi, &colorSensor, &gray_servos, &green_servos, &blue_servos, &screen, &process, &timer](Sepan_RGBC color)
	{
		auto classes = colorSensor->ParseColor(color.r, color.g, color.b);
		if(classes != 4 && classes != 0)
		{
			uint16_t task_id;
			if(classes == 1)
			{
				screen->DisplayText("This is food waste");
				delay(500);
				green_servos->Open();
				task_id = timer->RegisterTask(10000, [&green_servos, &screen, &process]()
				{
					if(green_servos->GetStatus() && process->status == ProcessClose)
					{
						green_servos->Close();
						process->status = ProcessDetectionStep;
						screen->DisplayOverTimeView();
					}
					return false;
				});
				wifi->AddThrowEvent(0);
			}

			else if(classes == 2)
			{
				screen->DisplayText("This is recyclable waste");
				delay(500);
				blue_servos->Open();
				task_id = timer->RegisterTask(10000, [&blue_servos, &screen, &process]()
				{
					if(blue_servos->GetStatus() && process->status == ProcessClose)
					{
						blue_servos->Close();
						process->status = ProcessDetectionStep;
						screen->DisplayOverTimeView();
					}
					return false;
				});
				wifi->AddThrowEvent(1);
			}

			else if(classes == 3)
			{
				screen->DisplayText("This is residual waste");
				delay(500);
				gray_servos->Open();
				task_id = timer->RegisterTask(10000, [&gray_servos, &screen, &process]()
				{
					if(gray_servos->GetStatus() && process->status == ProcessClose)
					{
						gray_servos->Close();
						process->status = ProcessDetectionStep;
						screen->DisplayOverTimeView();
					}
					return false;
				});
				wifi->AddThrowEvent(2);
			}
			process->servos_task_id = task_id;
			process->status = ProcessClose;
		}

	});
	auto blue_infraredSensor = new InfraredSensor(GPIOA, GPIO_PIN_5);
	blue_infraredSensor->AddEventHandler([&process, &blue_servos, &blue_infraredSensor, &timer, &screen, &wifi]()
	{
		return infrared_interrupt(process, blue_servos, blue_infraredSensor, timer, screen, wifi, 1);
	});
	auto green_infraredSensor = new InfraredSensor(GPIOA, GPIO_PIN_7);
	green_infraredSensor->AddEventHandler([&process, &green_servos, &green_infraredSensor, &timer, &screen, &wifi]()
	{
		return infrared_interrupt(process, green_servos, green_infraredSensor, timer, screen, wifi, 0);
	});
	auto gray_infraredSensor = new InfraredSensor(GPIOA, GPIO_PIN_6);
	gray_infraredSensor->AddEventHandler([&process, &gray_servos, &gray_infraredSensor, &timer, &screen, &wifi]()
	{
		return infrared_interrupt(process, gray_servos, gray_infraredSensor, timer, screen, wifi, 2);
	});
	while (1)
	{
		wifi->Invoke();
	}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
