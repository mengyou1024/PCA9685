/*
 * time:2021/4/4
 * File:PCA9685.c
 * 移植:梦幽
 */
 
#include "PCA9685.h"
/************************************************************************************************/

//代码移植区
#include "STM32_I2C.H"
#include "stm32f10x_Reg.h"
#include "stm32f10x_type.h"
#include "stm32f10x_Init.h"
#include "delay.h"
#include "math.h"

/*
 *	func:	向PCA9685寄存器里面写数据
 *	addr:	8位寄存器地址
 *	data:	8位数据
 *	return:	NULL
 */
void PCA9685_WriteReg(uchar addr, uchar data)
{
	I2C_SendByte(PCA9685_ADDRESS, addr, data);
	return ;
}
/*
 *	func:	读取PCA9685寄存器里面的数据并范湖
 *	addr:	8位寄存器地址
 *	return:	读取到的8位数据
 */
uchar PCA9685_ReadReg(uchar addr)
{
	uchar data;
	I2C_ReceByte(1, PCA9685_ADDRESS, addr, &data);//无应答位
	return data;
}
/************************************************************************************************/

/*
 * func:	芯片复位
 * return: 	NULL
 */
void PCA9685_Reset(void)
{
	PCA9685_WriteReg(PCA9685_MODE1, 0x00);
	return ;
}

/*
 * func:	设置输出PWM的频率
 * freq:	PWM的频率(Hz)
 * return: 	NULL
 */
void PCA9685_SetPWMFreq(float freq)
{
	float prescaleval=25000000.0;
	int prescale;
	char oldmode, newmode;
	prescaleval /= 4096.0;	      	
	prescaleval /= freq;
	prescaleval -= 1.0;
	prescale = floor(prescaleval+0.5);
	
	oldmode = PCA9685_ReadReg(PCA9685_MODE1);
	
	newmode = (oldmode & 0x7f) | 0x10;
	
	PCA9685_WriteReg(PCA9685_MODE1, newmode);
	PCA9685_WriteReg(PCA9685_PRESCALE, (int)floor(prescale));
	
	delay(5);
	
	PCA9685_WriteReg(PCA9685_MODE1, oldmode | 0x80);
	return ;
}

/*
 * func:	设置输出PWM
 * channel:	PWM通道号
 * on:		起始位置
 * off:		停止位置
 * return: 	NULL
 */
void PCA9685_SetPWM(char channel, unsigned int on, unsigned int off)
{
	PCA9685_WriteReg(PCA9685_LED0_ON_L+4*channel, on & 0xff);
	PCA9685_WriteReg(PCA9685_LED0_ON_H+4*channel, on >> 8);
	PCA9685_WriteReg(PCA9685_LED0_OFF_L+4*channel, off & 0xff);
	PCA9685_WriteReg(PCA9685_LED0_OFF_H+4*channel, off >> 8);
	return ;
}

/*
 * func:	设置舵机的脉冲
 * channel:	舵机号
 * pulse:	脉冲宽度(us)
 * return: 	NULL
 */
void PCA9685_SetServoPulse(char channel, float pulse)
{
	float temp;
	temp = pulse*4096/20000;
	PCA9685_SetPWM(channel, 0, (int)temp);
	return ;
}
