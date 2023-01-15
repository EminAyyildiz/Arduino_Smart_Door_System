#include <Keypad.h> 
#include<Servo.h>  
#include <Wire.h> 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);
int t=3000;
Servo servo;
const byte Satir= 4;  
const byte Sutun= 4;  
String Sifre;  
int led_red = 11;
int led_green = 12;
int buzzer = 13;


char key[Satir][Sutun]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte SatirPinleri[Satir] = {9,8,7,6}; 
byte SutunPinleri[Sutun]= {5,4,3,2}; 

Keypad TusTakimi= Keypad(makeKeymap(key), SatirPinleri, SutunPinleri, Satir, Sutun);
void setup()
{
  Serial.begin(9600);
  pinMode(led_red,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(buzzer,OUTPUT);
  servo.attach(10);
  servo.write(30);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("...WELCOME...");} 
  

void loop()
{ 

  char basilanTus = TusTakimi.getKey();
  if (basilanTus != NO_KEY) {

  Sifre = Sifre + basilanTus;
  lcd.setCursor(0,0);
  
  lcd.print("...Password...");
  lcd.setCursor(0,1);
  lcd.print(Sifre);
  
  Serial.println("Password :" + Sifre );}
  if (basilanTus == 'D'){
    Sifre = Sifre.substring(0, Sifre.length() - 2);
    Serial.println("Password:" + Sifre );
    lcd.clear();
     delay(100);
    lcd.setCursor(0,0);
  
    lcd.print("...Password...");
    lcd.setCursor(0,1);
   
    lcd.print(Sifre);}
  	if (Sifre == "*4321#"){
      digitalWrite(led_red, LOW);
      digitalWrite(led_green, HIGH);
      servo.write(175);
      tone(buzzer,250);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("...WELCOME...");
      lcd.setCursor(0,1);
      lcd.print("....OPENED....");
      delay(3000);
      noTone(buzzer);
      digitalWrite(led_green, LOW);
      Sifre = "" ;
      lcd.clear();
      lcd.print("...WELCOME...");}
     
   else{
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, LOW);
      servo.write(30);

   }    
}