#include <iostream>
#include <string>
#define NO_KEY 9
typedef int byte;
class Serial{
	public:
		void println(std::string op1){
			std::cout << op1 << std::endl;
		}
		void println(int x){
			std::cout << x << std::endl;
		}
}Serial;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
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
void AddData(byte data, int pos){
  CAPTURED[pos] = data;
}

int ComparePass(){
 Serial.println("Comprare pass");
 for (int x=0; x < PASSLENGTH; x++){
   if (CAPTURED[x] != PASS1[x])
     return 0;
 }
   return 1;
}

void InitBuffer(){
  for (int x; x < PASSLENGTH; x++){
        Serial.println("Informacion del buffer ");
        //Serial.println(CAPTURED[x]); 
        std::cout << CAPTURED[x];
        AddData(0, x);
  }
}

void loop(){
while(1){
char key =0;
  std::cin>>key;
  if (key != NO_KEY){
    if (i < PASSLENGTH){
      Serial.println("Agregando Datos al buffer");
      std::cout << key << std::endl;
      AddData(key, i);
    }
    else{
      int comp = ComparePass();
      Serial.println("Resultado de la comprar");
      Serial.println(comp);
      if ( comp == 0){
        Serial.println("borrando buffer");
        InitBuffer();
        i = 0;
      }
      else{
        Serial.println("Password correcto");
      }
    }
    //else{
    //  Serial.println("borrando buffer");
    //    InitBuffer();
    //    i = 0;
    //  }
    i++;
  }
}
}
  

int main(int argc, char** argv) {
	loop();
	return 0;
}
