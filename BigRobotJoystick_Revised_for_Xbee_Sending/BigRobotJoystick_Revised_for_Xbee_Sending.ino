

const int MOTOR_VALUE_STOP = 0;

const int SERIAL_COMMAND_SET_THROTTLE_MOTOR = 254;
const int SERIAL_COMMAND_SET_STEERING_MOTOR = 255;
const int SERIAL_COMMAND_SET_LEFT_BRAKE = 253;
const int SERIAL_COMMAND_SET_RIGHT_BRAKE = 252;

const unsigned long TIME_BETWEEN_GET_DATA = 100;
const long SERIAL_DATA_SPEED_38400_BPS = 38400;

int JOYSTICK_STEERING = A4;
int JOYSTICK_THROTTLE = A5;
int LEFT_BRAKE = A3;
int RIGHT_BRAKE = A2;


int throttleVal;
int steeringVal;
int leftBrakeVal;
int rightBrakeVal;


unsigned long previousTime;

void setup()
{
  Serial.begin(SERIAL_DATA_SPEED_38400_BPS);

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
    steeringVal = analogRead(JOYSTICK_STEERING);
    leftBrakeVal = analogRead(LEFT_BRAKE);
    rightBrakeVal = analogRead(RIGHT_BRAKE);

    throttleVal = constrain(throttleVal, 512, 1023);
    throttleVal = map(throttleVal, 512, 1023, 0, 50);

    steeringVal = map(steeringVal, 0, 180);

    leftBrakeVal = map(leftBrakeVal, 0, 180);
    rightBrakeVal = map(rightBrakeVal, 0, 180);

    SendNewMotorValues(throttleVal, steeringVal, leftBrakeVal, rightBrakeVal);
    previousTime = millis();
  }
}
}



//****************************** SUBROUTINES ************************************
void SendNewMotorValues(char thrust, char turn, char leftBrake, char rightBrake)
{
  Serial.write (SERIAL_COMMAND_SET_THROTTLE_MOTOR);
  Serial.write (thrust);

  Serial.write (SERIAL_COMMAND_SET_STEERING_MOTOR);
  Serial.write (turn);

  Serial.write (SERIAL_COMMAND_SET_LEFT_BRAKE);
  Serial.write (leftBrake);

  Serial.write (SERIAL_COMMAND_SET_RIGHT_BRAKE);
  Serial.write (rightBrake);
  
  Serial.print(thrust, DEC);
  Serial.print("   ");
  Serial.println(turn, DEC);
}



