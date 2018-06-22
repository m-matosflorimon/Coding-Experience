
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
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

//teclado
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

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

//screen

void(*resetFunc) (void)=0;

//menu
void menu(){
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenido!");
  lcd.setCursor(0,1);
  lcd.print("Que desea hacer?");
  lcd.setCursor(0,2);
  lcd.print("1.Depositar vehiculo");
  lcd.setCursor(0,3);
  lcd.print("2.Retirar vehiculo");
}

 void screen(){
  char key = keypad.getKey();
/////////////////////////////////////////Boton 1
if(key) {
switch (key)
case '1':
{
    char key = keypad.getKey(); //storing pressed key value in a char
  if (key != NO_KEY)
{
      lcd.setCursor(4,1);
      lcd.print(key); //showing pressed character on LCD

  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ingrese su codigo:");

break;
}
}
/////////////////////////////////////////Boton 2
if(key) {
switch (key)
{
case '2'://Cuando key "2" es oprimida...          
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Este es su codigo :");
  lcd.setCursor(6,1);
  lcd.print("codigo");
  lcd.setCursor(6,2);
  lcd.print("****");
break;
}
}

}

  void screen1(){
  char key = keypad.getKey();
/////////////////////////////////////////Boton 1
if(key) {
switch (key)
case '1':
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Un vehiculo bloquea ");
  lcd.setCursor(4,1);
  lcd.print("la salida");
  lcd.setCursor(0,2);
  lcd.print("regresando al menu");
  delay(3000);
  resetFunc(); 
break;
}
}
/////////////////////////////////////////Boton 2
if(key) {
switch (key)
{
case '2'://Cuando key "2" es oprimida...          
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Este es su codigo :");
  lcd.setCursor(6,1);
  lcd.print(key);
  lcd.setCursor(6,2);
  lcd.print("****");
break;
}
}

}
//separación


void setup()
{
  //lcd
    lcd.begin(20,4);
    
  
  // motor
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);

  //ldr

  Serial.begin(9600);
  pinMode(22, OUTPUT);

  //ultrasonic

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  //codigo
  Serial.begin(9600);
  randomInt = random(10000, 99999);

 //force
 menu();
}
void loop()
{
// ultrasonic
digitalWrite(trigPin, LOW);
delayMicroseconds(500000);
digitalWrite(trigPin, HIGH);
delayMicroseconds(500000);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm =  (duration / 2) / 29;
if (distanceCm<=referencia){
 screen1();
  }
if(distanceCm>referencia){
  screen();
  }
 LDRValue = analogRead(LDR);      //reads the ldr’s value through LDR
Serial.println(LDRValue);
delay(50);        //This is the speed by which LDR sends value to arduino

if (LDRValue < light_sensitivity)
{
  digitalWrite(22, LOW);
  Serial.println("No hay carro");
}
else
{
  digitalWrite(22, HIGH);
  Serial.println("Hay carro");
}
}
  // motor
// this subroutine stops the motor
  void stop_motor() {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, LOW);
  }
  
void motorcontrol () {
  switch (_step) {
   case 0:
  if (count < runTime)
  {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, HIGH);
  } else {
    stop_motor();
  }
  break;
case 1:
  if (count < runTime)
  {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, HIGH);
    digitalWrite(Pin4, HIGH);
  } else {
    stop_motor();
  }
  break;
case 2:
  if (count < runTime)
  {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, HIGH);
    digitalWrite(Pin4, LOW);
  } else {
    stop_motor();
  }
  break;
case 3:
  if (count < runTime)
  {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, HIGH);
    digitalWrite(Pin3, HIGH);
    digitalWrite(Pin4, LOW);
  } else {
    stop_motor();
  }
  break;
case 4:
  if (count < runTime)
  {
    digitalWrite(Pin1, LOW);
    digitalWrite(Pin2, HIGH);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, LOW);
  } else {
    stop_motor();
  }
  break;
case 5:
  if (count < runTime)
  {
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, HIGH);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, LOW);
  } else {
    stop_motor();
  }
  break;
case 6:
  if (count < runTime)
  {
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, LOW);
  } else {
    stop_motor();
  }
  break;
case 7:
  if (count < runTime)
  {
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, LOW);
    digitalWrite(Pin3, LOW);
    digitalWrite(Pin4, HIGH);
  } else {
    stop_motor();
  }
  break;
case 8:
  if (count < runTime)
  {
    digitalWrite(Pin1, HIGH);
    digitalWrite(Pin2, HIGH);
    digitalWrite(Pin3, HIGH);
    digitalWrite(Pin4, HIGH);
  } else {
    stop_motor();
  }
  break;
default:
  stop_motor();// stop the motor
  break;
}
if (dir) {
  _step++;
} else {
  _step--;
}
if (_step > 7) {
  _step = 0;
}
if (_step < 0) {
  _step = 7;
}
delay(1);

// check if the counter has reached run time
if (count < runTime) {
  +   count++;//increment count
} 
 else {
  stop_motor();
 }
}

//random
void codigo() {
  while (randomInt == previousRandomInt)
    //Create a random number and assign it to the randomInt variable.
    randomInt = random(0, 10); //When a consecutive random number has been identified, indicate it.
  Serial.println();
  //close while statement
  previousRandomInt = randomInt;
  Serial.print(randomInt);
}
