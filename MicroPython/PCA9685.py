# time:2021/4/4
# File:PCA9685.py
# 移植:梦幽

from pyb import I2C
import math, time

class PCA9685:
    __SUBADR1            = 0x02
    __SUBADR2            = 0x03
    __SUBADR3            = 0x04
    __MODE1              = 0x00
    __PRESCALE           = 0xFE
    __LED0_ON_L          = 0x06
    __LED0_ON_H          = 0x07
    __LED0_OFF_L         = 0x08
    __LED0_OFF_H         = 0x09
    __ALLLED_ON_L        = 0xFA
    __ALLLED_ON_H        = 0xFB
    __ALLLED_OFF_L       = 0xFC
    __ALLLED_OFF_H       = 0xFD
    def __init__(self):

        self.i2c = I2C(3, I2C.MASTER)
        self.i2c.init()
        print(self.i2c.scan())
        self.Write(self.__MODE1, 0x00)  # PCA9685复位

    def Write(self, reg, val):
        self.i2c.mem_write(val, 0x40, reg)

    def Read(self, reg):
        data = bytearray(1)
        data = self.i2c.mem_read(1, 0x40, reg)
        data = int.from_bytes(data,'big')
        return data
    def SetPWMFreq(self, freq):
        prescaleval = 25000000.0
        prescaleval /= 4096.0
        prescaleval /= float(freq)
        prescaleval -= 1.0
        prescale = math.floor(prescaleval+0.5)
        oldmode = self.Read(self.__MODE1)
        newmode = (oldmode & 0x7f) | 0x10
        self.Write(self.__MODE1, newmode)
        self.Write(self.__PRESCALE, int(math.floor(prescale)))
        time.sleep(0.005)
        self.Write(self.__MODE1, oldmode | 0x80)

    def SetPWM(self, channel, on, off):
        self.Write(self.__LED0_ON_L+4*channel, on & 0xff)
        self.Write(self.__LED0_ON_H+4*channel, on >> 8)
        self.Write(self.__LED0_OFF_L+4*channel, off & 0xFF)
        self.Write(self.__LED0_OFF_H+4*channel, off >> 8)

    def SetServoPulse(self, channel, pulse):
        pulse = pulse*4096/20000
        self.SetPWM(channel, 0, int(pulse))