//------------For Testing----------
//#include <Servo.h>
//// HI
//Servo leftBrake;
//Servo rightBrake;
//Servo steering;
//Servo throttle;
//
//const int LEFT_BRAKE_MOTOR = 8;
//const int RIGHT_BRAKE_MOTOR = 11;
//const int THROTTLE_MOTOR = 10;  ////////Will change once we wire///////
//const int STEERING_SERVO = 9;
//------Remove after testing------------

const int MOTOR_VALUE_STOP = 0;
const int MOTOR_VALUE_CENTER = 90;

const int SERIAL_COMMAND_SET_THROTTLE_MOTOR = 254;
const int SERIAL_COMMAND_SET_STEERING_MOTOR = 255;
const int SERIAL_COMMAND_SET_LEFT_BRAKE = 253;
const int SERIAL_COMMAND_SET_RIGHT_BRAKE = 252;

const unsigned long TIME_BETWEEN_GET_DATA = 50;
const long SERIAL_DATA_SPEED_38400_BPS = 9600;

int JOYSTICK_STEERING = A2;
int JOYSTICK_THROTTLE = A3;
int LEFT_BRAKE = A0;
int RIGHT_BRAKE = A1;


int throttleVal;
int steeringVal;
int leftBrakeVal;
int rightBrakeVal;


unsigned long previousTime;

void setup()
{
  Serial.begin(SERIAL_DATA_SPEED_38400_BPS);

  //--------------FOR TESTING------------------------
//  leftBrake.attach (LEFT_BRAKE_MOTOR);
//  leftBrake.write(MOTOR_VALUE_STOP);
//
//  rightBrake.attach(RIGHT_BRAKE_MOTOR);
//  rightBrake.write(MOTOR_VALUE_STOP);
//
//  throttle.attach(THROTTLE_MOTOR);
//  throttle.write(MOTOR_VALUE_STOP);
//
//  steering.attach(STEERING_SERVO);
//  steering.write(MOTOR_VALUE_CENTER);
  //----------REMOVE AFTER TESTING-----------------

  previousTime = millis();
}

void loop()
{
  int throttleVal = 0;
  int steeringVal = 0;
  int leftBrakeVal = 0;
  int rightBrakeVal = 0;

  if (millis() - previousTime >= TIME_BETWEEN_GET_DATA)
  {
    throttleVal = analogRead(JOYSTICK_THROTTLE);
    delayMicroseconds(20);
    steeringVal = analogRead(JOYSTICK_STEERING);
    delayMicroseconds(20);
    leftBrakeVal = analogRead(LEFT_BRAKE);
    delayMicroseconds(20);
    rightBrakeVal = analogRead(RIGHT_BRAKE);



    throttleVal = constrain(throttleVal, 512, 1023);
    throttleVal = map(throttleVal, 512, 1023, 0, 50);

    steeringVal = map(steeringVal, 0, 1023, 0, 100);


    leftBrakeVal = map(leftBrakeVal, 0, 1023, 0, 100);
    rightBrakeVal = map(rightBrakeVal, 0, 1023, 0, 100);

    SendNewMotorValues(throttleVal, steeringVal, leftBrakeVal, rightBrakeVal);
    previousTime = millis();

    //-------------FOR TESTING-----------------------
//    leftBrake.write(leftBrakeVal);
//    rightBrake.write(rightBrakeVal);
//    throttle.write(throttleVal);
//    steering.write(steeringVal);
    //---------------REMOVE WHEN FINISHED---------------
  }
}




//****************************** SUBROUTINES ************************************
void SendNewMotorValues(char thrust, char turn, char leftBrake, char rightBrake)
{
  Serial.write (SERIAL_COMMAND_SET_LEFT_BRAKE);
  Serial.write (leftBrake);

  Serial.write (SERIAL_COMMAND_SET_RIGHT_BRAKE);
  Serial.write (rightBrake);

  Serial.write (SERIAL_COMMAND_SET_STEERING_MOTOR);
  Serial.write (turn);

  Serial.write (SERIAL_COMMAND_SET_THROTTLE_MOTOR);
  Serial.write (thrust);



//  Serial.print(leftBrake, DEC);
//  Serial.print("   ");
//  Serial.print(rightBrake, DEC);
//  Serial.print("   ");
//  Serial.print(turn, DEC);
//  Serial.print("   ");
//  Serial.println(thrust, DEC);
  
  
  
}



