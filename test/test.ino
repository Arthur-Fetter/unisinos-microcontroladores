#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define EN1 6
#define EN2 9

char command;

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stop();

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  analogWrite(EN1, 170);
  analogWrite(EN2, 170);

  Serial.begin(9600);
}

void stop(){  
  Serial.write("Stoping..\n");

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void moveFoward(){  
  Serial.write("Moving foward..\n");

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  delay(300);

  stop();
}

void loop(){

  if(Serial.available()){
    command = Serial.read();      
    if(command == 'f'){
      Serial.print("Read command f\n");
      moveFoward();
    }  
  }
}