// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 200;
bool clean = false;

//limit switch circuit
const int botSwitchPin = 4; //orange
const int topSwitchPin = 7; //yellow

//covid input pin
const int covidInputPin = 12; //idk

void setup()
{
  // Declare pins as Outputs
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
  clean = false;
  
  //BREATHALYZER READY FOR SAMPLE
  if(digitalRead(covidInputPin) == LOW) {
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
    //Serial.print("Opening");

    if(digitalRead(botSwitchPin) == LOW) 
    { //door open
      Serial.print("Opened");
    } 
    else 
    {
      for(int x = 0; x < stepsPerRevolution; x++)
      {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
      }
    }
  }

  //BREATHALYZER PROCESSING SAMPLE
  if(digitalRead(covidInputPin) == HIGH) {
  
    //Serial.print("Closing");
    
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
  
    // Spin motor quickly
    if(digitalRead(topSwitchPin) == LOW) //door closed
    { 
      Serial.print("Closed");
      clean = true;
    } 
    else 
    {
      for(int x = 0; x < stepsPerRevolution; x++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
    }
    

    if(clean == true) {
      Serial.print("Cleaning");

      delay(3000);
      //clean system
      //this should not keep running constantly if door stays closed should only run one time. 
      
    }
  
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
  }
}
