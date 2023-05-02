# Simple_BNO055
Introducing Simple_BNO055, the easy-to-use Arduino Library for the Bosch Sensortec MEMS BNO055 sensor! If you've ever worked with a 9-DOF sensor, you know how challenging it can be to turn the sensor data from an accelerometer, gyroscope, and magnetometer into actual "3D space orientation." But now, with Simple_BNO055, you can have meaningful sensor data in minutes, thanks to the powerful sensor fusion algorithms and real-time capabilities of the BNO055.

Simple_BNO055 provides a simple abstraction layer between your Arduino project and the BNO055 sensor, allowing you to drop in any comparable sensor with only a few lines of code to modify. You can also easily perform quick sanity checks when working with new sensors, or swap in any compatible sensor if you require greater sensitivity or a cheaper unit becomes available.

This library includes the necessary header files and sensor driver APIs for the BNO055 sensor, making it easy to integrate into your project. You can also take advantage of the BNO055's ability to output a wide range of sensor data, including absolute orientation in Euler vectors or quaternions, angular velocity vector, acceleration vector, magnetic field strength vector, linear acceleration vector, gravity vector, and ambient temperature.

The BNO055 sensor has several modes that can be easily accessed through the Simple_BNO055 library for the Arduino platform. These modes can be selected by setting the appropriate value for the Set_Mode() function. Here's a brief overview of the different modes available:

--- Non-Fusion Modes:

CONFIGMODE: This mode is used for configuration, where all output data is reset to zero and sensor fusion is halted.
ACCONLY: This mode provides raw accelerometer data only.
MAGONLY: This mode behaves like a stand-alone magnetometer, providing magnetometer data only.
GYRONLY: This mode behaves like a stand-alone gyroscope, providing gyroscope data only.
ACCMAG: This mode enables both accelerometer and magnetometer data.
ACCGYRO: This mode enables both accelerometer and gyroscope data.
MAGGYRO: This mode enables both magnetometer and gyroscope data.
AMG: This mode enables all three sensors (accelerometer, magnetometer, and gyroscope) to be switched on.

--- Fusion Modes:

IMU: This mode calculates relative orientation in space from the accelerometer and gyroscope data.
COMPASS: This mode is used for heading calculation, where only the horizontal components x and y are used. The compass mode requires calibration.
M4G: This mode is similar to the IMU mode, but the changing orientation of the magnetometer in the magnetic field is used.
NDOF_FMC_OFF: This mode is the same as NDOF mode, but with the Fast Magnetometer Calibration turned 'OFF'.
NDOF: This mode provides absolute orientation data that is calculated from the accelerometer, gyroscope, and magnetometer. This mode is also referred to as the 9-degrees of freedom mode.
