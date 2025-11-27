
/* - WellSERVICE -
 *  PROYECTO: "Ctrl valvula proporcional hidraulica con regulador lineal lm317 por medio de una señal pwm"
 *  DISEÑADO POR: prof.martintorres@educ.ar
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  


int Valvula1 = 11;
int dirPin1 = 4;
int dirPin2 = 7 ;
int yPin = A1;

int yVal;
int APERTURA;
int compAPERTURA;
int APERTURA2;
int dt = 100;
int dt2 = 5000;


void setup() {
  Serial.begin(9600);
  pinMode(Valvula1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(yPin, INPUT);
   digitalWrite(dirPin1, 1);
   digitalWrite(dirPin2, 1);
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print ("  Well Service  ");
lcd.setCursor(0,1);
lcd.print ("-Tool & Testing-");
delay (1500);
lcd.clear();
}

void loop() {
  yVal = analogRead(yPin);
  Serial.println( "Lectura PUERTO: " );
  Serial.println(yVal);
 lcd.setCursor(0,0);
 lcd.print ("POSICION   L:");
 lcd.print (yVal);
 lcd.setCursor(0,1);
 
 if (yVal > 421 & yVal <430) {
   APERTURA2 = map(yVal,0,0,0,0);  
lcd.print ("-SIN GIRO- ");  
lcd.print (APERTURA2); 
     }

if (yVal < 420) {
 APERTURA2 = map(yVal,1023,420,0,255);  
lcd.print ("GIRO DER.: ");
lcd.print (APERTURA2); 
delay (150);
lcd.clear();  
     }

if (yVal > 431) {
 APERTURA2 = map(yVal,431,1023,0,-255);  
lcd.print ("GIRO IZQ.: ");
lcd.print (APERTURA2); 
delay (150);
lcd.clear();  
     }



  
  compAPERTURA = APERTURA; 

if (compAPERTURA <= 10) {
    digitalWrite(dirPin1, 1);
    digitalWrite(dirPin2, 1);
     }

  if (yVal > 410 & yVal <460) {     
    //if (yVal > 320 & yVal <380) 
    // if (yVal > 508 & yVal <512)
    digitalWrite(dirPin1, 1);
    digitalWrite(dirPin2, 1);
    APERTURA = map(yVal,500,0,0,0);
    analogWrite(Valvula1, APERTURA);
     }   
   
  if (yVal > 460) {
    APERTURA = map(yVal,460,1023,0,255);
    //APERTURA = map(yVal,380,1023,0,255);
    digitalWrite(dirPin1, 0);
    digitalWrite(dirPin2, 1);
    analogWrite(Valvula1, APERTURA);
   } else {
   digitalWrite(dirPin2, 0);
  }
 
  if (yVal <= 410 ) {
    APERTURA = map(yVal,410,0,0,255);
    digitalWrite(dirPin1, 1);
    digitalWrite(dirPin2, 0);
    analogWrite(Valvula1, APERTURA);
   }else {
   digitalWrite(dirPin1, 0);
  }
  }
