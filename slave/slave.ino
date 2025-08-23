#define LED 13  //led da placa
#define CS 3    //pino counter strike


char comando = 'D'; //comando ligado e desligado
void setup() {
  Serial.begin(9600); //inicia o serial

  pinMode(LED, OUTPUT); //inicia o pino do LED como saída
  pinMode(CS, INPUT);    //inicia o pino do counter strike como entrada

  digitalWrite(LED, HIGH);  //inicializa o LED como desligado
}

void loop() {
  if(digitalRead(CS) && Serial.available()){ //se o slave está selecionado e já recebeu o Serial
    comando = Serial.read();  //lê o comando e passa para o pino counter strike

    if(comando == 'D')          //se comando desliga
      digitalWrite(LED, LOW);   //liga o LED
    else if(comando == 'L')        //se comando liga
      digitalWrite(LED, HIGH);  //desliga o LED
  }  
}
