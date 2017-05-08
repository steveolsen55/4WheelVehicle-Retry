#include <Servo.h>
// HI
Servo leftBrake;
Servo rightBrake;
Servo steering;
Servo throttle;     ////////Is this a servo???

const int LEFT_BRAKE_MOTOR = 8;
const int RIGHT_BRAKE_MOTOR = 11;
const int THROTTLE_MOTOR = 5;  ////////Will change once we wire///////
const int STEERING_SERVO = 6;


const int MOTOR_VALUE_OFF = 0;        ////////Test to make sure these values 
const int MOTOR_VALUE_MAX = 179;      /////// will work (These are assuming 0
const int MOTOR_VALUE_CENTER = 90;    /////// is no brakes and 179 is full brakes)

const int NUMBER_OF_BYTES_IN_A_COMMAND = 8;
const int SERIAL_COMMAND_SET_THROTTLE_MOTOR = 254;
const int SERIAL_COMMAND_SET_STEERING_MOTOR = 255;
const int SERIAL_COMMAND_SET_LEFT_BRAKE = 253;
const int SERIAL_COMMAND_SET_RIGHT_BRAKE = 252;

const long SERIAL_DATA_SPEED_38400_BPS = 38400;

void setup()
{
  Serial.begin(SERIAL_DATA_SPEED_38400_BPS);

  leftBrake.attach (LEFT_BRAKE_MOTOR);
  leftBrake.write(MOTOR_VALUE_OFF);

  rightBrake.attach(RIGHT_BRAKE_MOTOR);
  rightBrake.write(MOTOR_VALUE_OFF);

  throttle.attach(THROTTLE_MOTOR);
  throttle.write(MOTOR_VALUE_OFF);

  steering.attach(STEERING_SERVO);
  steering.write(MOTOR_VALUE_CENTER);
}

void loop()
{
  static char rightBrakeVal = 0;
  static char leftBrakeVal = 0;
  static char throttleVal = 0;
  static char steeringVal = 90;
  Serial.println( Serial.available());
  if (Serial.available() > NUMBER_OF_BYTES_IN_A_COMMAND)
  {
    int incomingByte = Serial.read();
//    Serial.print( incomingByte);
    Serial.println("a");
    if (SERIAL_COMMAND_SET_LEFT_BRAKE == incomingByte)
    {
      leftBrakeVal = Serial.read();
//      Serial.print(leftBrakeVal);
Serial.println("b");
    }
    if (SERIAL_COMMAND_SET_RIGHT_BRAKE == incomingByte)
    {
      rightBrakeVal = Serial.read();
//      Serial.print(rightBrakeVal);
      Serial.println("c");
    }
    if (SERIAL_COMMAND_SET_THROTTLE_MOTOR == incomingByte)
    {
      throttleVal = Serial.read();
//      Serial.print(throttleVal);
      Serial.println("d");
    }    
    if (SERIAL_COMMAND_SET_STEERING_MOTOR == incomingByte)
    {
      steeringVal = Serial.read();
      Serial.println(steeringVal);
      Serial.println("e");
    }
    leftBrake.write(map(leftBrakeVal,0,100,0,179));
    rightBrake.write(map(rightBrakeVal,0,100,0,179));
    throttle.write(throttleVal);
    steering.write(map(steeringVal,0,100,0,179));
  }
}


