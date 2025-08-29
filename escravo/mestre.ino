#define PIN_B1 2
#define PIN_B2 3
#define PIN_B3 4
#define PIN_CS1 8
#define PIN_CS2 9
#define PIN_CS3 10

bool b1 = false;
bool b2 = false;
bool b3 = false;

bool flagB1 = false;
bool flagB2 = false;
bool flagB3 = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_B1, INPUT);
  pinMode(PIN_B2, INPUT);
  pinMode(PIN_B3, INPUT);

  pinMode(PIN_CS1, OUTPUT);
  pinMode(PIN_CS2, OUTPUT);
  pinMode(PIN_CS3, OUTPUT);
}

void loop() {
  if(digitalRead(PIN_B1)){
    if(!flagB1){
      digitalWrite(PIN_CS1, HIGH);
      
      if(b1){    
        Serial.write('D');
        b1 = false;
      }else{
        Serial.write('L');
        b1 = true;
      }
      
      delay(100);
      digitalWrite(PIN_CS1, LOW);
      flagB1 = true;
    }
  }else if(flagB1){
    flagB1 = false;
    delay(100);
  }

  if(digitalRead(PIN_B2)){
    if(!flagB2){
      digitalWrite(PIN_CS2, HIGH);
      
      if(b2){    
        Serial.write('D');
        b2 = false;
      }else{
        Serial.write('L');
        b2 = true;
      }
      
      delay(100);
      digitalWrite(PIN_CS2, LOW);
      flagB2 = true;
    }
  }else if(flagB2){
    flagB2 = false;
    delay(100);
  }

  if(digitalRead(PIN_B3)){
    if(!flagB3){
      digitalWrite(PIN_CS3, HIGH);
      
      if(b3){    
        Serial.write('D');
        b3 = false;
      }else{
        Serial.write('L');
        b3 = true;
      }
      
      delay(100);
      digitalWrite(PIN_CS3, LOW);
      flagB3 = true;
    }
  }else if(flagB3){
    flagB3 = false;
    delay(100);
  }
}
