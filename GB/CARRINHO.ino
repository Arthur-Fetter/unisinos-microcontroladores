//Passos da maquina de estados
enum carrinho_status{
  parado,
  segue_linha,
  gira
}

enum carrinho_status carrinho_passo = parado;

/*  CÓDIGO DO PROFESSOR

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

*/

//Pinos
#define LED_DEBUG 13
#define IR_CONTADOR_LINHA 8
#define IR_OBSTACULO 7
#define IR_SEGUIDOR_DIREITO 11
#define IR_SEGUIDOR_ESQUERDO 12
#define PWM_MOTOR_DIREITO 6
#define PWM_MOTOR_ESQUERDO 9
#define MOTOR_DIREITO_IN_0 2
#define MOTOR_DIREITO_IN_1 3
#define MOTOR_ESQUERDO_IN_0 4
#define MOTOR_ESQUERDO_IN_1 5

//Variaveis globais
int passo = SEGUIR_LINHA;
int iCount = 0;
int isObstaculo = 0;

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
  attachInterrupt(digitalPinToInterrupt(IR_CONTADOR_LINHA), contador_linha, RISING);
}

void loop()
{
  switch(carrinho_passo)
  {
    case segue_linha:
      seguidor_de_linha();
      break;
    case gira:
      realizar_a_curva();
      break;
    case parado:
      parar();
      break;
  }
}

/*
* todo
*/
void seguidor_de_linha(){
  
}

/*
* todo
*/
void realizar_a_curva()
{
  //Fazer a curva
  carrinho_passo = segue_linha
}

void parar()
{
  analogWrite(PWM_MOTOR_DIREITO, 0);
  analogWrite(PWM_MOTOR_ESQUERDO, 0);
  
  digitalWrite(MOTOR_DIREITO_IN_0, LOW);
  digitalWrite(MOTOR_DIREITO_IN_1, LOW);
  digitalWrite(MOTOR_ESQUERDO_IN_0, LOW);
  digitalWrite(MOTOR_ESQUERDO_IN_1, LOW);
}

void contador_linha()
{
  iCount++;
  
  if(iCount == 3){
    carrinho_passo = gira;
    iCount = 0;
  }
}

void obstaculo()
{
  isObstaculo =! isObstaculo;
  
  if(isObstaculo)
    carrinho_passo = parado;
  else
    carrinho_passo = segue_linha;
}