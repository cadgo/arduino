#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
const byte PASSLENGTH = 6;
const byte PASS1[PASSLENGTH] = {2, 9, 1, 1, 8, 3};
char CAPTURED[PASSLENGTH];
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte i = 0;
byte ROWPINS[ROWS]= {9, 8, 7, 6};
byte COLSPINS[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys),ROWPINS, COLSPINS, ROWS, COLS);

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    if (i < PASSLENGTH){
      Serial.println("Agregando Datos al buffer");
      Serial.println(key);
      CAPTURED[i] = key;
    }
    else{
      Serial.println("borrando buffer");
      for (int x= 0; x < PASSLENGTH; x++){
        Serial.print("Informacion del buffer ");
        Serial.println(CAPTURED[x]);
        CAPTURED[x] = 0;
        i = 0;
      }
    }
    i++;
  }
}
