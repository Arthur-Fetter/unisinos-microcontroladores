//Passos da maquina de estados
enum carrinho_status {
  para,
  segue_linha,
  gira_esquerda,
  gira_direita,
  retornar,
};

enum sentido {
  esquerda,
  direita
};

//Pinos
#define LED_DEBUG 13
#define IR_CONTADOR_LINHA 3
#define IR_OBSTACULO 2
#define IR_SEGUIDOR_DIREITO 11
#define IR_SEGUIDOR_ESQUERDO 12
#define PWM_MOTOR_DIREITO 5
#define PWM_MOTOR_ESQUERDO 6
#define MOTOR_DIREITO_IN_0 8
#define MOTOR_DIREITO_IN_1 7
#define MOTOR_ESQUERDO_IN_0 10
#define MOTOR_ESQUERDO_IN_1 9

//Variaveis globais
enum carrinho_status carrinho_passo = segue_linha;
int iCount = 0;
int isObstaculo = 0;
char command;
char buffer[80]; //variável utilizada para printar no serial

void setup()
{
  //Configuração dos pinos
  pinMode(LED_DEBUG, OUTPUT);
  pinMode(IR_CONTADOR_LINHA, INPUT);
  pinMode(IR_OBSTACULO, INPUT);
  pinMode(IR_SEGUIDOR_DIREITO, INPUT);
  pinMode(IR_SEGUIDOR_ESQUERDO, INPUT);
  pinMode(PWM_MOTOR_DIREITO, OUTPUT);
  pinMode(PWM_MOTOR_ESQUERDO, OUTPUT);
  pinMode(MOTOR_DIREITO_IN_0, OUTPUT);
  pinMode(MOTOR_DIREITO_IN_1, OUTPUT);
  pinMode(MOTOR_ESQUERDO_IN_0, OUTPUT);
  pinMode(MOTOR_ESQUERDO_IN_1, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(IR_OBSTACULO), obstaculo, CHANGE);  
  //attachInterrupt(digitalPinToInterrupt(IR_CONTADOR_LINHA), contador_linha, RISING);

  Serial.begin(9600);
}

void loop()
{    
  
  buffer[0] = digitalRead(LED_DEBUG) ? 'L' : ' ';  
  buffer[1] = digitalRead(IR_OBSTACULO) ? 'O' : ' ';
  buffer[2] = digitalRead(IR_SEGUIDOR_DIREITO) ? 'D' : ' ';
  buffer[3] = digitalRead(IR_SEGUIDOR_ESQUERDO) ? 'E' : ' ';
  buffer[4] = digitalRead(PWM_MOTOR_DIREITO) ? 'P' : ' ';
  buffer[5] = digitalRead(PWM_MOTOR_ESQUERDO) ? 'Q' : ' ';
  buffer[6] = digitalRead(MOTOR_ESQUERDO_IN_0) ? '1' : ' ';
  buffer[7] = digitalRead(MOTOR_ESQUERDO_IN_1) ? '2' : ' ';
  buffer[8] = digitalRead(MOTOR_DIREITO_IN_0) ? '3' : ' ';
  buffer[9] = digitalRead(MOTOR_DIREITO_IN_1) ? '4' : ' ';
  buffer[10] = '|',
  buffer[11] = '\0';
  
  Serial.print(buffer);
  
  /*
   * s -> segue_linha
   * g -> gira esquerda
   * h -> gira direita
   * p -> para
   * c -> contador de linha
   * o -> contador de linha
   */
  if(Serial.available()){
    command = Serial.read();   
    sprintf(buffer,"Leu comando: %c\n", command);  
    Serial.print(buffer);
    if(command == 's'){
      carrinho_passo = segue_linha;
    }else if(command == 'g'){
      carrinho_passo = gira_esquerda;
    }else if(command == 'h'){
      carrinho_passo = gira_direita;
    }else if(command == 'p'){
      carrinho_passo = para;
    }else if(command == 'c'){
      contador_linha();
    }else if(command == 'o'){
      obstaculo();
    }
  }
  
  switch (carrinho_passo)
  {
    case segue_linha:
      seguidor_de_linha();
      break;
    case gira_esquerda:
      faz_curva(esquerda);
      break;
    case gira_direita:
      faz_curva(direita);
      break;
    case para:
      parar();
      break;
    case retornar:
      retornar();
      break;
  }
}

void seguidor_de_linha() {
  Serial.print("Seguindo linha\n"); 

  /*if(digitalRead(IR_SEGUIDOR_DIREITO)){
    Serial.print("alinhando para a esquerda\n"); 
    digitalWrite(MOTOR_DIREITO_IN_0, HIGH);
    digitalWrite(MOTOR_DIREITO_IN_1, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_1, HIGH);
    delay(100);
  }else if(digitalRead(IR_SEGUIDOR_ESQUERDO)){ 
    Serial.print("alinhando para a direita\n"); 
    digitalWrite(MOTOR_DIREITO_IN_0, LOW);
    digitalWrite(MOTOR_DIREITO_IN_1, HIGH);
    digitalWrite(MOTOR_ESQUERDO_IN_0, HIGH);
    digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);
    delay(100);
  }*/
  
  digitalWrite(MOTOR_DIREITO_IN_0, LOW);
  digitalWrite(MOTOR_DIREITO_IN_1, HIGH);
  digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
  digitalWrite(MOTOR_ESQUERDO_IN_1, HIGH);
}

void faz_curva(enum sentido curva_sentido){
  if(curva_sentido == esquerda){
    Serial.print("Fazendo curva esquerda\n");
    
    // Comando de curva deve estar demarcado por uma lógica para realizar a curva
    // int linha_lateral = false;
    // int linha_frontal = false;
    // while (!(linha_lateral && linha_frontal)) {
    //    if (digialRead(IR_CONTADOR_LINHA)) {
    //      linha_lateral = true;
    //    }
    //    if (digitalRead(IR_SEGUIDOR_DREITO)) {
    //      linha_frontal = true;
    //    }
    //    digitalWires
    // }
    digitalWrite(MOTOR_DIREITO_IN_0, LOW);
    digitalWrite(MOTOR_DIREITO_IN_1, HIGH);
    digitalWrite(MOTOR_ESQUERDO_IN_0, HIGH);
    digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);

    delay(1000);
 
    Serial.print("Fez curva, passo segue_linha\n");
  }else{
    Serial.print("Fazendo curva direita\n");
      
    digitalWrite(MOTOR_DIREITO_IN_0, HIGH);
    digitalWrite(MOTOR_DIREITO_IN_1, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_1, HIGH);

    delay(1000);

    Serial.print("Fez curva, passo segue_linha\n");
  }

  parar();

  carrinho_passo = segue_linha;
}

void parar(){
  Serial.print("Parando\n");
  
  analogWrite(PWM_MOTOR_DIREITO, 0);
  analogWrite(PWM_MOTOR_ESQUERDO, 0);

  digitalWrite(MOTOR_DIREITO_IN_0, LOW);
  digitalWrite(MOTOR_DIREITO_IN_1, LOW);
  digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
  digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);
}

void retornar() {
  // faz_curva(esquerda);
  // segue_linha_tile(1);
  // faz_curva(direita);
  // segue_linha_tile(1);
  // faz_curva(direita);
  // segue_linha_tile(1);
  // faz_curva(esquerda);
  carrinho_passo = segue_linha;
}

int contContadorLinha = 0;
void contador_linha(){
  if(!contContadorLinha){
    contContadorLinha++;
    
    sprintf(buffer, "Contou linha, iCount: %d\n", iCount);
    Serial.print(buffer);
    
    iCount++;
    if (iCount == 3) {
      sprintf(buffer, "Passo gira, iCount: %d\n", iCount);
      Serial.print(buffer);
      carrinho_passo = gira_direita;
      iCount = 0;
    }
  }else{
    contContadorLinha = 0;
  }
}

int contObstaculo = 0;
void obstaculo(){
  if(!contObstaculo){
    contObstaculo++;
    isObstaculo = ! isObstaculo;
    
    sprintf(buffer, "encontrou obstaculo, isObstaculo depois de inverter: %d\n", isObstaculo);
    Serial.print(buffer);

    if (isObstaculo){
      Serial.print("Passo parado\n");
      carrinho_passo = para;
    }else{
      Serial.print("Passo segue_linha\n");
      carrinho_passo = segue_linha;
    }
  }else{
    contObstaculo = 0;
  }
}
