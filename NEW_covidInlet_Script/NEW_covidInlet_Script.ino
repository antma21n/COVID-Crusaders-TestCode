// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;
const int speedDelay = 600;

//limit switch circuit
const int botSwitchPin = 4; //orange
const int topSwitchPin = 7; //yellow

//covid input pin
const int covidInputPin = 13; //idk

//UV pin and vars-
const int ledPin = 9; //blue
const int cleanTime = 15*1000;
bool cleaned = true;

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
  //Serial.print(digitalRead(covidInputPin));
  
  //BREATHALYZER READY FOR SAMPLE
  if(digitalRead(covidInputPin) == HIGH) {
    digitalWrite(dirPin, HIGH); // Set motor direction clockwise
    if(digitalRead(botSwitchPin) == LOW) //door opened
    {
      //sample();
    } 
    else 
    {
      cleaned = false;
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
  else if(digitalRead(covidInputPin) == LOW) {    
    digitalWrite(dirPin, LOW); // Set motor direction counterclockwise
    if(digitalRead(topSwitchPin) == LOW) //door closed
    { 
      
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
  Serial.print(cleaned);
  if(cleaned == false) 
  {
    Serial.print("Closed");
    Serial.print("Cleaning");
    digitalWrite(ledPin, HIGH);   
    delay(cleanTime);              
    digitalWrite(ledPin, LOW);   
    cleaned = true;
  }
}

void sample()
{
  Serial.print("opened");
}
