#include <AFMotor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#define pHpin A1
#define turbidityPin A2

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

String robotDirection, action;
int Speeed = 255;
float calibration_value = 21.34 - 0.7;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;

float ph_act;

void setup()
{
  sensors.begin();  // Start up the temperature library
  Serial.begin(115200);  //Set the baud rate to your ESP module.
  Serial.println("Water purity Robot");
}

void loop() {
  Serial.println("Waiting for next command");
    while (Serial.available() > 0) {
    action = getCommands();
    Serial.println("Command :" + action);
    if (action == "Move") {
      Serial.print("Starting robot ");
      moveRobot();
    }
    else if (strcmp(action.c_str(), "Measure") == 0)  {
      Serial.println("Checking Quality");
      while(action != "Abort"){
      measurePH();
      measureTurbidity();
      measureTemperature();
      action = getCommands();
      }
    }
    }
   delay(1000);
}

String getCommands() {
  if (Serial.available() > 0) {
    String receivedString = ""; // Create a string variable to store received data
    while (Serial.available() > 0) {
      char incomingChar = Serial.read(); // Read a character
      if (incomingChar == '\n' || incomingChar == '\r') {
        // If newline or carriage return is encountered, break the loop
        break;
      }
      receivedString += incomingChar; // Append the received character to the string
    }
    return receivedString;
  }
  else {
    return "SerialNotAvailable";
  }
}

void moveRobot() {
  Serial.println("Ready To Control");
  while(1)  {
     Serial.println("Looking for Direction Command ");
    delay(1000);
    if(Serial.available()>0){
       robotDirection = getCommands();
       Serial.println("Direction Command :" + robotDirection);
    Stop(); //initialize with motors stoped

    if (robotDirection == "F") {
      Serial.println("Moving Forward");
      forward();
    }

    if (robotDirection == "B") {
      Serial.println("Moving Backward");
      back();
    }

    if (robotDirection == "L") {
      Serial.println("Moving Left");
      left();
    }

    if (robotDirection == "R") {
      Serial.println("Moving Right");
      right();
    }
    if (robotDirection == "I") {
      Serial.println("Moving TopRight");
      topright();
    }

    if (robotDirection == "J") {
      Serial.println("Moving TopLeft");
      topleft();
    }

    if (robotDirection == "K") {
      Serial.println("Moving BottomRight");
      bottomright();
    }

    if (sobotDirection."== M") {
      Serial.println("Moving BottomLeft");
      bottomleft();
    }
    if (robotDirection == "T") {
      Serial.println("Stopped");
      Stop();
    }
    if (robotDirection == "Exit"){
       Serial.println("Exiting Moving");
      break;
    }
    }
  }
}

void forward()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void left()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

void right()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void topleft() {
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void topright()
{
  motor1.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

void bottomleft()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void bottomright()
{
  motor1.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed / 3.1); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}


void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}


void measurePH() {
  //ph
  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(pHpin);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  { 
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  ph_act = -5.70 * volt + calibration_value;

  Serial.println("pH Val: ");
  Serial.print(ph_act);
  delay(1000);

  //phEnd
}

void measureTurbidity() {
  //turbidity
  int turbidityValue = analogRead(turbidityPin);
  //  Serial.println(turbidityValue);
  int turbidity = map(turbidityValue, 0, 750, 100, 0);
  delay(100);
  //  lcd.setCursor(0, 0);
  //  lcd.print("Turbidity:");
  //  lcd.print("   ");
  //  lcd.setCursor(10, 0);
  //  lcd.print(turbidity);
  delay(100);
  if (turbidity < 20) {
    //    lcd.setCursor(0, 1);
    //    lcd.print(" its CLEAR ");
    Serial.print(" its CLEAR ");
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    //    lcd.setCursor(0, 1);
    //    lcd.print(" its CLOUDY ");
    Serial.print(" its CLOUDY ");
  }
  if (turbidity > 50) {
    //    lcd.setCursor(0, 1);
    //    lcd.print(" its DIRTY ");
    Serial.print(" its DIRTY ");
  }

  //turbidityEnd
}

void measureTemperature() {
  // Send the command to get temperatures
  sensors.requestTemperatures();

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
  delay(500);


  //temperatureEnd
}
