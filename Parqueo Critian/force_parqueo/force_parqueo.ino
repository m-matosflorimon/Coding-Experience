
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

//Database
int data[3][2]{
  {0,0},
  {0,0},
  {0,0}
};

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


bool ultrasonic(){
  
  // ultrasonic retorna true si hay auto presente y false en caso contrario
digitalWrite(trigPin, LOW);
delayMicroseconds(500000);
digitalWrite(trigPin, HIGH);
delayMicroseconds(500000);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm =  (duration / 2) / 29;
if (distanceCm<=referencia){
 return true;
  }
 return false;
  
}



/*
 * Esta funcion recibe 2 parametros: selector de funcionalidad , codigo usuario
 * Requests:
 *    1 retorna la hora de entrada del codigo
 *    2 retorna el numero de parqueo donde esta el codigo
 *    3 agrega un nuevo codigo; retorna 1 (tentativo)
 *    Retorna 0 en caso de no encontrar el codigo introducido o si esta lleno el parqueo
 */
int dataBase(int request , int code){

    for (int i; i<=2;i++){
        if(data[i][1] == code){

           switch(request){

              case 1:
                  return data[i][0];

              case 2:
                  return i + 1;
           }
        }
        else if (request == 3 && data[i][0] == 0){

              data[i][0] = getTime();
              data[i][1] = code;
              return 1;    
        }
    }
    return 0;
}

int codigo() {
  while (randomInt == previousRandomInt)
    //Create a random number and assign it to the randomInt variable.
    randomInt = random(0, 10); //When a consecutive random number has been identified, indicate it.
  Serial.println();
  //close while statement
  previousRandomInt = randomInt;
  Serial.print(randomInt);

  return randomInt;
}

void door(bool control){
  
}

int monto(int hora){
  return 0;
}

int getTime(){
  return 0;
}

char menu(){

menu:

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bienvenido!");
  lcd.setCursor(0,1);
  lcd.print("Que desea hacer?");
  lcd.setCursor(0,2);
  lcd.print("1.Depositar vehiculo");
  lcd.setCursor(0,3);
  lcd.print("2.Retirar vehiculo");

  char key = keypad.waitForKey();       

  switch (key){

    case '1':
        if(ultrasonic()){

             lcd.clear();
             int code = codigo();
             if(dataBase(3,code) == 0){
              
              lcd.print("No hay parqueos disponibles");
              break;
             }
              lcd.print("Su codigo es: " + code);
              lcd.setCursor(0,1);
              lcd.print("Presione 'D' cuando salga");
              door(true);

              while(key != 'D'){
                key = keypad.waitForKey();
              }

              door(false);
              lcd.clear();
              lcd.print("Gracias");
              
              //PENDIENTE: Poner cubiculo vacio si existe
              
              delay(5000);
        }
        break;
        
    case '2':
        if(!ultrasonic()){
            
            lcd.clear();
            lcd.print("Digite su codigo");
            lcd.setCursor(0,1);
            String _code = "";
            int i = 0;
            while(_code.length() <= 5){

                key = keypad.waitForKey();
                if(isDigit(key)){
                  _code += key;
                  lcd.setCursor(i,1);
                  lcd.print('*');
                  i++;
                  continue;
                }
                lcd.setCursor(0,2);
                lcd.print("Tecla invalida");
                delay(700);
                lcd.setCursor(0,2);
                lcd.print("               ");
            }

            if(dataBase(1,_code.toInt()) == 0){
              lcd.clear();
              lcd.print("Codigo Invalido");
              goto menu;
            }

            lcd.print("Su monto a pagar es RD$" + monto(dataBase(1,_code.toInt())));
            
        }
    

    default:
      lcd.clear();
      lcd.print("Opcion incorrecta");
      break;
    
  }

  goto menu;
  
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


