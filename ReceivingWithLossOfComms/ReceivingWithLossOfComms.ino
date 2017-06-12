#include <Servo.h>

Servo brake;
Servo steering;
Servo throttle;

const int BRAKE_MOTOR = 8;
const int THROTTLE_MOTOR = 9;  
const int STEERING_SERVO = 7;

const int MOTOR_VALUE_OFF = 0;
const int MOTOR_VALUE_MAX = 179;
const int MOTOR_VALUE_CENTER = 90;

const int NUMBER_OF_BYTES_IN_A_COMMAND = 6;
const int SERIAL_COMMAND_SET_THROTTLE_MOTOR = 254;
const int SERIAL_COMMAND_SET_STEERING_MOTOR = 255;
const int SERIAL_COMMAND_SET_BRAKE = 253;
const int SERIAL_COMMAND_RECEIVED = 250;

const long SERIAL_DATA_SPEED_9600_BPS = 9600;
const unsigned long MAX_TIMEOUT = 250;
unsigned long previousTime;

void setup()
{
  previousTime = millis();
  Serial.begin(SERIAL_DATA_SPEED_9600_BPS);

  brake.attach(BRAKE_MOTOR);
  brake.write(MOTOR_VALUE_OFF);

  throttle.attach(THROTTLE_MOTOR);
  throttle.write(MOTOR_VALUE_OFF);

  steering.attach(STEERING_SERVO);
  steering.write(MOTOR_VALUE_CENTER);
}

void loop()
{
  static char brakeVal = 0;
  static char throttleVal = 0;
  static char steeringVal = 50;

  if (Serial.available() >= NUMBER_OF_BYTES_IN_A_COMMAND)
  {
    int incomingByte = Serial.read();
    
    if (SERIAL_COMMAND_SET_BRAKE == incomingByte)
    {
      brakeVal = Serial.read();
      Serial.write(SERIAL_COMMAND_RECEIVED);
      previousTime = millis();
    }
    else if (SERIAL_COMMAND_SET_STEERING_MOTOR == incomingByte)
    {
      steeringVal = Serial.read();
      Serial.write(SERIAL_COMMAND_RECEIVED);
      previousTime = millis();
    }
    else if (SERIAL_COMMAND_SET_THROTTLE_MOTOR == incomingByte)
    {
      throttleVal = Serial.read();
      Serial.write(SERIAL_COMMAND_RECEIVED);
      previousTime = millis();
    }
  }

  //If no new signals recieved for 5 cycles of reading
  if (millis() - previousTime >= MAX_TIMEOUT)
  {
    throttle.write(MOTOR_VALUE_OFF);
    brake.write(MOTOR_VALUE_MAX);
    steering.write(MOTOR_VALUE_CENTER);
  }

  brake.write(map(brakeVal, 0, 100, 50, 0));
  throttle.write(map(throttleVal, 0, 100, 40, 60));
  steering.write(map(steeringVal, 0, 100, 125, 70));
}
