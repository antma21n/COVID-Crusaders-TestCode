//stepper motor circuit
const int dirPin = 2; //blue
const int stepPin = 3; //green
const int stepsPerRevolution = 200;

//LED circuit
const int ledPin = 9; //blue again 
const int cureTime = 500; //1000 * 60

//limit switch circuit
const int botSwitchPin = 4; //orange
const int topSwitchPin = 7; //yellow

//covid input pin
const int covidInputPin = 12; //idk

void setup() {
  // put your setup code here, to run once:
  pinMode(botSwitchPin, INPUT);
  pinMode(topSwitchPin, INPUT);
  pinMode(covidInputPin, INPUT);

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  //start spinning motor to know code started
  digitalWrite(stepPin, HIGH); //turn on motor

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //door is closed and clicks limit switch
  if(digitalRead(botSwitchPin) == LOW) {
    Serial.print("Bottom Clicked Orange ");
    
    digitalWrite(dirPin, HIGH); //swap stepper dir
    digitalWrite(stepPin, LOW); //turn off motor
    
    delayMicroseconds(1000); //delay for 2sec
    digitalWrite(ledPin, HIGH); //turn on UV
    delayMicroseconds(cureTime); //leave on for 60sec

    digitalWrite(stepPin, HIGH); //turn on motor
    }

  //door is open and clicks limit switch
  if(digitalRead(topSwitchPin) == LOW) {
    
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);

    //wait for breathlyzer to accept breath and send signal to close
    if(digitalRead(covidInputPin) == HIGH) {
      digitalWrite(stepPin, HIGH); 
      delayMicroseconds(1000); //delay for 2sec to make sure door opens enough so if statement is not triggered again 
      }
    }
}
