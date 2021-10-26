//Limit Switch Code

const int botSwitchPin = 4; //orange
const int topSwitchPin = 7; //yellow

//declare another pin for testing if click has been made
//const int ledPin = 9; //blue

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(botSwitchPin, INPUT);
  pinMode(topSwitchPin, INPUT);

  //pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //botRead = digitalRead(botSwitchPin);
  //topRead = digitalRead(topSwitchPin);

  if(digitalRead(botSwitchPin) == HIGH) {
    //digitalWrite(ledPin, HIGH);
    Serial.print("bot clicked");
    
  }
  if(digitalRead(topSwitchPin) == HIGH) {
    //digitalWrite(ledPin, HIGH);
    Serial.print("top clicked");
  }
}
