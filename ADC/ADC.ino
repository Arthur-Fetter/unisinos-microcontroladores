#define FAIXA1      40
#define FAIXA2      80
#define ADC_BOTTOM  25
#define ADC_TOP     980
#define LED_PIN     13
#define LED_DELAY   200

void setup() {
  pinMode(A0, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(A0);
  int leitura_map = map(leitura, ADC_BOTTOM, ADC_TOP, 0, 100);
  Serial.println(leitura_map);

  if (leitura_map < FAIXA1) {
    digitalWrite(LED_PIN, LOW);
  } else if (leitura_map > FAIXA1 && leitura_map < FAIXA2) {
    digitalWrite(LED_PIN, HIGH);
  } else if (leitura_map > FAIXA2) {
    digitalWrite(LED_PIN, HIGH);
    delay(LED_DELAY);
    digitalWrite(LED_PIN, LOW);
    delay(LED_DELAY);
  }
}