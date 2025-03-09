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
#include "Arduino.h"
#include <Wire.h>
#include "Simple_Wire.h"
#include "Simple_BNO055.h"
#include "BNO_ReadMacros.h"
#include "BNO_WriteMacros.h"

// Blink Without Delay Serial Port Spam Timer Macro
#define spamtimer(t) for (static uint32_t SpamTimer; (uint32_t)(millis() - SpamTimer) >= (t); SpamTimer = millis()) // A Way to do a Blink without Delay timer

/**
@brief      Initialization functions
*/
Simple_BNO055::Simple_BNO055(){
    SetIntMSBPos(false);
}
Simple_BNO055::Simple_BNO055(uint8_t address) {
    SetAddress(address);
}
Simple_BNO055 & Simple_BNO055::begin(int sdaPin, int sclPin){
    delay(650); // hold on for boot
    if(!GetAddress()) SetAddress(Check_Address(BNO055_ADDRESS_A)?BNO055_ADDRESS_A:BNO055_ADDRESS_B);
    return *this;
}
Simple_BNO055 & Simple_BNO055::Initialize(){
    W_OPR_MODE(CONFIGMODE); 
    W_SYS_TRIGGER_RST_SYS();  // reset
    W_PWR_MODE_NORMAL(); 
    Check_SelfTest();
    W_UNIT_SEL_ORI_Android();
    W_UNIT_SEL_TEMP_Unit_C();
    W_UNIT_SEL_EUL_Unit_Deg();
    W_UNIT_SEL_GYR_Unit_RPS();
    W_UNIT_SEL_ACC_Uni_MS2();
    uint8_t Data;
    R_UNIT_SEL(&Data) ;
    Serial.print(Data,BIN);
    W_AXIS_MAP(POS1); // POS0~POS7 3.4 Axis remap BNO055 Data sheet Page 25 
 //   Check_SelfTest();
    return *this;
}
Simple_BNO055 & Simple_BNO055::Set_Mode(uint8_t Operating_Mode){
    W_OPR_MODE(Operating_Mode);
       return *this;
}

/* Get_Values() Type options:
 * Get_TEMPERATURE   0
 * Get_MAGNETOMETER  1
 * Get_GYROSCOPE     2
 * Get_EULER         3
 * Get_ACCELEROMETER 4
 * Get_LINEARACCEL   5
 * Get_GRAVITY       6
 * Get_QUATERNION    7
 */


Simple_BNO055 & Simple_BNO055::Get_Values(double *Value, uint8_t Type){
    int16_t Data[4];
    uint8_t x = 0;
    double M = 1.0;
    switch (Type) {
    case Get_TEMPERATURE:
        // 1°C = 1 LSB
        // 2 F = 1 LSB
        R_UNIT_SEL_TEMP_Unit(&x);
        M = (x) ? 2.0 : 1.0; // ? °F : °C
        R_TEMP_Data(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        break;        
    case Get_MAGNETOMETER:
        // 1 uT = 16 LSB 
        M = 1.0 / 16;
        R_MAG_DATA(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_GYROSCOPE:
        // 1 Dps = 16 LSB
        // 1 Rps = 900 LSB
        R_UNIT_SEL_GYR_Unit(&x);
        M = (x) ? 900.0 : 16.0; // ? 1 Rps : 1 Dps
        M = 1.0 / M;
        R_GYR_DATA(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_EULER:
        // 1 Degree = 16 LSB
        // 1 Radian = 900 LSB
        R_UNIT_SEL_EUL_Unit(&x);
        M = (x) ? 900.0 : 16.0; // ? 1 Radian : 1 Degree
        M = 1.0 / M;
        R_EUL_Data(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_ACCELEROMETER:
        //1 m/s2 = 100 LSB
        //1 mg = 1 LSB
        R_UNIT_SEL_ACC_Uni(&x);
        M = (x) ? 1.0 : 100.0; // ? 1 mg : 1 m/s2
        M = 1.0 / M;
        R_ACC_DATA(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_LINEARACCEL:
        //1 m/s2 = 100 LSB
        //1 mg = 1 LSB
        R_UNIT_SEL_ACC_Uni(&x);
        M = (x) ? 1.0 : 100.0; // ? 1 mg : 1 m/s2
        M = 1.0 / M;
        R_LIA_Data(Data); 
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_GRAVITY:
        //1 m/s2 = 100 LSB
        //1 mg = 1 LSB
        R_UNIT_SEL_ACC_Uni(&x);
        M = (x) ? 1.0 : 100.0; // ? 1 mg : 1 m/s2
        M = 1.0 / M;
        R_GRV_Data(Data);
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        break;
    case Get_QUATERNION:
        // 1 Quaternion (unit less) = 2^14 LSB
        R_QUA_Data(Data);
        M = 1.0 / 16384.0;
        Value[0] = ((double)((int16_t)Data[0])) * M;
        Value[1] = ((double)((int16_t)Data[1])) * M;
        Value[2] = ((double)((int16_t)Data[2])) * M;
        Value[2] = ((double)((int16_t)Data[3])) * M;
        break;
    }
    
    return *this;
}
/**
@brief      Test to be sure we have communication to the MPU
returns 1 on success
stops or returns 0 on fail
*/
uint8_t Simple_BNO055::TestConnection(bool Verbose) {
	if(Check_Address(GetAddress())){
        R_CHIP_ID(&SensorID);
        if(Verbose){
            Serial.print("Found BNO055 at: 0x");
            Serial.println(GetAddress(), HEX);
            Serial.print("BNO055 Chip ID: 0x");
            Serial.println(SensorID, HEX);
        }
        return (SensorID == CHIP_ID)?1:0;
	} else if(Verbose) I2C_Scanner();
	return 0;
}

uint8_t Simple_BNO055::Check_SelfTest(bool Verbose,bool StopHere){
    static bool ReSelfTest = 0;
    if (ReSelfTest){
        if(Verbose) Serial.println("Re-Self Testing");
        W_SYS_TRIGGER_Self_Test();
    } 
    ReSelfTest = 1;
    uint8_t SelfTest = 0;
    for(uint8_t Count = 0; Count < 100;Count++){ //Self Test May require additional time to complete
        R_ST_RESULT(&SelfTest);   // Self Test MCU GYR MAG ACC
        if(SelfTest == B1111)break;
        delay(10);
    }
    if(SelfTest != B1111) { 
        Serial.println("Chip issues: ");
        if(!(SelfTest & 0b1000))Serial.println("Microcontroller self test Failed");
        if(!(SelfTest & 0b0100))Serial.println("Gyroscope self test Failed");
        if(!(SelfTest & 0b0010))Serial.println("Magnetometer self test Failed");
        if(!(SelfTest & 0b0001))Serial.println("Accelerometer self test Failed");
        if(StopHere)while(1){};
        return 0;
    }
    else if(Verbose) Serial.println("Self Test Passed");
    return 1;
}
uint8_t Simple_BNO055::Check_Calibration(bool Verbose, uint8_t Test ){ // 0 = Check All, 1 Check System, 2 check Gyro, 3 check accel, 4 check Mag
    uint8_t Data = 0;
    R_CALIB_STAT(&Data);
    if(Verbose){
    switch (Test)
    {
    case 1:
        Serial.print("SYS Calibration Status: ");
        Serial.println((Data & 0b11000000) >> 6);
        break;
    case 2:
        Serial.print("Gyro Calibration Status: ");
        Serial.println((Data & 0b00110000) >> 4);
        break;
    case 3:
        Serial.print("Accelerometer Calibration Status: ");
        Serial.println((Data & 0b00001100) >> 2);
        break;
    case 4:
        Serial.print("Magnetometer Calibration Status: ");
        Serial.println((Data & 0b00000011) );
        break;
    default:
        uint16_t DataMix = 0;
        Serial.print("Calibration Status SYS,GYR,ACC,MAG:");
        DataMix =  ( (uint8_t)(Data & 0b00000011)      );
        DataMix += (((uint8_t)(Data & 0b00001100) >> 2)) * 10;      
        DataMix += (((uint8_t)(Data & 0b00110000) >> 4)) * 100;      
        DataMix += (((uint8_t)(Data & 0b11000000) >> 6)) * 1000;

        Serial.println(DataMix);
        break;
    }
    }
    return (Data);

}

Simple_BNO055 & Simple_BNO055::CalibrationView(){
    int16_t StoredVals[11];
    uint8_t CurrMode = CONFIGMODE;

    uint8_t CalStates = 0;
    R_OPR_MODE(&CurrMode);
    W_OPR_MODE_CONFIGMODE();
    R_All_Calibration(StoredVals);
    R_CALIB_STAT(&CalStates);
    Serial.print("#define Offsets "); 
    for(int i = 0; i < 3; i++) {

        if(i>0)Serial.print(", ");
        Serial.print(StoredVals[(3*i)]);
        Serial.print(", ");
        Serial.print(StoredVals[(3*i)+1]);
        Serial.print(", ");
        Serial.print(StoredVals[(3*i)+2]);
    }

    Serial.print(", ");
    Serial.print(StoredVals[9]);
    Serial.print(", ");
    Serial.print(StoredVals[10]);
    Serial.println();
    W_OPR_MODE(CurrMode);
    return *this;
}

Simple_BNO055 & Simple_BNO055::CalibrationSave(int16_t *StoredVals){
    uint8_t CurrMode = CONFIGMODE;
    R_OPR_MODE(&CurrMode);
    W_OPR_MODE_CONFIGMODE();
    W_All_Calibration(StoredVals);
    W_OPR_MODE(CurrMode);
    return *this;
}


Simple_BNO055 & Simple_BNO055::CalibrationRestore(int16_t *StoredVals){
    uint8_t CurrMode = CONFIGMODE;
    int16_t CalVals[11];
    uint8_t CalStates = 0;
    R_OPR_MODE(&CurrMode);
    W_OPR_MODE_CONFIGMODE();
    R_All_Calibration(CalVals);
    R_CALIB_STAT(&CalStates);

    uint8_t positions[3] {B001100, B000011, B110000}; // Acc, Gyro, Mag
    for(int i = 0; i < 3; i++) {

        if((CalStates & positions[i]) == positions[i]){
            StoredVals[(3*i)] = CalVals[(3*i)];
            StoredVals[(3*i)+1] = CalVals[(3*i)+1];
            StoredVals[(3*i)+2] = CalVals[(3*i)+2];
        } 
    }
    if((CalStates & 0b11000000) == B11000000){
        StoredVals[9] = CalVals[9];
        StoredVals[10] = CalVals[10];
    }
    W_OPR_MODE(CurrMode);
    return *this;
}

Simple_BNO055 & Simple_BNO055::PG(uint8_t Page){
    static uint8_t PageID = 10;
    if(PageID != Page)    W_Page_ID(Page);
    PageID = Page;
    return *this;
}