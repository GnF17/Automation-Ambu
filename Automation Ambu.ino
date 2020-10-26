#include <LiquidCrystal.h>
int motor = 11;
int potenciometroPino = A0;
int estado;
float potenciometro;
float fluxo = 0;
float x = 0;
LiquidCrystal lcd(10,A1,A2,A3,A4,A5);
const int interruptor = 2;
const int buzzerPino = 8;
const int f = 349;
const int gS = 415;
const int a = 440;
const int cH = 523;
const int eH = 659;
const int fH = 698;
const int vermelho = 9;
const int azul = 6;
const int verde = 5;

void telaLcd(float x){
  lcd.setCursor(4,0);
  lcd.print("*GRUPO 1*");
  lcd.setCursor(0,1);
  lcd.print("FLUXO(%): ");
  lcd.setCursor(10,1);
  lcd.print("      ");
  lcd.setCursor(10,1);
  lcd.print(x);
  delay(250);
}

void motorFuncao(){
  potenciometro = 0;
  potenciometro = map(analogRead(potenciometroPino),0,1023,0,255);
  analogWrite(motor,potenciometro);
  fluxo = (potenciometro*100)/255;
  telaLcd(fluxo);
}

void desligado(){
	analogWrite(verde, 0);
  	analogWrite(vermelho, 255);
}

void ligado(){
  	analogWrite(vermelho, 0);
  	analogWrite(verde, 255);
}

void buzzer(){
    tone(8,eH, 500);
    tone(8,eH, 500);
    tone(8,eH, 500); 
    tone(8,fH, 350);
    tone(8,cH, 150);
    tone(8,gS, 500);
    tone(8,f, 350);
    tone(8,cH, 150);
    tone(8,a, 650);
  	delay(500);
  	noTone(8);
}

void setup(){
  lcd.begin(16,2);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  buzzer();
  analogWrite(azul, HIGH);
}

void loop(){
  estado=digitalRead(interruptor);
  if(estado==HIGH){
    ligado();
  	motorFuncao();
  }else{
    desligado();
  	delay(500);
}
}