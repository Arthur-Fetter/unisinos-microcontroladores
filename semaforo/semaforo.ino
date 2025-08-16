#define VERMELHO 3
#define AMARELO 4
#define VERDE 5
#define BOTAO 6

bool estadoBotao = true;

void setup() {
  //inicializa o estado dos pinos
  pinMode(VERMELHO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(VERDE, OUTPUT);  
  pinMode(BOTAO, INPUT);

  //inicializa o valor dos pinos
  digitalWrite(VERDE, HIGH);
  digitalWrite(AMARELO, LOW);
  digitalWrite(VERMELHO, LOW);

  Serial.begin(9600);
}

void fechaSinaleira(){
  digitalWrite(VERDE, LOW);
  digitalWrite(AMARELO, HIGH);

  delay(2000);
  digitalWrite(AMARELO, LOW);
  digitalWrite(VERMELHO, HIGH);

  delay(4000);
  digitalWrite(VERMELHO, LOW);
  digitalWrite(VERDE, HIGH);

}

void loop() {
  estadoBotao = digitalRead(BOTAO);

  if(estadoBotao){
    fechaSinaleira();
  }
}