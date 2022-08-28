/* ============================================
  Simple_BN0055 device library code is placed under the MIT license
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

#ifndef BN_WriteMacros_h
#define BN_WriteMacros_h
/*4.2 Register map
The register map is separated into two logical pages, Page 1 contains sensor specific
configuration data and Page 0 contains all other configuration parameters and output data.
At power-on Page 0 is selected, the PAGE_ID register can be used to identify the current
selected page and change between page 0 and page 1.
*/
// 4.2.1 Register map Page 0
#define W_All_Calibration(Data)               PG(0).WriteInts(0x55, 11, (int16_t *)Data)   //  All Calibration Values 3ACC 3MAG 3GYR AccRadius MagRadius 

#define W_MAG_RADIUS(Data)                    PG(0).WriteInt(0x69, (int16_t)Data)       //  Magnetometer Radius
#define W_ACC_RADIUS(Data)                    PG(0).WriteInt(0x67, (int16_t)Data)       //  Accelerometer Radius

#define W_GYR_OFFSET(Data)                    PG(0).WriteInts(0x61, 3, (int16_t)Data)   //   Gyroscope Offset.

#define W_GYR_OFFSET_X(Data)                  PG(0).WriteInt(0x61, (int16_t)Data)       //   Gyroscope Offset X.
#define W_GYR_OFFSET_Y(Data)                  PG(0).WriteInt(0x63, (int16_t)Data)       //   Gyroscope Offset Y.
#define W_GYR_OFFSET_Z(Data)                  PG(0).WriteInt(0x65, (int16_t)Data)       //   Gyroscope Offset Z.

#define W_MAG_OFFSET(Data)                    PG(0).WriteInts(0x5B, 3, (int16_t)Data)   //   Magnetometer Offset.

#define W_MAG_OFFSET_X(Data)                  PG(0).WriteInt(0x5B, (int16_t)Data)       //   Magnetometer Offset X.
#define W_MAG_OFFSET_Y(Data)                  PG(0).WriteInt(0x5D, (int16_t)Data)       //   Magnetometer Offset Y.
#define W_MAG_OFFSET_Z(Data)                  PG(0).WriteInt(0x5F, (int16_t)Data)       //   Magnetometer Offset Z.

#define W_ACC_OFFSET(Data)                    PG(0).WriteInts(0x55, 3, (int16_t)Data)   //   Accelerometer Offset.

#define W_ACC_OFFSET_X(Data)                  PG(0).WriteInt(0x55, (int16_t)Data)       //   Accelerometer Offset X.
#define W_ACC_OFFSET_Y(Data)                  PG(0).WriteInt(0x57, (int16_t)Data)       //   Accelerometer Offset Y.
#define W_ACC_OFFSET_Z(Data)                  PG(0).WriteInt(0x59, (int16_t)Data)       //   Accelerometer Offset Z.

//0x43 - 0x54 Reserved

//placement for axis vs. register settings:
//Placement -- AXIS_REMAP_CONFIG, AXIS_REMAP_SIGN
//3.4 Axis remap BNO055 Data sheet Page 25 
// SetArray Options:
#define POS0 uint8_t _POS[2] = {0x21, 0x04}
#define POS1 uint8_t _POS[2] = {0x24, 0x00} //(default)
#define POS2 uint8_t _POS[2] = {0x24, 0x06}
#define POS3 uint8_t _POS[2] = {0x21, 0x02}
#define POS4 uint8_t _POS[2] = {0x24, 0x03}
#define POS5 uint8_t _POS[2] = {0x21, 0x01}
#define POS6 uint8_t _POS[2] = {0x21, 0x07}
#define POS7 uint8_t _POS[2] = {0x24, 0x05}

#define W_AXIS_MAP(SetArray)         SetArray;PG(0).WriteByte(0x41, (uint8_t)_POS[0]).Delay(10).WriteByte(0x42, (uint8_t)_POS[1]).Delay(10) //   Remapped  axis Values & signs
#define W_AXIS_MAP_SIGN(SetArray)    SetArray;PG(0).WriteByte(0x42, (uint8_t)_POS[1]).Delay(10)      //   Remapped  axis signs
#define W_AXIS_MAP_SIGN_X(Data)               PG(0).WriteBit(0x42, 1, 2, (uint8_t)Data).Delay(10)  //   Remapped X axis sign
#define W_AXIS_MAP_SIGN_Y(Data)               PG(0).WriteBit(0x42, 1, 1, (uint8_t)Data).Delay(10)  //   Remapped Y axis sign
#define W_AXIS_MAP_SIGN_Z(Data)               PG(0).WriteBit(0x42, 1, 0, (uint8_t)Data).Delay(10)  //   Remapped Z axis sign

#define W_AXIS_MAP_CONFIG(SetArray)  SetArray;PG(0).WriteByte(0x41, (uint8_t)_POS[0]).Delay(10)      //   Remapped  axis values
#define W_AXIS_MAP_CONFIG_X(Data)             PG(0).WriteBit(0x41, 2, 1, (uint8_t)Data).Delay(10)  //   Remapped X axis value
#define W_AXIS_MAP_CONFIG_Y(Data)             PG(0).WriteBit(0x41, 2, 3, (uint8_t)Data).Delay(10)  //   Remapped Y axis value
#define W_AXIS_MAP_CONFIG_Z(Data)             PG(0).WriteBit(0x41, 2, 5, (uint8_t)Data).Delay(10)  //   Remapped Z axis value 

#define W_TEMP_SOURCE(Data)                   PG(0).WriteBit(0x40, 2, 1, (uint8_t)Data)  //   TEMP_Source <1:0>

#define W_SYS_TRIGGER_CLK_SEL(Data)           PG(0).WriteBitX(0x3F, 1, 7, (uint8_t)Data).Delay(100)  //   CLK_SEL   -- Delay for power issues https://tinyurl.com/y375z699
#define W_SYS_TRIGGER_CLK_SEL_internal()      PG(0).WriteBitX(0x3F, 1, 7, 0).Delay(100)              //   CLK_SEL Internal oscillator  -- Delay for power issues https://tinyurl.com/y375z699
#define W_SYS_TRIGGER_CLK_SEL_External()      PG(0).WriteBitX(0x3F, 1, 7, 1).Delay(100)              //   CLK_SEL External oscillator  -- Delay for power issues https://tinyurl.com/y375z699
#define W_SYS_TRIGGER_RST_INT()               PG(0).WriteBitX(0x3F, 1, 6, 1)                         //   Triggers RST_Interrupt   -- Delay for power issues https://tinyurl.com/y375z699
#define W_SYS_TRIGGER_RST_SYS()               PG(0).WriteBitX(0x3F, 1, 5, 1).Delay(650)              //   Triggers RST_SYS   -- Delay required for completion of self test
#define W_SYS_TRIGGER_Self_Test()             PG(0).WriteBitX(0x3F, 1, 0, 1).Delay(350)              //   Triggers Self_Test -- Delay required for completion of self test

#define W_PWR_MODE(Data)                      PG(0).WriteBit(0x3E, 2, 1, (uint8_t)Data).Delay(10)  //   Power Mode <1:0>
#define W_PWR_MODE_NORMAL()                   PG(0).WriteBit(0x3E, 2, 1, 0X00) //   POWER MODE NORMAL 
#define W_PWR_MODE_LOWPOWER()                 PG(0).WriteBit(0x3E, 2, 1, 0X01).Delay(10) //   Power Mode LOW POWER
#define W_PWR_MODE_SUSPEND()                  PG(0).WriteBit(0x3E, 2, 1, 0X02).Delay(10) //   Power Mode SUSPEND

//4.3.61 OPR_MODE 0x3D for W_OPR_MODE(Data);
//3.3 Operation Modes
//--- Non-Fusion Modes              **2 types: Non-absolute or relative orientation and Absolute orientation linked to magnetic north pole.
#define CONFIGMODE    0X00 //This mode is used for configuration wherein all output data is reset to zero and sensor fusion is halted.
#define ACCONLY       0X01 //Use if the application requires only raw accelerometer data.
#define MAGONLY       0X02 //Behaves like a stand-alone magnetometer.
#define GYRONLY       0X03 //Behaves like a stand-alone gyroscope.
#define ACCMAG        0X04 //Both accelerometer and magnetometer are switched on.
#define ACCGYRO       0X05 //Both accelerometer and gyroscope are switched on.
#define MAGGYRO       0X06 //Both magnetometer and gyroscope are switched on.
#define AMG           0X07 //All three sensors accelerometer, magnetometer and gyroscope are switched on.
//--- Fusion Modes                  **2 types: Non-absolute or relative orientation and Absolute orientation linked to magnetic north pole.
#define IMU           0X08 //Relative orientation in space is calculated from the accelerometer and gyroscope data.
#define COMPASS       0X09 //For heading calculation (direction of compass pointer) only the horizontal components x and y are used. The compass mode requires calibration.
#define M4G           0X0A //While similar to the IMU mode, the changing orientation of the magnetometer in the magnetic field is used. 
#define NDOF_FMC_OFF  0X0B //same as NDOF mode, but with the Fast Magnetometer Calibration turned ‘OFF’.
#define NDOF          0X0C //NOF (9-Degrees of Freedom) --- Absolute orientation data is calculated from accelerometer, gyroscope and the magnetometer.

#define W_OPR_MODE(Data)                      PG(0).WriteBit(0x3D, 4, 3, (uint8_t)Data)         //   Operation Mode <3:0>  Default 0x1C
//--- Non-Fusion Modes              **2 types: Non-absolute or relative orientation and Absolute orientation linked to magnetic north pole.
#define W_OPR_MODE_CONFIGMODE()               PG(0).WriteBit(0x3D, 4, 3, (uint8_t)CONFIGMODE)   //   Operation Mode 
#define W_OPR_MODE_ACCONLY()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)ACCONLY)      //   Operation Mode 
#define W_OPR_MODE_MAGONLY()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)MAGONLY)      //   Operation Mode 
#define W_OPR_MODE_GYRONLY()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)GYRONLY)      //   Operation Mode 
#define W_OPR_MODE_ACCMAG()                   PG(0).WriteBit(0x3D, 4, 3, (uint8_t)ACCMAG)       //   Operation Mode 
#define W_OPR_MODE_ACCGYRO()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)ACCGYRO)      //   Operation Mode 
#define W_OPR_MODE_MAGGYRO()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)MAGGYRO)      //   Operation Mode 
#define W_OPR_MODE_AMG()                      PG(0).WriteBit(0x3D, 4, 3, (uint8_t)AMG)          //   Operation Mode 
//--- Fusion Modes                  **2 types: Non-absolute or relative orientation and Absolute orientation linked to magnetic north pole.
#define W_OPR_MODE_IMU()                      PG(0).WriteBit(0x3D, 4, 3, (uint8_t)IMU)          //   Operation Mode 
#define W_OPR_MODE_COMPASS()                  PG(0).WriteBit(0x3D, 4, 3, (uint8_t)COMPASS)      //   Operation Mode 
#define W_OPR_MODE_M4G()                      PG(0).WriteBit(0x3D, 4, 3, (uint8_t)M4G)          //   Operation Mode 
#define W_OPR_MODE_NDOF_FMC_OFF()             PG(0).WriteBit(0x3D, 4, 3, (uint8_t)NDOF_FMC_OFF) //   Operation Mode 
#define W_OPR_MODE_NDOF()                     PG(0).WriteBit(0x3D, 4, 3, (uint8_t)NDOF)         //   Operation Mode 

//0x3C Reserved

#define W_UNIT_SEL(Data)                      PG(0).WriteByte(0x3B, 1, 7, (uint8_t)Data & B10010111)  //  Set all bits at once
#define W_UNIT_SEL_ORI_Android_Windows(Data)  PG(0).WriteBit(0x3B, 1, 7, (uint8_t)Data)  //   ORI_Android_Windows
#define W_UNIT_SEL_ORI_Windows()              PG(0).WriteBit(0x3B, 1, 7, 0)              //   ORI_Windows
#define W_UNIT_SEL_ORI_Android()              PG(0).WriteBit(0x3B, 1, 7, 1)              //   ORI_Android
// Bits 6,5 reserved
#define W_UNIT_SEL_TEMP_Unit(Data)            PG(0).WriteBit(0x3B, 1, 4, (uint8_t)Data)  //   TEMP_Unit 
#define W_UNIT_SEL_TEMP_Unit_C()              PG(0).WriteBit(0x3B, 1, 4, 0)              //   TEMP_Unit Celsius
#define W_UNIT_SEL_TEMP_Unit_F()              PG(0).WriteBit(0x3B, 1, 4, 1)              //   TEMP_Unit Fahrenheit 
// Bit 3 reserved
#define W_UNIT_SEL_EUL_Unit(Data)             PG(0).WriteBit(0x3B, 1, 2, (uint8_t)Data)  //   EUL_Unit 
#define W_UNIT_SEL_EUL_Unit_Deg()             PG(0).WriteBit(0x3B, 1, 2, 0)              //   EUL_Unit Degrees 
#define W_UNIT_SEL_EUL_Unit_Rad()             PG(0).WriteBit(0x3B, 1, 2, 1)              //   EUL_Unit Radians 
#define W_UNIT_SEL_GYR_Unit(Data)             PG(0).WriteBit(0x3B, 1, 1, (uint8_t)Data)  //   GYR_Unit 
#define W_UNIT_SEL_GYR_Unit_DPS()             PG(0).WriteBit(0x3B, 1, 1, 0)              //   GYR_Unit Degrees/Second
#define W_UNIT_SEL_GYR_Unit_RPS()             PG(0).WriteBit(0x3B, 1, 1, 1)              //   GYR_Unit Radians/Second
#define W_UNIT_SEL_ACC_Uni(Data)              PG(0).WriteBit(0x3B, 1, 0, (uint8_t)Data)  //   ACC_Uni
#define W_UNIT_SEL_ACC_Uni_MS2()              PG(0).WriteBit(0x3B, 1, 0, 0)              //   ACC_Uni m/s21 
#define W_UNIT_SEL_ACC_Uni_MG()               PG(0).WriteBit(0x3B, 1, 0, 1)              //   ACC_Uni mg





#define W_SYS_CLK_STATUS(Data)                PG(0).WriteBit(0x38, 1, 0, (uint8_t)Data)  //   ST_MAIN_CLK
#define W_Page_ID_1()                               PG(1)                                //   Go To Page ID 1


//4.2.2 Register map Page 1

//0x7F-0x60 Reserved
//0x5F - 0x50   BNO unique ID
//0x4F - 0x20 Reserved

#define W_GYR_AM_SET_Awake_Duration(Data)     PG(1).WriteBit(0x1F, 2, 3, (uint8_t)Data)  //   Awake Duration
#define W_GYR_AM_SET_Slope_Samples(Data)      PG(1).WriteBit(0x1F, 2, 1, (uint8_t)Data)  //   Slope Samples

#define W_GYR_AM_THRES(Data)                  PG(1).WriteBit(0x1E, 7, 6, (uint8_t)Data)  //   Gyro Any Motion Threshold <6:0>

#define W_GYR_DUR_Z(Data)                     PG(1).WriteByte(0x1D, (uint8_t)Data)       //   HR_Z_Duration

#define W_GYR_HR_Z_SET_THRES_HYST(Data)       PG(1).WriteBit(0x1C, 2, 6, (uint8_t)Data)  //   HR_Z_THRES_HYST
#define W_GYR_HR_Z_SET_Threshold(Data)        PG(1).WriteBit(0x1C, 5, 4, (uint8_t)Data)  //   HR_Z_Threshold

#define W_GYR_DUR_Y(Data)                     PG(1).WriteByte(0x1B, (uint8_t)Data)       //   HR_Y_Duration

#define W_GYR_HR_Y_SET_THRES_HYST(Data)       PG(1).WriteBit(0x1A, 2, 6, (uint8_t)Data)  //   HR_Y_THRES_HYST
#define W_GYR_HR_Y_SET_Threshold(Data)        PG(1).WriteBit(0x1A, 5, 4, (uint8_t)Data)  //   HR_Y_Threshold

#define W_GYR_DUR_X(Data)                     PG(1).WriteByte(0x19, (uint8_t)Data)       //   HR_X_Duration

#define W_GYR_HR_X_SET_THRES_HYST(Data)       PG(1).WriteBit(0x18, 2, 6, (uint8_t)Data)  //   HR_X_THRES_HYST
#define W_GYR_HR_X_SET_Threshold(Data)        PG(1).WriteBit(0x18, 5, 4, (uint8_t)Data)  //   HR_X_Threshold

#define W_GYR_INT_SETING_HR_FILT (Data)       PG(1).WriteBit(0x17, 1, 7, (uint8_t)Data)  //   HR_FILT
#define W_GYR_INT_SETING_AM_FILT (Data)       PG(1).WriteBit(0x17, 1, 6, (uint8_t)Data)  //   AM_FILT
#define W_GYR_INT_SETING_HR_Z_AXIS (Data)     PG(1).WriteBit(0x17, 1, 5, (uint8_t)Data)  //   HR_Z_AXIS
#define W_GYR_INT_SETING_HR_Y_AXIS (Data)     PG(1).WriteBit(0x17, 1, 4, (uint8_t)Data)  //   HR_Y_AXIS
#define W_GYR_INT_SETING_HR_X_AXIS (Data)     PG(1).WriteBit(0x17, 1, 3, (uint8_t)Data)  //   HR_X_AXIS
#define W_GYR_INT_SETING_AM_Z_AXIS (Data)     PG(1).WriteBit(0x17, 1, 2, (uint8_t)Data)  //   AM_Z_AXIS
#define W_GYR_INT_SETING_AM_Y_AXIS (Data)     PG(1).WriteBit(0x17, 1, 1, (uint8_t)Data)  //   AM_Y_AXIS
#define W_GYR_INT_SETING_AM_X_AXIS (Data)     PG(1).WriteBit(0x17, 1, 0, (uint8_t)Data)  //   AM_X_AXIS

#define W_ACC_NM_SET_NO_SLOW_Mo_Dur(Data)     PG(1).WriteBit(0x16, 6, 6, (uint8_t)Data)  //   ACC NO/SLOW Motion Duration
#define W_ACC_NM_SET_SMNM(Data)               PG(1).WriteBit(0x16, 1, 0, (uint8_t)Data)  //   ACC SMNM

#define W_ACC_NM_THRE(Data)                   PG(1).WriteByte(0x15, (uint8_t)Data)       //   Accelerometer NO/SLOW motion threshold

#define W_ACC_HG_THRES(Data)                  PG(1).WriteByte(0x14, (uint8_t)Data)       //   Accelerometer High G Threshold

#define W_ACC_HG_DURATION(Data)               PG(1).WriteByte(0x13, (uint8_t)Data)       //   Accelerometer High G Duration

#define W_ACC_INT_Set_HG_Z_AXIS(Data)         PG(1).WriteBit(0x12, 1, 7, (uint8_t)Data)  //   HG_Z_AXIS
#define W_ACC_INT_Set_HG_Y_AXIS(Data)         PG(1).WriteBit(0x12, 1, 6, (uint8_t)Data)  //   HG_Y_AXIS
#define W_ACC_INT_Set_HG_X_AXIS(Data)         PG(1).WriteBit(0x12, 1, 5, (uint8_t)Data)  //   HG_X_AXIS
#define W_ACC_INT_Set_AM_NM_Z_AXIS(Data)      PG(1).WriteBit(0x12, 1, 4, (uint8_t)Data)  //   AM/NM_Z_AXIS
#define W_ACC_INT_Set_AM_NM_Y_AXIS(Data)      PG(1).WriteBit(0x12, 1, 3, (uint8_t)Data)  //   AM/NM_Z_AXIS
#define W_ACC_INT_Set_AM_NM_X_AXIS(Data)      PG(1).WriteBit(0x12, 1, 2, (uint8_t)Data)  //   AM/NM_Z_AXIS
#define W_ACC_INT_Set_AM_DUR(Data)            PG(1).WriteBit(0x12, 2, 1, (uint8_t)Data)  //   AM_DUR 

#define W_ACC_AM_THRES(Data)                  PG(1).WriteByte(0x11, (uint8_t)Data)       //   Accelerometer Any motion threshold

#define W_INT_EN_ACC_NM(Data)                 PG(1).WriteBit(0x10, 1, 7, (uint8_t)Data)  //   ACC_NM
#define W_INT_EN_ACC_AM(Data)                 PG(1).WriteBit(0x10, 1, 6, (uint8_t)Data)  //   ACC_AM
#define W_INT_EN_ACC_HIGH_g(Data)             PG(1).WriteBit(0x10, 1, 5, (uint8_t)Data)  //   ACC_HIGH_G
#define W_INT_EN_GYR_HIGH_RATE(Data)          PG(1).WriteBit(0x10, 1, 3, (uint8_t)Data)  //   GYR_HIGH_RATE
#define W_INT_EN_GYR_AM(Data)                 PG(1).WriteBit(0x10, 1, 2, (uint8_t)Data)  //   GYR_AM

#define W_INT_MSK_ACC_NM(Data)                PG(1).WriteBit(0x0F, 1, 7, (uint8_t)Data)  //   ACC_NM
#define W_INT_MSK_ACC_AM(Data)                PG(1).WriteBit(0x0F, 1, 6, (uint8_t)Data)  //   ACC_AM
#define W_INT_MSK_ACC_HIGH_g(Data)            PG(1).WriteBit(0x0F, 1, 5, (uint8_t)Data)  //   ACC_HIGH_G
#define W_INT_MSK_GYR_HIGH_RATE(Data)         PG(1).WriteBit(0x0F, 1, 3, (uint8_t)Data)  //   GYR_HIGH_RATE
#define W_INT_MSK_GYR_AM(Data)                PG(1).WriteBit(0x0F, 1, 2, (uint8_t)Data)  //   GYR_AM

//0x0E Reserved 
#define W_GYR_Sleep_Config_AUTO_SLP_DUR(Data) PG(1).WriteBit(0x0D, 3, 5, (uint8_t)Data)  //   AUTO_SLP_DURATION
#define W_GYR_Sleep_Config_SLP_DURATION(Data) PG(1).WriteBit(0x0D, 3, 2, (uint8_t)Data)  //   SLP_DURATION

#define W_ACC_Sleep_Config_SLP_DURATION(Data) PG(1).WriteBit(0x0C, 4, 4, (uint8_t)Data)  //   SLP_DURATION
#define W_ACC_Sleep_Config_SLP_MODE(Data)     PG(1).WriteBit(0x0C, 1, 0, (uint8_t)Data)  //   SLP_MODE

#define W_GYR_Config_1_Power_Mode(Data)       PG(1).WriteBit(0x0B, 3, 2, (uint8_t)Data)  //   GYR_Power_Mode

#define W_GYR_Config_0_Bandwidth(Data)        PG(1).WriteBit(0x0A, 3, 5, (uint8_t)Data)  //   GYR_Bandwidth
#define W_GYR_Config_0_Range(Data)            PG(1).WriteBit(0x0A, 3, 2, (uint8_t)Data)  //   GYR_Range

#define W_MAG_Config_Power_mode(Data)         PG(1).WriteBit(0x09, 2, 6, (uint8_t)Data)  //   MAG_Power_mode
#define W_MAG_Config_OPR_Mode(Data)           PG(1).WriteBit(0x09, 2, 4, (uint8_t)Data)  //   MAG_OPR_Mode 
#define W_MAG_Config_Data_output_rate(Data)   PG(1).WriteBit(0x09, 3, 2, (uint8_t)Data)  //   MAG_Data_output_rate

#define W_ACC_Config_PWR_Mode(Data)           PG(1).WriteBit(0x09, 3, 7, (uint8_t)Data)  //   ACC_PWR_Mode
#define W_ACC_Config_BW(Data)                 PG(1).WriteBit(0x09, 3, 7, (uint8_t)Data)  //   ACC_BW
#define W_ACC_Config_Range(Data)              PG(1).WriteBit(0x09, 3, 7, (uint8_t)Data)  //   ACC_Range

#define W_Page_ID(Data)                             WriteByte(0x07, (uint8_t)Data)       //   Go To Page ID
#define W_Page_ID_0()                               PG(0)                                  //   Go To Page ID 0

//0x06 - 0x00 Reserved

#endif