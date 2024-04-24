#include "oled.h"
#include "oledfont.h"

static void OLED_Write_Cmd(uint8_t cmd)
{
	uint8_t buf[2];
	buf[0] = 0x00;	//control byte
	buf[1] = cmd;
	HAL_I2C_Master_Transmit(&hi2c2, 0x78, buf, 2, 0xFFFF);
}
/**
 * @brief	OLEDд������
 * @param cmd - ��д������
 * @note	��ֲʱ����ʹ���Լ��ĵײ�APIʵ�� 
*/
static void OLED_Write_Dat(uint8_t dat)
{
	uint8_t buf[2];
	buf[0] = 0x40; //control byte
	buf[1] = dat;
	
	//ʹ��HAL���APIʵ��
	HAL_I2C_Master_Transmit(&hi2c2, 0x78, buf, 2, 0xFFFF);
}

/**
 * @brief	OLED������ʾλ��
 * @param x - X����λ��
 * @param y - Y����λ��
*/
void OLED_Set_Pos(uint8_t x, uint8_t y)
{ 	
	OLED_Write_Cmd(0xb0+y);
	OLED_Write_Cmd(((x&0xf0)>>4)|0x10);
	OLED_Write_Cmd((x&0x0f)|0x01);
}   	  
/**
 * @brief	OLED������ʾ
*/ 
void OLED_Display_On(void)
{
	OLED_Write_Cmd(0X8D);  //SET DCDC����
	OLED_Write_Cmd(0X14);  //DCDC ON
	OLED_Write_Cmd(0XAF);  //DISPLAY ON
}
/**
 * @brief	OLED�ر���ʾ
*/   
void OLED_Display_Off(void)
{
	OLED_Write_Cmd(0X8D);  //SET DCDC����
	OLED_Write_Cmd(0X10);  //DCDC OFF
	OLED_Write_Cmd(0XAE);  //DISPLAY OFF
}		   			 
/**
 * @brief	OLED��������������֮����ĻȫΪ��ɫ��
*/ 
void OLED_Clear(void)
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_Write_Cmd(0xb0+i);    //����ҳ��ַ��0~7��
		OLED_Write_Cmd(0x00);      //������ʾλ�á��е͵�ַ
		OLED_Write_Cmd(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
			OLED_Write_Dat(0);
		}			
	}
}

void OLED_On(void)
{  
	uint8_t i,n;
	for(i=0;i<8;i++)
	{  
		OLED_Write_Cmd(0xb0+i);    //����ҳ��ַ��0~7��
		OLED_Write_Cmd(0x00);      //������ʾλ�á��е͵�ַ
		OLED_Write_Cmd(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
			OLED_Write_Dat(1);
		}			
	}
}

void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size)
{   
	uint8_t c=0,i=0;
	
	c = chr-' ';	
	if(x > 128-1)
	{
		x=0;
		y++;
	}
	
	if(size ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		{
			OLED_Write_Dat(F8X16[c*16+i]);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_Write_Dat(F8X16[c*16+i+8]);
		}
	}
	else
	{	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_Write_Dat(F6x8[c][i]);
		}
	}
}

static uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}	

void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size); 
	}
} 

void OLED_ShowString(uint8_t x,uint8_t y,char *chr,uint8_t size)
{
	uint8_t j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],size);
			x+=8;
			if(x>120){x=0;y+=2;}
			j++;
	}
}


/**
 * @brief	OLED��ʼ��
*/			    
void OLED_Init(void)
{ 	

	HAL_Delay(500);

	OLED_Write_Cmd(0xAE);//--display off
	OLED_Write_Cmd(0x00);//---set low column address
	OLED_Write_Cmd(0x10);//---set high column address
	OLED_Write_Cmd(0x40);//--set start line address  
	OLED_Write_Cmd(0x81); // contract control
	OLED_Write_Cmd(0xFF);//--128   
	OLED_Write_Cmd(0xA1);//set segment remap 
	OLED_Write_Cmd(0xC8);//Com scan direction
	OLED_Write_Cmd(0xA6);//--normal / reverse
	OLED_Write_Cmd(0xA8);//--set multiplex ratio(1 to 64)
	OLED_Write_Cmd(0x3F);//--1/32 duty
	OLED_Write_Cmd(0xD3);//-set display offset
	OLED_Write_Cmd(0x00);//
	OLED_Write_Cmd(0xD5);//set osc division
	OLED_Write_Cmd(0x80);
	OLED_Write_Cmd(0xD9);//Set Pre-Charge Period
	OLED_Write_Cmd(0xF1);//
	OLED_Write_Cmd(0xDA);//set com pin configuartion
	OLED_Write_Cmd(0x12);//
	OLED_Write_Cmd(0xDB);//set Vcomh
	OLED_Write_Cmd(0x40);//
	OLED_Write_Cmd(0x20);
	OLED_Write_Cmd(0x02);
	OLED_Write_Cmd(0x8D);//set charge pump enable
	OLED_Write_Cmd(0x14);//
	OLED_Write_Cmd(0xA4);
	OLED_Write_Cmd(0xA6);
	OLED_Write_Cmd(0xAF);//--turn on oled panel
	
	OLED_Clear();
	OLED_Set_Pos(0,0);
}
