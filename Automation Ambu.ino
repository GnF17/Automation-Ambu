//Biblioteca LCD
#include <LiquidCrystal.h>

//Pinos:
int motor = 11;
int potenciometroPino = A0;

//Variaveis de controle:
int estado;
float potenciometro;
float frequencia = 0;
float x = 0;

//Pinos:
LiquidCrystal lcd(10,A1,A2,A3,A4,A5); 
const int interruptor = 2; 
const int buzzerPino = 8; 

//Frequencia das notas musicais:
const int f = 349;
const int gS = 415;
const int a = 440;
const int cH = 523;
const int eH = 659;
const int fH = 698;

//pinos:
const int vermelho = 9;
const int azul = 6;
const int verde = 5;

void telaLcd(float x){ //Funcao LCD - x eh o valor da frequencia
  lcd.setCursor(4,0); //"Seta" a posicao do cursor na coluna 4 e linha 0
  lcd.print("*GRUPO 1*"); //Imprime o valor passado na posicao informada
  lcd.setCursor(0,1);
  lcd.print("FREQUENCIA: ");
  lcd.setCursor(10,1);
  lcd.print("      ");
  lcd.setCursor(10,1);
  lcd.print(x); //Imprime o valor da frequencia do motor
  delay(250); //Pausa a execucao do codigo por 250 milissegundos
}

void motorFuncao(){ //Funcao motor
  potenciometro = 0; //Garante que o valor lido pelo potenciometro seja inicialmente 0
  potenciometro = map(analogRead(potenciometroPino),0,1023,0,300); 
  //Mapeia o valor lido na porta do potenciometro de 0 a 1023 para 0 a 300
  analogWrite(motor,potenciometro); //"Seta" o valor lido no potenciometro na porta do motor
  frequencia = (potenciometro/3.242); //Converte o valor lido em um valor de frequencia
  telaLcd(frequencia); //Chama a funcao do LCD
}

void desligado(){ //Funcao que "desliga" o circuito
	analogWrite(verde, 0); //Configura o valor da porta verde do LED para 0
  	analogWrite(vermelho, 255); //Configura o valor da porta vermelha do LED para 255
  	analogWrite(motor,0); ///Configura a velocidade do motor pra 0
  	lcd.noDisplay(); //"Desliga" o LCD
}

void ligado(){ //Funcao que liga o LED verde
  	analogWrite(vermelho, 0); //Configura o valor da porta vermelho do LED para 0
  	analogWrite(verde, 255); //Configura o valor da porta verde do LED para 255
}

void buzzer(){ //Funcao Buzzer
  	//Funcao tone especifica do buzzer tone(porta,variavel-frequencia,tempo-milissegundos)
  	tone(8,eH, 500);
    tone(8,eH, 500);
    tone(8,eH, 500); 
    tone(8,fH, 350);
    tone(8,cH, 150);
    tone(8,gS, 500);
    tone(8,f, 350);
    tone(8,cH, 150);
    tone(8,a, 650);
  	//Pausa o codigo por 500 milissegundos
  	delay(500);
  	//Desliga o buzzer
  	noTone(8);
}

void setup(){
  lcd.begin(16,2); //Inicializa a tela LCD
  //Configura as portas como OUTPUT(saida) ou INPUT(entrada)
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  buzzer(); //Chama a funcao Buzzer
  //O valor da porta azul é configurada sempre para 0 pois nunca sera usada
  analogWrite(azul, 0); //Configura o valor da porta azul do LED para 0
}

void loop(){
  estado=digitalRead(interruptor); //Le o valor do interruptor
  if(estado==HIGH){ //Verifica se o valor lido eh HIGH (ligado)
    ligado(); //Chama a funcao ligado
  	motorFuncao(); //Chama a funcao motor
  }else{ //Se o valor lido for LOW (desligado)
    desligado(); //Chama a funcao desligado
}
}
