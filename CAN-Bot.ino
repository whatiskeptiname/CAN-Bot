#include <Servo.h> // Servo library

#define mA1 12   // A motor
#define mA2 11
#define mB1 10   // B motor
#define mB2 9
#define  trigPin 8 // trigger pin for ultrasonic sensor
#define  echoPin 7 // echo pin for ultrasonic sensor

Servo servohand; // servo for hand of the bot
Servo servohead; // servo for head of the bot
long int dist, duration; // distance and duration variables for ultrasonic sensor
char input; // input variable for serial communication

void sensor_check() // function to get data from sensors and serial communication
{
  // get the proximity value from the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  dist = (duration / 2) / 29.1;

  //read tx inputa
  if (Serial1.available() > 0) input = Serial1.read();

  Serial1.print(dist);
  Serial1.print(" cm ");
  Serial1.print("data: ");
  Serial1.print(input);
  Serial1.println();
}

void setup()
{
  // initializing the pins 
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);

  servohand.attach(6); // attach bot hand servo to pin 6
  servohead.attach(5); // attach bot head servo to pin 5 
  
  servohand.write(90); // default servo position
  servohead.write(90);
  Serial1.begin(115200); // initialize serial communication at 115200 baud
}

void left() // move the bot left
{
  Serial.println("Left");
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void right() // move the bot right
{
  Serial.println("Right");
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void backward() // move the bot backward
{
  Serial.println("Backward");
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
}
void forward() // move the bot forward
{
  Serial.println("Forward");
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
}
void wait() // stop the bot from moving 
{
  Serial.println("Wait");
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
}

void loop() // main loop
{
  sensor_check();

  if (dist>=10 && dist <= 20) // wave hand if the proximity is between 10 and 20 cm
  {
    wait(); // stop the moving bot
    // wave bot hand
    servohand.write(140);
    delay(200);
    servohand.write(40);
    delay(200);
    servohand.write(90);
  }
  else if (dist <= 10) // nod head
  {
    wait();
    servohead.write(0);
    delay(100);
    servohead.write(180);
    delay(100);
    servohead.write(90);
  }
  else
  {
    sensor_check(); // check the distance and serial data

    switch (input) // move the bot according to the input from the serial communication
    {
      case 'S':
        wait();
        break;
      case 'F':
        forward();
        break;
      case 'R':
        right();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'X':
        servohand.write(140);
        break;
      case 'x':
        servohand.write(90);
        break;
      case 'V':
        servohead.write(140);
        break;
      case 'v':
        servohead.write(90);
        break;
      deafult:
        wait();
        break;
    }
  }
}
