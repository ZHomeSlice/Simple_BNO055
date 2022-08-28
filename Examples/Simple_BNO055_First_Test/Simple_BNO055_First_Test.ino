#include "Simple_BNO055.h"
Simple_BNO055 BNO;

// Blink Without Delay Serial Port Spam Timer Macro
#define spamtimer(t) for (static uint32_t SpamTimer; (uint32_t)(millis() - SpamTimer) >= (t); SpamTimer = millis()) // Another Way to do a Blink without Delay timer
#define printfloat(Name,Variable,Spaces,Precision,EndTxt) print(Name); Serial.print(F(" ")); Serial.print(Variable,Precision);Serial.print(EndTxt);//Name,Variable,Spaces,Precision,EndTxt
  /* Get_Values() Type options:
     Get_MAGNETOMETER  0
     Get_GYROSCOPE     1
     Get_EULER         2
     Get_ACCELEROMETER 3
     Get_LINEARACCEL   4
     Get_GRAVITY       5
     Get_QUATERNION    6
  */
void Print_QUATERNION() {
  double Value[4];
  BNO.Get_Values(Value, Get_QUATERNION);
  spamtimer(100) { //Serial port can only handle 10 per second.
    double quatw = Value[0];
    double quatx = Value[1];
    double quaty = Value[2];
    double quatz = Value[3];

    /* Create Roll Pitch Yaw Angles from Quaternions */
    double yy = quaty  * quaty ; // 2 Uses below

    double roll = atan2(2 * (quatw  * quatx  + quaty  * quatz ), 1 - 2 * (quatx  * quatx  + yy));
    double pitch = asin(2 * quatw  * quaty  - quatx  * quatz );
    double yaw = atan2(2 * (quatw  * quatz  + quatx  * quaty ), 1 - 2 * (yy + quatz  * quatz ));

    /*  Convert Radians to Degrees */

    float rollDeg  = 57.2958 * roll;
    float pitchDeg = 57.2958 * pitch;
    float yawDeg   = 57.2958 * yaw;

    Serial.printfloat("yaw ", yawDeg, 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("pitch ", pitchDeg, 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("roll ", rollDeg, 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.println();
  }
}
void Print_EULER() {

  double Value[4];
  BNO.Get_Values(Value, Get_EULER);
  spamtimer(100) { //Serial port can only handle 10 per second.
    Serial.print(BNO.Check_Calibration(false,4));
    Serial.printfloat(" yaw ", Value[0], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("pitch ", Value[1], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("roll ", Value[2], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.println();
  }
}
void Print_MAGNETOMETER() {
  double Value[4];
  BNO.Get_Values(Value, Get_MAGNETOMETER);
  spamtimer(100) { //Serial port can only handle 10 per second.
    Serial.print(BNO.Check_Calibration(false,4));
    Serial.printfloat(" yaw ", Value[0], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("pitch ", Value[1], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.printfloat("roll ", Value[2], 6, 2, " "); //Name,Variable,Spaces,Precision,EndTxt
    Serial.println();
  }
}
void Print_Values(){
  //Print_QUATERNION();
  Print_EULER();
  //Print_MAGNETOMETER();
}

void setup() {
  // initialize serial communication
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("Start:"));
  if (!BNO.Begin().TestConnection()) {
    Serial.println(F("Failed to connect.\nEND..."));
    while (1) {};
  }
  Serial.println(F("Connected!"));
  BNO.Initialize();
  /*
    4.3.61 OPR_MODE 0x3D for W_OPR_MODE(Data);
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
  BNO.Set_Mode(COMPASS);
  
}


void loop() {
  spamtimer(10) { // lets slow our requests doen to 100 per second
    Print_Values();
  }
  spamtimer(1000) { // lets slow our requests doen to 1 per second
   // BNO.Check_Calibration(1);
   // BNO.Check_Calibration(2);
   // BNO.Check_Calibration(3);
  // BNO.Check_Calibration(false,4);
  }
}
