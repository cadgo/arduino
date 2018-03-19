#include <Keypad.h>
int relaysig = 13;
int LEDT = 12;
const byte ROWS = 4;
const byte COLS = 4;
const byte PASSLENGTH = 6;
byte PASS1[PASSLENGTH] = {'2', '9', '1', '1', '8', '3'};
byte PASS2[PASSLENGTH] = {'1', '0', '4', '1', '4', '2'};
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
  pinMode(relaysig, OUTPUT);
  pinMode(LEDT, OUTPUT);
}

int globalCounter = 0;
int gloCounRes=0;

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
  digitalWrite(LEDT, HIGH);
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
                digitalWrite(relaysig, HIGH);
                Serial.println("Abriendo Cerradura");
                delay(5000);
                digitalWrite(relaysig, LOW);
                Serial.println("Cerrando Cerradura");
                InitBuffer();
            }else{
                Serial.println("Password Incorrecto");
                digitalWrite(relaysig, LOW);
                Serial.println("Cerrando Cerradura");
                InitBuffer();
            }
        break;
        default:
            CAPTURED[globalCounter] = key;
            globalCounter++;
        break;
      }
      }else{
        Serial.println("BORRANDO");
        InitBuffer();
    }
  }
}
