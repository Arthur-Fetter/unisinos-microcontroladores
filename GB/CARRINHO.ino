//Passos da maquina de estados
enum carrinho_status {
  para,
  segue_linha,
  gira_esquerda,
  gira_direita,
  retorna,
};

enum sentido {
  esquerda,
  direita,
  frente,
  tras
};

//Pinos
#define LED_DEBUG 13
#define IR_CONTADOR_LINHA 3
#define IR_OBSTACULO 2
#define IR_SEGUIDOR_DIREITO 11
#define IR_SEGUIDOR_ESQUERDO 12
#define PWM_MOTOR_DIREITO 10
#define PWM_MOTOR_ESQUERDO 6
#define MOTOR_DIREITO_IN_0 8
#define MOTOR_DIREITO_IN_1 7
#define MOTOR_ESQUERDO_IN_0 13
#define MOTOR_ESQUERDO_IN_1 9

//Variaveis globais
//enum carrinho_status carrinho_passo = para;
enum carrinho_status carrinho_passo = segue_linha;
int iCount = 0;
int isObstaculo = 0;
char command;
char buffer[80]; //variável utilizada para printar no serial

void setup()
{
  Serial.begin(9600);

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
  // attachInterrupt(digitalPinToInterrupt(IR_OBSTACULO), obstaculo, CHANGE);  
  attachInterrupt(digitalPinToInterrupt(IR_CONTADOR_LINHA), contador_linha, CHANGE);

  analogWrite(PWM_MOTOR_ESQUERDO, 95);
  analogWrite(PWM_MOTOR_DIREITO, 100);
}

void loop()
{      
  buffer[0] = digitalRead(LED_DEBUG) ? 'L' : ' ';  
  buffer[1] = digitalRead(IR_OBSTACULO) ? 'O' : ' ';
  buffer[2] = digitalRead(IR_SEGUIDOR_DIREITO) ? 'D' : ' ';
  buffer[3] = digitalRead(IR_SEGUIDOR_ESQUERDO) ? 'E' : ' ';
  buffer[4] = digitalRead(IR_CONTADOR_LINHA) ? 'C' : ' ';
  buffer[5] = ' ';
  buffer[6] =' ';
  //buffer[5] = digitalRead(PWM_MOTOR_DIREITO) ? 'P' : ' ';
  //buffer[6] = digitalRead(PWM_MOTOR_ESQUERDO) ? 'Q' : ' ';
  buffer[7] = digitalRead(MOTOR_ESQUERDO_IN_0) ? '1' : ' ';
  buffer[8] = digitalRead(MOTOR_ESQUERDO_IN_1) ? '2' : ' ';
  buffer[9] = digitalRead(MOTOR_DIREITO_IN_0) ? '3' : ' ';
  buffer[10] = digitalRead(MOTOR_DIREITO_IN_1) ? '4' : ' ';
  buffer[11] = '|',
  buffer[12] = '\0';
  
  // Serial.print(buffer);
  
  /*
   * s -> segue_linha
   * g -> gira esquerda
   * h -> gira direita
   * p -> para
   * c -> contador de linha
   * o -> contador de linha
   * r -> retorna
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
    }else if(command == 'r'){
      carrinho_passo = retorna;
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
    case retorna:
      retornar();
      break;
  }
}

void gira_motor_esquerdo(enum sentido sentido_motor){
  if(sentido_motor == frente){ 
    analogWrite(PWM_MOTOR_ESQUERDO, 250);    
    digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_1, HIGH);        
    delay(30);
    analogWrite(PWM_MOTOR_ESQUERDO, 120);    
  }else if(sentido_motor == tras){    
    analogWrite(PWM_MOTOR_ESQUERDO, 250);    
    digitalWrite(MOTOR_ESQUERDO_IN_0, HIGH);
    digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);    
    delay(30);
    analogWrite(PWM_MOTOR_ESQUERDO, 120);    
  }else{    
    digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
    digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);
  }
}

void gira_motor_direito(enum sentido sentido_motor){
  if(sentido_motor == frente){ 
    analogWrite(PWM_MOTOR_DIREITO, 250);    
    digitalWrite(MOTOR_DIREITO_IN_0, LOW);
    digitalWrite(MOTOR_DIREITO_IN_1, HIGH);        
    delay(30);
    analogWrite(PWM_MOTOR_DIREITO, 120);    
  }else if(sentido_motor == tras){    
    analogWrite(PWM_MOTOR_DIREITO, 250);   
    digitalWrite(MOTOR_DIREITO_IN_0, HIGH);
    digitalWrite(MOTOR_DIREITO_IN_1, LOW);
    delay(30);
    analogWrite(PWM_MOTOR_DIREITO, 120);    
  }else{    
    digitalWrite(MOTOR_DIREITO_IN_0, LOW);
    digitalWrite(MOTOR_DIREITO_IN_1, LOW);
  }
}

void seguidor_de_linha() {
  // Serial.print("Seguindo linha\n"); 

  if(digitalRead(IR_SEGUIDOR_ESQUERDO) && digitalRead(IR_SEGUIDOR_DIREITO)){
    Serial.print("encontrou linha ortogonal com o sensor posterior\n");     
    gira_motor_esquerdo(frente);
    gira_motor_direito(frente);
    delay(50);
  }else if(digitalRead(IR_SEGUIDOR_DIREITO)){
    Serial.print("alinhando para a direita\n");
    
    gira_motor_esquerdo(frente);
    gira_motor_direito(tras);
    delay(10);
  }else if(digitalRead(IR_SEGUIDOR_ESQUERDO)){ 
    Serial.print("alinhando para a esquerda\n");  
    gira_motor_esquerdo(tras);
    gira_motor_direito(frente);
    delay(10);
  }else{     
    gira_motor_esquerdo(frente);
    gira_motor_direito(frente);
  }
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
    gira_motor_esquerdo(tras);
    gira_motor_direito(frente);

    delay(600);
 
    Serial.print("Fez curva, passo segue_linha\n");
  }else{
    Serial.print("Fazendo curva direita\n");
          
    gira_motor_esquerdo(frente);
    gira_motor_direito(tras);

    delay(600);

    Serial.print("Fez curva, passo segue_linha\n");
  }

  carrinho_passo = para;

  parar();  
  //carrinho_passo = segue_linha;
}

void parar(){
  Serial.print("Parando\n");
    
  gira_motor_esquerdo(0);
  gira_motor_direito(0);
}

void retornar() {
  // fazer um tempo mínimo para girar mais que 90 graus, depois girar até achar a linha no sensor (não é feito da segunda forma direto para evitar ler a linha à 90 graus no sensor, se houver)
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
void contador_linha() {
  Serial.print("ENCONTROU LINHA!!!!!!");
  if(digitalRead(IR_CONTADOR_LINHA)){
    contContadorLinha++;
    
    sprintf(buffer, "Contou linha, iCount: %d\n", iCount);
    Serial.print(buffer);
    
    iCount++;
    if (iCount == 3) {
      sprintf(buffer, "Passo gira, iCount: %d\n", iCount);
      Serial.print(buffer);
      carrinho_passo = gira_esquerda;
      iCount = 0;
    }
  } else {
    contContadorLinha = 0;
  }
  delay(100);
}

int contObstaculo = 0;
void obstaculo() {
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
