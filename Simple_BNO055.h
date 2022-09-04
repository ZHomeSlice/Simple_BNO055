/* ============================================
  Simple_BNO055 device library code is placed under the MIT license
  Copyright (c) 2021 Homer Creutz

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  ===============================================
*/
#ifndef Simple_BNO055_h
#define Simple_BNO055_h

#include "Arduino.h"
#include "Simple_Wire.h"
#include "BNO_WriteMacros.h"
#include "BNO_ReadMacros.h"
#ifdef __AVR__
#include <avr/pgmspace.h>
#ifndef interruptPin
#define interruptPin 2
#endif
#define Interupt_Attach_Function  if(interruptPin > 0)	attachInterrupt(digitalPinToInterrupt(interruptPin), [] {mpuInterrupt = true;}, RISING); //NOTE: "[]{mpuInterrupt = true;}" Is a complete function without a name. It is handed to the callback of attachInterrupts Google: "Lambda anonymous functions"
#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); {char S[(Spaces + Precision + 3)];Serial.print(F(" ")); Serial.print(dtostrf((float)Variable,Spaces,Precision ,S));}Serial.print(EndTxt);//Name,Variable,Spaces,Precision,EndTxt
#elif defined(ESP32)
    #include <pgmspace.h>
    #include <stdlib_noniso.h>
    #ifndef interruptPin
    #define interruptPin 15
    #endif
    #define  Interupt_Attach_Function  if(interruptPin > 0) attachInterrupt(digitalPinToInterrupt(interruptPin),  [] {mpuInterrupt = true;}, RISING); //NOTE: "[]{mpuInterrupt = true;}" Is a complete function without a name. It is handed to the callback of attachInterrupts Google: "Lambda anonymous functions"
#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); Serial.print(F(" ")); Serial.print(Variable,Precision);Serial.print(EndTxt);//Name,Variable,Spaces,Precision,EndTxt
#else
#define Interupt_Attach_Function
#define printfloatx(Name,Variable,Spaces,Precision,EndTxt) print(Name); Serial.print(F(" ")); Serial.print(Variable,Precision);Serial.print(EndTxt);//Name,Variable,Spaces,Precision,EndTxt
#endif

#define DPRINTBINL(Num) for (uint16_t i=0;i<(sizeof((uint16_t)Num)*8);i++) Serial.write(((Num >> i) & 1) == 1 ? '1' : '0'); // Prints a binary number with following Placeholder Zeros  (Automatic Handling)
#define DPRINTBINLX(S,Num,nl) Serial.print(F(S)); for (uint16_t i=0;i<(sizeof((uint16_t)Num)*8);i++) Serial.write(((Num >> i) & 1) == 1 ? '1' : '0'); if(nl)Serial.println(); // Prints a binary number with following Placeholder Zeros  (Automatic Handling)
#define DPRINTBIN(Num) for (uint32_t t = (1UL<< ((sizeof(Num)*8)-1)); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)
#define DPRINTHEX(Num) Serial.print(Num>>4,HEX);Serial.print(Num&0X0F,HEX);
#define ShowByte(Addr) {uint8_t val; I2Cdev::readBytes(0x68, Addr, 1, &val);  Serial.print("0x"); DPRINTHEX(Addr); Serial.print(" = 0x"); DPRINTHEX(val); Serial.print(" = 0B"); DPRINTBIN(val); Serial.println();}
#define ShowValue(Name, FunctionD) FunctionD; Serial.print(Name); Serial.print(" = 0x"); DPRINTHEX(D); Serial.print(" = 0B"); DPRINTBIN(D); Serial.println();

/*    4.3.61 OPR_MODE 0x3D for W_OPR_MODE(Data);
    3.3 Operation Modes
    --- Non-Fusion Modes
     CONFIGMODE    0X00 //This mode is used for configuration wherein all output data is reset to zero and sensor fusion is halted.
     ACCONLY       0X01 //Use if the application requires only raw accelerometer data.
     MAGONLY       0X02 //Behaves like a stand-alone magnetometer.
     GYRONLY       0X03 //Behaves like a stand-alone gyroscope.
     ACCMAG        0X04 //Both accelerometer and magnetometer are switched on.
     ACCGYRO       0X05 //Both accelerometer and gyroscope are switched on.
     MAGGYRO       0X06 //Both magnetometer and gyroscope are switched on.
     AMG           0X07 //All three sensors accelerometer, magnetometer and gyroscope are switched on.
    --- Fusion Modes                  **2 types: Non-absolute or relative orientation and Absolute orientation linked to magnetic north pole.
     IMU           0X08 //Relative orientation in space is calculated from the accelerometer and gyroscope data.
     COMPASS       0X09 //For heading calculation (direction of compass pointer) only the horizontal components x and y are used. The compass mode requires calibration.
     M4G           0X0A //While similar to the IMU mode, the changing orientation of the magnetometer in the magnetic field is used.
     NDOF_FMC_OFF  0X0B //same as NDOF mode, but with the Fast Magnetometer Calibration turned ‘OFF’.
     NDOF          0X0C //NOF (9-Degrees of Freedom) --- Absolute orientation data is calculated from accelerometer, gyroscope and the magnetometer.
  */


// Get_Values() Type options:
#define Get_TEMPERATURE   0
#define Get_MAGNETOMETER  1
#define Get_GYROSCOPE     2
#define Get_EULER         3
#define Get_ACCELEROMETER 4
#define Get_LINEARACCEL   5
#define Get_GRAVITY       6
#define Get_QUATERNION    7

/** BNO055 Address A **/
#define BNO055_ADDRESS_A (0x28)
/** BNO055 Address B **/
#define BNO055_ADDRESS_B (0x29)
/** BNO055 ID **/
#define BNO055_ID (0xA0)

class Simple_BNO055 : public Simple_Wire {
  public:
	uint8_t SensorID;

    uint8_t data[16];
    int16_t  gyro[3], accel[3];
	float mag[3];
    int32_t quat[4];
	int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output

    //Startup Functions MPU
    Simple_BNO055(); // Constructor
    Simple_BNO055(uint8_t address);// Constructor
    Simple_BNO055 & Begin();
    Simple_BNO055 & Initialize();
    Simple_BNO055 & Set_Mode(uint8_t Operating_Mode);
    Simple_BNO055 & Get_Values(double *Value, uint8_t Type);
    uint8_t TestConnection(bool Verbose = false);
    uint8_t Check_SelfTest(bool Verbose = 1,bool StopHere = 1);
    uint8_t Check_Calibration(bool Verbose = 1, uint8_t Test = 1);
    Simple_BNO055 & CalibrationView();
    Simple_BNO055 & CalibrationSave(int16_t *StoredVals);
    Simple_BNO055 & CalibrationRestore(int16_t *StoredVals);
    Simple_BNO055 & PG(uint8_t Page);
};
#endif