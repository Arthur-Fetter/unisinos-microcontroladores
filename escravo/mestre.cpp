#define PIN_B1 2
#define PIN_B2 3
#define PIN_B3 4
#define PIN_CS1 8
#define PIN_CS2 9
#define PIN_CS3 10

int b1 = 0;
int b2 = 0;
int b3 = 0;

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
  if (digitalRead(PIN_B1)) {
    digitalWrite(PIN_CS1, HIGH);
    if (b1 == 1 && digitalRead(PIN_B1) == 0) {
      Serial.write('D');
      b1 = 0;
    } else if (b1 == 0 && digitalRead(PIN_B1) == 1) {
      Serial.write('L');
      b1 = 1;
    }
    digitalWrite(PIN_CS1, LOW);
    delay(100);
  }
  if (digitalRead(PIN_B2)) {
    digitalWrite(PIN_CS2, HIGH);
    b2 = !b2;
    if (b2 == 0) {
      Serial.write("D");
    } else {
      Serial.write("L");
    }
    digitalWrite(PIN_CS2, LOW);
  }
  if (digitalRead(PIN_B3)) {
    digitalWrite(PIN_CS3, HIGH);
    b3 = !b3;
    if (b3 == 0) {
      Serial.write("D");
    } else {
      Serial.write("L");
    }
    digitalWrite(PIN_CS3, LOW);
  }
}
