//Last Minute Engineers Test Code

// Define pin connections & motor's steps per revolution
const int dirPin = 2;
const int stepPin = 3;
const int stepsPerRevolution = 500;
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
  //BREATHALYZER READY FOR SAMPLE
  if(digitalRead(covidInputPin) == LOW) {
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
    Serial.print("Opening");

    if(digitalRead(botSwitchPin) == HIGH) 
    { //door open
      Serial.print("Opened");
    } 
    else 
    {
      for(int x = 0; x < stepsPerRevolution; x++)
      {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
      }
    }
  }

  //BREATHALYZER PROCESSING SAMPLE
  if(digitalRead(covidInputPin) == HIGH) {
  
    delay(1000); // Wait a second
    Serial.print("Closing");
    
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
  
    // Spin motor quickly
    for(int x = 0; x < stepsPerRevolution; x++)
    {
      if(digitalRead(topSwitchPin) == HIGH) { //door closed
        x = stepsPerRevolution;
        clean = true;
      } else {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
      }
    }
    delay(1000); // Wait a second

    if(clean == true) {
      Serial.print("Cleaning");
      //clean system
    }
  
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
  }
}
