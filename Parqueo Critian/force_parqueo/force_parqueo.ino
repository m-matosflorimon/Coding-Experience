
//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// motor
int Pin1 = 10;
int Pin2 = 11;
int Pin3 = 12;
int Pin4 = 13;
int _step = 0;
boolean dir = true;// false=clockwise, true=counter clockwise

int referencia = 20;
int count = 0; // counter for running time
int runTime = 0;// the time motor will run

//ldr

int LDR = 0;     //analog pin to which LDR is connected, here we set it to 0 so it means A0
int LDRValue = 0;      //that’s a variable to store LDR values
int light_sensitivity = 500;    //This is the approx value of light surrounding your LDR

//ultrasonic

const int trigPin = 23;
const int echoPin = 24;
long duration;
int distanceCm;
int contar=0;

//codigo

int randomInt = 0;
int previousRandomInt = 0;
/*
//teclado
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
*/
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {5,4,3,2}; //Columnas (pines del 5 al)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


bool ultrasonic(){
  // ultrasonic
digitalWrite(trigPin, LOW);
delayMicroseconds(500000);
digitalWrite(trigPin, HIGH);
delayMicroseconds(500000);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm =  (duration / 2) / 29;
if (distanceCm<=referencia){
 return false;
  }
if(distanceCm>referencia){
  return true;
  }
}

char menu(){
  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenido!");
  lcd.setCursor(0,1);
  lcd.print("Que desea hacer?");
  lcd.setCursor(0,2);
  lcd.print("1.Depositar vehiculo");
  lcd.setCursor(0,3);
  lcd.print("2.Retirar vehiculo");
*/
  char key = keypad.waitForKey();       
  
  return key;    
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  char keyy = menu();
  Serial.println(keyy);
  Serial.println("Paso pa aca");
}


