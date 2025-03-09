# Simple_BNO055
<h2>Introducing Simple_BNO055, the Easy-to-Use Arduino Library for the Bosch Sensortec MEMS BNO055 Sensor!</h2>
<p>If you've ever worked with a 9-DOF sensor, you know how challenging it can be to turn the sensor data from an accelerometer, gyroscope, and magnetometer into actual "3D space orientation." But now, with Simple_BNO055, you can have meaningful sensor data in minutes, thanks to the powerful sensor fusion algorithms and real-time capabilities of the BNO055.</p>
<p>This library makes it easy to integrate into your project. You can also take advantage of the BNO055's ability to output a wide range of sensor data, including absolute orientation in Euler vectors or quaternions, angular velocity vector, acceleration vector, magnetic field strength vector, linear acceleration vector, gravity vector, and ambient temperature.</p>
<p>The BNO055 sensor has several modes that can be easily accessed through the Simple_BNO055 library for the Arduino platform. These modes can be selected by setting the appropriate value for the Set_Mode() function. Here's a brief overview of the different modes available:</p>
<h2>BNO055 Sensor Modes</h2>
<h3>Non-Fusion Modes:</h3>
<ul>
  <li>CONFIGMODE: This mode is used for configuration, where all output data is reset to zero and sensor fusion is halted.</li>
  <li>ACCONLY: This mode provides raw accelerometer data only.</li>
  <li>MAGONLY: This mode behaves like a stand-alone magnetometer, providing magnetometer data only.</li>
  <li>GYRONLY: This mode behaves like a stand-alone gyroscope, providing gyroscope data only.</li>
  <li>ACCMAG: This mode enables both accelerometer and magnetometer data.</li>
  <li>ACCGYRO: This mode enables both accelerometer and gyroscope data.</li>
  <li>MAGGYRO: This mode enables both magnetometer and gyroscope data.</li>
  <li>AMG: This mode enables all three sensors (accelerometer, magnetometer, and gyroscope) to be switched on.</li>
</ul>
<h3>Fusion Modes:</h3>
<ul>
  <li>IMU: This mode calculates relative orientation in space from the accelerometer and gyroscope data.</li>
  <li>COMPASS: This mode is used for heading calculation, where only the horizontal components x and y are used. The compass mode requires calibration.</li>
  <li>M4G: This mode is similar to the IMU mode, but the changing orientation of the magnetometer in the magnetic field is used.</li>
  <li>NDOF_FMC_OFF: This mode is the same as NDOF mode, but with the Fast Magnetometer Calibration turned 'OFF'.</li>
  <li>NDOF: This mode provides absolute orientation data that is calculated from the accelerometer, gyroscope, and magnetometer. This mode is also referred to as the 9-degrees of freedom mode.</li>
</ul>

Required Library<br>
Library Name: Simple_Wire<br>
Version: 1.0.0<br>
<a href="https://github.com/ZHomeSlice/Simple_Wire">Simple_Wire library on GitHub</a>
Description: Easy-to-use Arduino Library for I2C communication that simplifies reading and writing data to I2C devices. The library uses the standard Wire library and provides a simpler syntax for sending and receiving data, as well as optional error checking. The library is designed for novice programmers and those new to I2C communication.
