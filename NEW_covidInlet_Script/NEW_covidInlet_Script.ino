// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;
const int speedDelay = 375;

//limit switch circuit
const int botSwitchPin = 4; //orange
const int topSwitchPin = 7; //yellow

//covid input pin
const int covidInputPin = 12; //idk

//UV pin and vars
const int ledPin = 9; //blue
const int cleanTime = 15*1000;
bool cleaned = false;

void setup()
{
  // Declare pins as Outputs
  pinMode(ledPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);

  //Declare pins as Inputs
  pinMode(botSwitchPin, INPUT);
  pinMode(topSwitchPin, INPUT);
  pinMode(covidInputPin, INPUT);
}

//use this loop function in main code to improve spinning.
void loop()
{
  
  //BREATHALYZER READY FOR SAMPLE
  if(digitalRead(covidInputPin) == LOW) {
    cleaned = false;
    digitalWrite(dirPin, HIGH); // Set motor direction clockwise
    if(digitalRead(botSwitchPin) == LOW) //door opened
    {
      Serial.print("Opened");
    } 
    else 
    {
      for(int x = 0; x < stepsPerRevolution; x++)
      {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(speedDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(speedDelay);
      }
    }
  }

  //BREATHALYZER PROCESSING SAMPLE
  if(digitalRead(covidInputPin) == HIGH) {    
    digitalWrite(dirPin, LOW); // Set motor direction counterclockwise
    if(digitalRead(topSwitchPin) == LOW) //door closed
    { 
      Serial.print("Closed");
      clean();
    } 
    else 
    {
      for(int x = 0; x < stepsPerRevolution; x++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speedDelay);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speedDelay);
      }
    }
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
  }
}

void clean()
{
  if(cleaned == true) 
  {
    Serial.print("Cleaning");
    digitalWrite(ledPin, HIGH);   
    delay(cleanTime);              
    digitalWrite(ledPin, LOW);   
    cleaned = true;
  }
}
