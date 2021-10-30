/*
 * time:2021/4/4
 * File:PCA9685.h
 * 移植:梦幽
 */

#ifndef __PCA9685__H
#define __PCA9685__H



#define PCA9685_ADDRESS	0x40	//PCA9685 IIC总线地址

#define PCA9685_MODE1			0x00	

#define PCA9685_SUBADR1			0x02
#define PCA9685_SUBADR2			0x03
#define PCA9685_SUBADR3			0x04

#define PCA9685_LED0_ON_L		0x06	//低8位(共12位，[0, 4095])
#define PCA9685_LED0_ON_H		0x07	//PWM起始位寄存器高8位(只用了4位)
#define PCA9685_LED0_OFF_L		0x08	//低8位(共12位，[0, 4095])
#define PCA9685_LED0_OFF_H		0x09	//PWM停止位寄存器高8位(只用了4位)

#define PCA9685_ALLLED_ON_L		0xfa
#define PCA9685_ALLLED_ON_H		0xfb
#define PCA9685_ALLLED_OFF_L	0xfc
#define PCA9685_ALLLED_OFF_H	0xfd

#define PCA9685_PRESCALE		0xfe	//  PWM频率寄存器

void PCA9685_Reset(void);
void PCA9685_SetPWMFreq(float freq);
void PCA9685_SetPWM(char channel, unsigned int on, unsigned int off);
void PCA9685_SetServoPulse(char channel, float pulse);

#endif 
