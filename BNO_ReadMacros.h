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

#ifndef BN_ReadMacros_h
#define BN_ReadMacros_h
/*4.2 Register map
The register map is separated into two logical pages, Page 1 contains sensor specific
configuration data and Page 0 contains all other configuration parameters and output data.
At power-on Page 0 is selected, the PAGE_ID register can be used to identify the current
selected page and change between page 0 and page 1.
*/
// 4.2.1 Register map Page 0
#define R_All_Calibration(Data)               PG(0).ReadInts(0x55, 11, (int16_t *)Data)   //  All Calibration Values 3ACC 3MAG 3GYR AccRadius MagRadius 

#define R_MAG_RADIUS(Data)                    PG(0).ReadInt(0x69, (int16_t *)Data)        //  Magnetometer Radius
#define R_ACC_RADIUS(Data)                    PG(0).ReadInt(0x67, (int16_t *)Data)        //  Accelerometer Radius
 
#define R_GYR_OFFSET(Data)                    PG(0).ReadInt(0x61, 3, (int16_t *)Data)     //   Gyroscope Offset.

#define R_GYR_OFFSET_X(Data)                  PG(0).ReadInt(0x61, (int16_t *)Data)        //   Gyroscope Offset X.
#define R_GYR_OFFSET_Y(Data)                  PG(0).ReadInt(0x63, (int16_t *)Data)        //   Gyroscope Offset Y.
#define R_GYR_OFFSET_Z(Data)                  PG(0).ReadInt(0x65, (int16_t *)Data)        //   Gyroscope Offset Z.

#define R_MAG_OFFSET(Data)                    PG(0).ReadInt(0x5B, 3, (int16_t *)Data)     //   Magnetometer Offset.

#define R_MAG_OFFSET_X(Data)                  PG(0).ReadInt(0x5B, (int16_t *)Data)        //   Magnetometer Offset X.
#define R_MAG_OFFSET_Y(Data)                  PG(0).ReadInt(0x5D, (int16_t *)Data)        //   Magnetometer Offset Y.
#define R_MAG_OFFSET_Z(Data)                  PG(0).ReadInt(0x5F, (int16_t *)Data)        //   Magnetometer Offset Z.

#define R_ACC_OFFSET(Data)                    PG(0).ReadInt(0x55, 3, (int16_t *)Data)     //   Accelerometer Offset.

#define R_ACC_OFFSET_X(Data)                  PG(0).ReadInt(0x55, (int16_t *)Data)        //   Accelerometer Offset X.
#define R_ACC_OFFSET_Y(Data)                  PG(0).ReadInt(0x57, (int16_t *)Data)        //   Accelerometer Offset Y.
#define R_ACC_OFFSET_Z(Data)                  PG(0).ReadInt(0x59, (int16_t *)Data)        //   Accelerometer Offset Z.

//0x43 - 0x54 Reserved

#define R_AXIS_MAP_SIGN_X(Data)               PG(0).ReadBit(0x42, 1, 2, (uint8_t *)Data)  //   Remapped X axis sign
#define R_AXIS_MAP_SIGN_Y(Data)               PG(0).ReadBit(0x42, 1, 1, (uint8_t *)Data)  //   Remapped Y axis sign
#define R_AXIS_MAP_SIGN_Z(Data)               PG(0).ReadBit(0x42, 1, 0, (uint8_t *)Data)  //   Remapped Z axis sign

#define R_AXIS_MAP_CONFIG_X(Data)             PG(0).ReadBit(0x41, 2, 1, (uint8_t *)Data)  //   Remapped X axis value
#define R_AXIS_MAP_CONFIG_Y(Data)             PG(0).ReadBit(0x41, 2, 3, (uint8_t *)Data)  //   Remapped Y axis value
#define R_AXIS_MAP_CONFIG_Z(Data)             PG(0).ReadBit(0x41, 2, 5, (uint8_t *)Data)  //   Remapped Z axis value 

#define R_TEMP_SOURCE(Data)                   PG(0).ReadBit(0x40, 2, 1, (uint8_t *)Data)  //   TEMP_Source <1:0>

#define R_PWR_MODE(Data)                      PG(0).ReadBit(0x3E, 2, 1, (uint8_t *)Data)  //   Power Mode <1:0>

#define R_OPR_MODE(Data)                      PG(0).ReadBit(0x3D, 4, 3, (uint8_t *)Data)  //   Operation Mode <3:0>  Default 0x1C

//0x3C Reserved

#define R_UNIT_SEL(Data)                      PG(0).ReadByte(0x3B, (uint8_t *)Data)       //   Units Selection
#define R_UNIT_SEL_ORI_Android_Windows(Data)  PG(0).ReadBit(0x3B, 1, 7, (uint8_t *)Data)  //   ORI_Android_Windows
#define R_UNIT_SEL_TEMP_Unit(Data)            PG(0).ReadBit(0x3B, 1, 4, (uint8_t *)Data)  //   TEMP_Unit
#define R_UNIT_SEL_EUL_Unit(Data)             PG(0).ReadBit(0x3B, 1, 2, (uint8_t *)Data)  //   EUL_Unit
#define R_UNIT_SEL_GYR_Unit(Data)             PG(0).ReadBit(0x3B, 1, 1, (uint8_t *)Data)  //   GYR_Unit
#define R_UNIT_SEL_ACC_Uni(Data)              PG(0).ReadBit(0x3B, 1, 0, (uint8_t *)Data)  //   ACC_Uni

#define R_SYS_ERR(Data)                       PG(0).ReadByte(0x3A, (uint8_t *)Data)       //  System Error Code

#define R_SYS_STATUS(Data)                    PG(0).ReadByte(0x39, (uint8_t *)Data)       //  System Status Code

#define R_SYS_CLK_STATUS(Data)                PG(0).ReadBit(0x38, 1, 0, (uint8_t *)Data)  //   ST_MAIN_CLK

#define R_INT_STA_ACC_NM(Data)                PG(0).ReadBit(0x37, 1, 7, (uint8_t *)Data)  //   ACC_NM
#define R_INT_STA_ACC_AM(Data)                PG(0).ReadBit(0x37, 1, 6, (uint8_t *)Data)  //   ACC_AM
#define R_INT_STA_ACC_HIGH_G(Data)            PG(0).ReadBit(0x37, 1, 5, (uint8_t *)Data)  //   ACC_HIGH_G
#define R_INT_STA_GYR_HIGH_G(Data)            PG(0).ReadBit(0x37, 1, 3, (uint8_t *)Data)  //   ACC_HIGH_G
#define R_INT_STA_GYR_AM(Data)                PG(0).ReadBit(0x37, 1, 2, (uint8_t *)Data)  //   ACC_AM

#define R_ST_RESULT(Data)                     PG(0).ReadBit(0x36, 4, 3, (uint8_t *)Data)       //   Bit 0 = Acc, 1 = Mag,  2 = Gyro, 3 = MCU
#define R_ST_RESULT_ST_MCU(Data)              PG(0).ReadBit(0x36, 1, 3, (uint8_t *)Data)  //   ST_MCU
#define R_ST_RESULT_ST_GYR(Data)              PG(0).ReadBit(0x36, 1, 2, (uint8_t *)Data)  //   ST_GYR
#define R_ST_RESULT_ST_MAG(Data)              PG(0).ReadBit(0x36, 1, 1, (uint8_t *)Data)  //   ST_MAG
#define R_ST_RESULT_ST_ACC(Data)              PG(0).ReadBit(0x36, 1, 0, (uint8_t *)Data)  //   ST_ACC

#define R_CALIB_STAT(Data)                    PG(0).ReadByte(0x35,  (uint8_t *)Data)      //   Calibration Status 
#define R_SYS_CALIB_STAT(Data)                PG(0).ReadBit(0x35, 2, 7, (uint8_t *)Data)  //   SYS Calib Status 0:3
#define R_GYR_CALIB_STAT(Data)                PG(0).ReadBit(0x35, 2, 5, (uint8_t *)Data)  //   GYR Calib Status 0:3 
#define R_ACC_CALIB_STAT(Data)                PG(0).ReadBit(0x35, 2, 3, (uint8_t *)Data)  //   ACC Calib Status 0:3
#define R_MAG_CALIB_STAT(Data)                PG(0).ReadBit(0x35, 2, 1, (uint8_t *)Data)  //   MAG Calib Status 0:3

#define R_TEMP_Data(Data)                     PG(0).ReadByte(0x34, (uint8_t *)Data)       //  Temperature

#define R_GRV_Data(Data)                      PG(0).ReadInts(0x2E, 3, (int16_t *)Data)   //   Gravity Vector Data.
#define R_GRV_Data_X(Data)                    PG(0).ReadInt(0x2E, (int16_t *)Data)       //   Gravity Vector Data X <15:0>
#define R_GRV_Data_Y(Data)                    PG(0).ReadInt(0x30, (int16_t *)Data)       //   Gravity Vector Data Y <15:0>
#define R_GRV_Data_Z(Data)                    PG(0).ReadInt(0x32, (int16_t *)Data)       //   Gravity Vector Data Z <15:0>

#define R_LIA_Data(Data)                      PG(0).ReadInts(0x28, 3, (int16_t *)Data)   //   Linear Acceleration Data.
#define R_LIA_Data_X(Data)                    PG(0).ReadInt(0x28, (int16_t *)Data)       //   Linear Acceleration Data X <15:0>
#define R_LIA_Data_Y(Data)                    PG(0).ReadInt(0x2A, (int16_t *)Data)       //   Linear Acceleration Data Y <15:0>
#define R_LIA_Data_Z(Data)                    PG(0).ReadInt(0x2C, (int16_t *)Data)       //   Linear Acceleration Data Z <15:0>

#define R_QUA_Data(Data)                      PG(0).ReadInts(0x20, 4, (int16_t *)Data)   //   Quaternion Data.
#define R_QUA_Data_W(Data)                    PG(0).ReadInt(0x20, (int16_t *)Data)       //   Quaternion W Data <15:0>
#define R_QUA_Data_X(Data)                    PG(0).ReadInt(0x22, (int16_t *)Data)       //   Quaternion X Data <15:0>
#define R_QUA_Data_Y(Data)                    PG(0).ReadInt(0x24, (int16_t *)Data)       //   Quaternion Y Data <15:0>
#define R_QUA_Data_Z(Data)                    PG(0).ReadInt(0x26, (int16_t *)Data)       //   Quaternion Z Data <15:0>

#define R_EUL_Data(Data)                      PG(0).ReadInts(0x1A, 3, (int16_t *)Data)   //   Euler Heading Pitch and Roll.
#define R_EUL_Heading(Data)                   PG(0).ReadInt(0x1A, (int16_t *)Data)       //   Euler Heading Data < <15:0>
#define R_EUL_Roll(Data)                      PG(0).ReadInt(0x1C, (int16_t *)Data)       //   Euler Roll <15:0>
#define R_EUL_Pitch(Data)                     PG(0).ReadInt(0x1E, (int16_t *)Data)       //   Euler Pitch <15:0>

#define R_GYR_DATA(Data)                      PG(0).ReadInts(0x14, 3, (int16_t *)Data)   //   Gyroscope Data
#define R_GYR_DATA_X(Data)                    PG(0).ReadInt(0x14, (int16_t *)Data)       //   Gyroscope Data X <15:0>
#define R_GYR_DATA_Y(Data)                    PG(0).ReadInt(0x16, (int16_t *)Data)       //   Gyroscope Data Y <15:0>
#define R_GYR_DATA_Z(Data)                    PG(0).ReadInt(0x18, (int16_t *)Data)       //   Gyroscope Data Z <15:0>

#define R_MAG_DATA(Data)                      PG(0).ReadInts(0x0E, 3, (int16_t *)Data)   //   Magnetometer Data
#define R_MAG_DATA_X(Data)                    PG(0).ReadInt(0x0E, (int16_t *)Data)       //   Magnetometer Data X <15:0>
#define R_MAG_DATA_Y(Data)                    PG(0).ReadInt(0x10, (int16_t *)Data)       //   Magnetometer Data Y <15:0>
#define R_MAG_DATA_Z(Data)                    PG(0).ReadInt(0x12, (int16_t *)Data)       //   Magnetometer Data Z <15:0>

#define R_ACC_DATA(Data)                      PG(0).ReadInts(0x08, 3, (int16_t *)Data)   //   Magnetometer Data
#define R_ACC_DATA_X(Data)                    PG(0).ReadInt(0x08, (int16_t *)Data)       //   Magnetometer Data X <15:0>
#define R_ACC_DATA_Y(Data)                    PG(0).ReadInt(0x0A, (int16_t *)Data)       //   Magnetometer Data Y <15:0>
#define R_ACC_DATA_Z(Data)                    PG(0).ReadInt(0x0C, (int16_t *)Data)       //   Magnetometer Data Z <15:0>

#define R_Page_ID(Data)                             ReadByte(0x07, (uint8_t *)Data)       //   Page ID
#define R_BL_Rev_ID (Data)                    PG(0).ReadByte(0x06, (uint8_t *)Data)       //   Bootloader Version 
#define R_SW_REV_ID(Data)                     PG(0).ReadUInt(0x04, (uint16_t *)Data)      //   SW Revision ID Default 0x0308
#define R_GYR_ID(Data)                        PG(0).ReadByte(0x03, (uint8_t *)Data)       //   GYRO chip ID Default 0x0F
#define R_MAG_ID(Data)                        PG(0).ReadByte(0x02, (uint8_t *)Data)       //   MAG chip ID Default 0x32
#define R_ACC_ID(Data)                        PG(0).ReadByte(0x01, (uint8_t *)Data)       //   ACC chip ID Default 0xFB
#define R_CHIP_ID(Data)                       PG(0).ReadByte(0x00, (uint8_t *)Data)       //   BNO055 CHIP ID Default 0xA0 
#define CHIP_ID                               0xA0                                        //   BNO055 CHIP ID Default 0xA0 

//4.2.2 Register map Page 1

//0x7F-0x60 Reserved
//0x5F - 0x50   BNO unique ID
//0x4F - 0x20 Reserved

#define R_GYR_AM_SET_Awake_Duration(Data)     PG(1).ReadBit(0x1F, 2, 3, (uint8_t *)Data)  //   Awake Duration
#define R_GYR_AM_SET_Slope_Samples(Data)      PG(1).ReadBit(0x1F, 2, 1, (uint8_t *)Data)  //   Slope Samples

#define R_GYR_AM_THRES(Data)                  PG(1).ReadBit(0x1E, 7, 6, (uint8_t *)Data)  //   Gyro Any Motion Threshold <6:0>

#define R_GYR_DUR_Z(Data)                     PG(1).ReadByte(0x1D, (uint8_t *)Data)       //   HR_Z_Duration

#define R_GYR_HR_Z_SET_THRES_HYST(Data)       PG(1).ReadBit(0x1C, 2, 6, (uint8_t *)Data)  //   HR_Z_THRES_HYST
#define R_GYR_HR_Z_SET_Threshold(Data)        PG(1).ReadBit(0x1C, 5, 4, (uint8_t *)Data)  //   HR_Z_Threshold

#define R_GYR_DUR_Y(Data)                     PG(1).ReadByte(0x1B, (uint8_t *)Data)       //   HR_Y_Duration

#define R_GYR_HR_Y_SET_THRES_HYST(Data)       PG(1).ReadBit(0x1A, 2, 6, (uint8_t *)Data)  //   HR_Y_THRES_HYST
#define R_GYR_HR_Y_SET_Threshold(Data)        PG(1).ReadBit(0x1A, 5, 4, (uint8_t *)Data)  //   HR_Y_Threshold

#define R_GYR_DUR_X(Data)                     PG(1).ReadByte(0x19, (uint8_t *)Data)       //   HR_X_Duration

#define R_GYR_HR_X_SET_THRES_HYST(Data)       PG(1).ReadBit(0x18, 2, 6, (uint8_t *)Data)  //   HR_X_THRES_HYST
#define R_GYR_HR_X_SET_Threshold(Data)        PG(1).ReadBit(0x18, 5, 4, (uint8_t *)Data)  //   HR_X_Threshold

#define R_GYR_INT_SETING_HR_FILT (Data)       PG(1).ReadBit(0x17, 1, 7, (uint8_t *)Data)  //   HR_FILT
#define R_GYR_INT_SETING_AM_FILT (Data)       PG(1).ReadBit(0x17, 1, 6, (uint8_t *)Data)  //   AM_FILT
#define R_GYR_INT_SETING_HR_Z_AXIS (Data)     PG(1).ReadBit(0x17, 1, 5, (uint8_t *)Data)  //   HR_Z_AXIS
#define R_GYR_INT_SETING_HR_Y_AXIS (Data)     PG(1).ReadBit(0x17, 1, 4, (uint8_t *)Data)  //   HR_Y_AXIS
#define R_GYR_INT_SETING_HR_X_AXIS (Data)     PG(1).ReadBit(0x17, 1, 3, (uint8_t *)Data)  //   HR_X_AXIS
#define R_GYR_INT_SETING_AM_Z_AXIS (Data)     PG(1).ReadBit(0x17, 1, 2, (uint8_t *)Data)  //   AM_Z_AXIS
#define R_GYR_INT_SETING_AM_Y_AXIS (Data)     PG(1).ReadBit(0x17, 1, 1, (uint8_t *)Data)  //   AM_Y_AXIS
#define R_GYR_INT_SETING_AM_X_AXIS (Data)     PG(1).ReadBit(0x17, 1, 0, (uint8_t *)Data)  //   AM_X_AXIS

#define R_ACC_NM_SET_NO_SLOW_Mo_Dur(Data)     PG(1).ReadBit(0x16, 6, 6, (uint8_t *)Data)  //   ACC NO/SLOW Motion Duration
#define R_ACC_NM_SET_SMNM(Data)               PG(1).ReadBit(0x16, 1, 0, (uint8_t *)Data)  //   ACC SMNM

#define R_ACC_NM_THRE(Data)                   PG(1).ReadByte(0x15, (uint8_t *)Data)       //   Accelerometer NO/SLOW motion threshold

#define R_ACC_HG_THRES(Data)                  PG(1).ReadByte(0x14, (uint8_t *)Data)       //   Accelerometer High G Threshold

#define R_ACC_HG_DURATION(Data)               PG(1).ReadByte(0x13, (uint8_t *)Data)       //   Accelerometer High G Duration

#define R_ACC_INT_Set_HG_Z_AXIS(Data)         PG(1).ReadBit(0x12, 1, 7, (uint8_t *)Data)  //   HG_Z_AXIS
#define R_ACC_INT_Set_HG_Y_AXIS(Data)         PG(1).ReadBit(0x12, 1, 6, (uint8_t *)Data)  //   HG_Y_AXIS
#define R_ACC_INT_Set_HG_X_AXIS(Data)         PG(1).ReadBit(0x12, 1, 5, (uint8_t *)Data)  //   HG_X_AXIS
#define R_ACC_INT_Set_AM_NM_Z_AXIS(Data)      PG(1).ReadBit(0x12, 1, 4, (uint8_t *)Data)  //   AM/NM_Z_AXIS
#define R_ACC_INT_Set_AM_NM_Y_AXIS(Data)      PG(1).ReadBit(0x12, 1, 3, (uint8_t *)Data)  //   AM/NM_Z_AXIS
#define R_ACC_INT_Set_AM_NM_X_AXIS(Data)      PG(1).ReadBit(0x12, 1, 2, (uint8_t *)Data)  //   AM/NM_Z_AXIS
#define R_ACC_INT_Set_AM_DUR(Data)            PG(1).ReadBit(0x12, 2, 1, (uint8_t *)Data)  //   AM_DUR 

#define R_ACC_AM_THRES(Data)                  PG(1).ReadByte(0x11, (uint8_t *)Data)       //   Accelerometer Any motion threshold

#define R_INT_EN_ACC_NM(Data)                 PG(1).ReadBit(0x10, 1, 7, (uint8_t *)Data)  //   ACC_NM
#define R_INT_EN_ACC_AM(Data)                 PG(1).ReadBit(0x10, 1, 6, (uint8_t *)Data)  //   ACC_AM
#define R_INT_EN_ACC_HIGH_g(Data)             PG(1).ReadBit(0x10, 1, 5, (uint8_t *)Data)  //   ACC_HIGH_G
#define R_INT_EN_GYR_HIGH_RATE(Data)          PG(1).ReadBit(0x10, 1, 3, (uint8_t *)Data)  //   GYR_HIGH_RATE
#define R_INT_EN_GYR_AM(Data)                 PG(1).ReadBit(0x10, 1, 2, (uint8_t *)Data)  //   GYR_AM

#define R_INT_MSK_ACC_NM(Data)                PG(1).ReadBit(0x0F, 1, 7, (uint8_t *)Data)  //   ACC_NM
#define R_INT_MSK_ACC_AM(Data)                PG(1).ReadBit(0x0F, 1, 6, (uint8_t *)Data)  //   ACC_AM
#define R_INT_MSK_ACC_HIGH_g(Data)            PG(1).ReadBit(0x0F, 1, 5, (uint8_t *)Data)  //   ACC_HIGH_G
#define R_INT_MSK_GYR_HIGH_RATE(Data)         PG(1).ReadBit(0x0F, 1, 3, (uint8_t *)Data)  //   GYR_HIGH_RATE
#define R_INT_MSK_GYR_AM(Data)                PG(1).ReadBit(0x0F, 1, 2, (uint8_t *)Data)  //   GYR_AM

//0x0E Reserved 
#define R_GYR_Sleep_Config_AUTO_SLP_DUR(Data) PG(1).ReadBit(0x0D, 3, 5, (uint8_t *)Data)  //   AUTO_SLP_DURATION
#define R_GYR_Sleep_Config_SLP_DURATION(Data) PG(1).ReadBit(0x0D, 3, 2, (uint8_t *)Data)  //   SLP_DURATION

#define R_ACC_Sleep_Config_SLP_DURATION(Data) PG(1).ReadBit(0x0C, 4, 4, (uint8_t *)Data)  //   SLP_DURATION
#define R_ACC_Sleep_Config_SLP_MODE(Data)     PG(1).ReadBit(0x0C, 1, 0, (uint8_t *)Data)  //   SLP_MODE

#define R_GYR_Config_1_Power_Mode(Data)       PG(1).ReadBit(0x0B, 3, 2, (uint8_t *)Data)  //   GYR_Power_Mode

#define R_GYR_Config_0_Bandwidth(Data)        PG(1).ReadBit(0x0A, 3, 5, (uint8_t *)Data)  //   GYR_Bandwidth
#define R_GYR_Config_0_Range(Data)            PG(1).ReadBit(0x0A, 3, 2, (uint8_t *)Data)  //   GYR_Range

#define R_MAG_Config_Power_mode(Data)         PG(1).ReadBit(0x09, 2, 6, (uint8_t *)Data)  //   MAG_Power_mode
#define R_MAG_Config_OPR_Mode(Data)           PG(1).ReadBit(0x09, 2, 4, (uint8_t *)Data)  //   MAG_OPR_Mode 
#define R_MAG_Config_Data_output_rate(Data)   PG(1).ReadBit(0x09, 3, 2, (uint8_t *)Data)  //   MAG_Data_output_rate

#define R_ACC_Config_PWR_Mode(Data)           PG(1).ReadBit(0x09, 3, 7, (uint8_t *)Data)  //   ACC_PWR_Mode
#define R_ACC_Config_BW(Data)                 PG(1).ReadBit(0x09, 3, 7, (uint8_t *)Data)  //   ACC_BW
#define R_ACC_Config_Range(Data)              PG(1).ReadBit(0x09, 3, 7, (uint8_t *)Data)  //   ACC_Range

//0x06 - 0x00 Reserved

#endif