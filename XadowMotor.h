/*
  XadowMotor.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-7-14
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __XADOWMOTOR_H__
#define __XADOWMOTOR_H__

#define __DebugXM   0
#define MSTOP       0                           // stop
#define MFOR        1                           // go forward
#define MREV        2                           // go reverse..
#define MHOLD       3

#define MOTORA      1                           // MOTOR A
#define MOTORB      2                           // MOTOR B

#define MOTORADDRESS0       0x40                // A0 LOW, A1 LOW
#define MOTORADDRESS1       0x41                // A0 HIGH, A1 LOW
#define MOTORADDRESS2       0x42                // A0 LOW, A1 HIGH
#define MOTORADDRESS3       0x43                // A0 HIGH, A1 HIGH

class XadowMotor{

private:

    int i2cAddress;
public:
    void sendI2C(unsigned char dta);
    
    unsigned char calcOdd(unsigned char dta);
public:

    void begin(int address);
    float getBatVol();
    void setMotorRun(unsigned char sMotorA, unsigned char sMotorB);
    
    void setPwrDown();
    void setWakeUp();
    
};

extern XadowMotor xadowMotor;

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/