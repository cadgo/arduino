#include <Keypad.h>
#define VELOCIDAD 1700
int CSTATUS = 10;
int steps = 10;
int direccion = 11;
int reset = 12;
int pasos = 200;
const byte ROWS = 4;
const byte COLS = 4;
const byte PASSLENGTH = 6;
byte PASS1[PASSLENGTH] = {'*', '*', '*', '*', '*', '*'};
byte PASS2[PASSLENGTH] = {'*', '*', '*', '*', '*', '*'};
byte CAPTURED[PASSLENGTH];
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte ROWPINS[ROWS]= {9, 8, 7, 6};
byte COLSPINS[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys),ROWPINS, COLSPINS, ROWS, COLS);

void setup(){
  Serial.begin(9600);
  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
  pinMode(reset, OUTPUT);
  //Necesitamos definir el estado anterior del motor para volverlo a un estado
}

int globalCounter = 0;
int gloCounRes=0;
int ABRIR = HIGH;
int CERRAR = LOW;

void Apertura(int GIRO){
  digitalWrite(reset, HIGH);
  delay(100);
  digitalWrite(direccion, GIRO);
  for (int i = 0; i<pasos; i++)       //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.  
    delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.
  }
  delay(100);
  digitalWrite(reset,LOW);     
}

void AddData(byte data, int pos){
  Serial.println("Agregando ");
  Serial.println(data);
  //Serial.println(data);
  CAPTURED[pos] = data;
}

int ComparePass(byte comppass[]){
 for (int x=0; x < PASSLENGTH; x++){
   if (CAPTURED[x] != comppass[x])
     return 0;
 }
   return 1;
}

void InitBuffer(){
  for (int x=0; x <= PASSLENGTH; x++){
        CAPTURED[x] = 0;
  }
  globalCounter=0;
}
int comp1=0;
int comp2=0;

void loop(){
  digitalWrite(reset, LOW);
  char key = keypad.getKey();
  //Serial.println("indice ");
  //Serial.println(i);
  if (key != NO_KEY){
    if (globalCounter < PASSLENGTH+1){
      Serial.println("Agregando Datos al buffer");
      Serial.println(key);
      //CAPTURED[globalCounter] = key;
        switch(key)
      {
        case 'A':
            comp1 = ComparePass(PASS1);
            comp2 = ComparePass(PASS2);
            Serial.println("Comparing");
            Serial.println(comp1);
            Serial.println(comp2);
//            if ( comp1 == 1){
//              Serial.println("Password Coorrecto");
//              InitBuffer();
//            }
//            else{
//              Serial.println("Password Incorrecto");
//              InitBuffer();
//            }
            if ((comp1 == 1) || (comp2 == 1)){
                Serial.println("Password Coorrecto");
                //llamamos a la apertura
                if (CSTATUS == ABRIR)
                  Serial.println("Cerradura previamente abierta");
                else{
                  Apertura(ABRIR);
                  CSTATUS = ABRIR;
                  Serial.println("Abriendo Cerradura");
                  InitBuffer();
                }
            }else{
                Serial.println("Password Incorrecto");
                //Cerramos Cerradura
                //Apertura(CERRAR);
                //Serial.println("Cerrando Cerradura");
                InitBuffer();
            }
        break;
        case 'B':
          Serial.println("Borrando Datos");
          InitBuffer();
        break;
        default:
            CAPTURED[globalCounter] = key;
            globalCounter++;
        break;
        case 'C':
          if (CSTATUS == CERRAR)
            Serial.println("Cerradura previamente cerrada");
          else{
            Serial.println("Cerrando Cerradura");
            Apertura(CERRAR);
            CSTATUS = CERRAR; 
          }
        break;
      }
      }else{
        Serial.println("BORRANDO");
        InitBuffer();
    }
  }
}
