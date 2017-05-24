const int SERIAL_COMMAND_SET_THROTTLE_MOTOR = 254;
const int SERIAL_COMMAND_SET_STEERING_MOTOR = 255;
const int SERIAL_COMMAND_SET_LEFT_BRAKE = 253;
const int SERIAL_COMMAND_SET_RIGHT_BRAKE = 252;
const int SERIAL_COMMAND_RECEIVED = 250;

const int NUMBER_OF_BYTES_IN_A_COMMAND = 1;

const unsigned long TIME_BETWEEN_GET_DATA = 50;
const long SERIAL_DATA_SPEED_9600_BPS = 9600;
const unsigned long MAX_TIMEOUT = 250;

// Active Low LED's
int POWER_LED = 2;          //Red
int COMS_GOOD_LED = 13;       //Green
int COMS_BAD_LED = 12;       //Red

int JOYSTICK_STEERING = A2;
int JOYSTICK_THROTTLE = A3;
int LEFT_BRAKE = A0;
int RIGHT_BRAKE = A1;

int throttleVal;
int steeringVal;
int leftBrakeVal;
int rightBrakeVal;

unsigned long previousTime;
unsigned long commTime;

void setup()
{
  Serial.begin(SERIAL_DATA_SPEED_9600_BPS);

  previousTime = millis();
  commTime = millis();

  pinMode(POWER_LED, OUTPUT);
  pinMode(COMS_GOOD_LED, OUTPUT);
  pinMode(COMS_BAD_LED, OUTPUT);

  digitalWrite(POWER_LED, HIGH);
  digitalWrite(COMS_GOOD_LED, HIGH);
  digitalWrite(COMS_BAD_LED, HIGH);
}

void loop()
{
  digitalWrite(POWER_LED, LOW);

  int throttleVal = 0;
  int steeringVal = 0;
  int leftBrakeVal = 0;
  int rightBrakeVal = 0;

  if (Serial.available() > NUMBER_OF_BYTES_IN_A_COMMAND)
  { //// When xbees are communicating
    digitalWrite(COMS_GOOD_LED, LOW);
    digitalWrite(COMS_BAD_LED, HIGH);
    Serial.read();
    commTime = millis();
  }
  else if (millis() - commTime >= MAX_TIMEOUT)
  { //// When xbees haven't received comms for 5 cycles of reads
    digitalWrite(COMS_GOOD_LED, HIGH);
    digitalWrite(COMS_BAD_LED, LOW);
  }

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
    throttleVal = map(throttleVal, 512, 1023, 40, 60);

    steeringVal = map(steeringVal, 0, 1023, 0, 100);

    leftBrakeVal = map(leftBrakeVal, 0, 1023, 0, 100);
    rightBrakeVal = map(rightBrakeVal, 0, 1023, 0, 100);

    SendNewMotorValues(throttleVal, steeringVal, leftBrakeVal, rightBrakeVal);
    previousTime = millis();
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
}
