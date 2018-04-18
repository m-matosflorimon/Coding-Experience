#include <Keypad.h>

#define sw1 PINC
#define sw2 PIND
#define current PINL
#define sala_cocina PORTF
#define habitacion PORTK 

//corrientes
#define latch1 16 //sala
#define latch2 15 //cocina 
#define latch3 14 //habitacion
#define latch_clk 1

//sala
#define stv A0
#define sfan A1
#define slight A2
#define slamp A3
#define smaxc 50 //corriente maxima de la sala

//cocina
#define nevera A4
#define micro A5
#define cfan A6
#define clight A7
#define cmaxc 50 //corriente maxima de la cocina

//habitacion
#define hlamp A8
#define htv A9
#define hlight A10
#define radio A11
#define hmaxc 50 //corriente maxima de la habitacion

//keypad
#define row1 9
#define row2 8
#define row3 7
#define row4 6
#define col1 5
#define col2 4
#define col3 3
#define col4 2


//sala_teclado
#define stvk '1'
#define sfank '2'
#define slightk '3'
#define slampk 'A'

//cocina_teclado
#define neverak '4'
#define microk '5'
#define cfank '6'
#define clightk 'B'

//habitacion_teclado
#define hlampk '7'
#define htvk '8'
#define hlightk '9'
#define radiok 'C'

#include <Keypad.h>

byte diff;
byte sw1_actual = sw1;
byte sw2_actual = sw2;
byte sw1_new = sw1;
byte sw2_new = sw2;
int pressed;



const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {row1, row2, row3, row4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {col1, col2, col3, col4}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

char blueToothVal;           //value sent over via bluetooth

void setup() {
  
  DDRL = 0;
  DDRC = 0;
  DDRD = 0;
  DDRF = B11111111;
  DDRK = B00001111;
  sala_cocina = 0;
  habitacion = 0;
/*
  pinMode (stv , OUTPUT);
  pinMode (sfan , INPUT);
  pinMode (slight , INPUT);
  pinMode (slamp , INPUT);

  pinMode (nevera , INPUT);
  pinMode (micro , INPUT);
  pinMode (cfan , INPUT);
  pinMode (clight , INPUT);

  pinMode (hlamp , INPUT);
  pinMode (htv , INPUT);
  pinMode (hlight , INPUT);
  pinMode (radio , INPUT);
*/
  pinMode(latch1 , OUTPUT);
  pinMode(latch2 , OUTPUT);
  pinMode(latch3 , OUTPUT);

  digitalWrite(latch1 , HIGH);
  digitalWrite(latch2 , HIGH);  
  digitalWrite(latch3 , HIGH);
  
  pinMode(13 ,OUTPUT);
  Serial.begin(9600);



 
 
}

void loop() {
//////////////////////////////////// check current /////////////////////////////////////////////////

  digitalWrite(latch1 , LOW);
  //Serial.println(current);
  if (current >= smaxc){
    ctrl_individual('*');
  }
  digitalWrite(latch1 , HIGH);
  delay(latch_clk);
  
  digitalWrite(latch2 , LOW);
  //Serial.println(current);
  if (current >= cmaxc){
    ctrl_individual('0');
  }
  digitalWrite(latch2 , HIGH);
  delay(latch_clk);

  digitalWrite(latch3 , LOW);
  //Serial.println(current);
  if (current >= hmaxc){
    ctrl_individual('#');
  }
  digitalWrite(latch3 , HIGH);

//////////////////////////////////// check switches /////////////////////////////////////////////////

  sw1_new = sw1;
  if (sw1_new != sw1_actual){
    diff = sw1_new ^ sw1_actual;
    sala_cocina =  sala_cocina ^ diff;
    sw1_actual = sw1_new;

  }
 

  sw2_new = sw2;
  if (sw2_new != sw2_actual){
    diff = sw2_new ^ sw2_actual; 
    habitacion = habitacion ^ diff;
    sw2_actual = sw2_new;
  }

//////////////////////////////////// check keypad /////////////////////////////////////////////////

  pressed = keypad.getKey();
  if(pressed != NO_KEY){
    ctrl_individual(pressed);
  }  
  
//////////////////////////////////// check bluetooth /////////////////////////////////////////////////

  if(Serial.available())
  {//if there is data being recieved
    blueToothVal=Serial.read(); //read it
    ctrl_individual(blueToothVal);
  }
  
}

//////////////////////////////////// Stuff control /////////////////////////////////////////////////

void ctrl_individual(char key) {
      //Serial.println(pressed);
    //Serial.println(key);
    switch (key){

 //sala
      case stvk:
        digitalWrite(stv , !digitalRead(stv));
        //Serial.println(digitalRead(stv));
        break;
        
      case sfank:
        digitalWrite(sfan , !digitalRead(sfan));
        break;
        
      case slightk:
        digitalWrite(slight , !digitalRead(slight));
        break;
        
      case slampk:
        digitalWrite(slamp , !digitalRead(slamp));
        break;
        
//cocina
      case neverak:
        digitalWrite(nevera , !digitalRead(nevera));
        break;
        
      case microk:
        digitalWrite(micro , !digitalRead(micro));
        break;

      case cfank:
        digitalWrite(cfan , !digitalRead(cfan));
        break;
        
      case clightk:
        digitalWrite(clight , !digitalRead(clight));
        break;

//habitacion      
      case hlampk:
        digitalWrite(hlamp , !digitalRead(hlamp));
        break;
        
      case htvk:
        digitalWrite(htv, !digitalRead(htv));
        break;

      case hlightk:
        digitalWrite(hlight , !digitalRead(hlight));
        break;
        
      case radiok:
        digitalWrite(radio , !digitalRead(radio));
        break;

//codigos de apagado completo
      case '*':
        sala_cocina = sala_cocina & B11110000;
        break;

      case '0':
        sala_cocina = sala_cocina & B00001111;
        break;

      case '#':
        habitacion = 0;
        break;

      default:
        digitalWrite(13,!digitalRead(13));
        break;

        
    }
}




