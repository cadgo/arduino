#include <iostream>
#include <string>
#define NO_KEY NULL
typedef unsigned char byte;
class Serial{
	public:
		void println(std::string op1){
			std::cout << op1 << std::endl;
		}
		void println(byte x){
			std::cout << (byte)x << std::endl;
		}
}Serial;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
const byte ROWS = 4;
const byte COLS = 4;

const byte PASSLENGTH = 6;
const byte PASS1[PASSLENGTH] = {'2', '9', '1', '1', '8', '3'};
byte CAPTURED[PASSLENGTH];
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void AddData(byte data, int pos){
  Serial.println("Agregando ");
  std::cout << data << std::endl;
  //Serial.println(data);
  CAPTURED[pos] = data;
}

int ComparePass(){
 //Serial.println("Comprare pass");
 for (int x=0; x < PASSLENGTH; x++){
   //std::cout << "password " << (byte)PASS1[x] << std::endl;
   //std::cout << "catpurado " << (byte)CAPTURED[x] << std::endl;
   if (CAPTURED[x] != PASS1[x])
     return 0;
 }
   return 1;
}

void InitBuffer(){
  for (int x=0; x <= PASSLENGTH; x++){
        //Serial.println("Informacion del buffer \n");
        //Serial.println(CAPTURED[x]);
        std::cout << CAPTURED[x] << std::endl;
        CAPTURED[x] = 0;
  }
}

int globalCounter = 0;
int gloCounRes=0;
void loop(){
while(1){
byte key =0;
  std::cin>>key;
  std::cout << "indice " << globalCounter << std::endl;
  //Serial.println("indice ");
  //Serial.println(i);
  if (key != NO_KEY){
    if (globalCounter < PASSLENGTH){
      Serial.println("Agregando Datos al buffer");
      std::cout << (byte)key << std::endl;
      CAPTURED[globalCounter] = key;
    }
    else{
      int comp = ComparePass();
      Serial.println("Resultado de la comparacion");
      if ( comp == 0){
        Serial.println("Password Incorrecto");
        InitBuffer();
        gloCounRes = 1;
      }
      else{
        Serial.println("Password correcto");
        InitBuffer();
        gloCounRes =1;
      }
    }
    //else{
    //  Serial.println("borrando buffer");
    //    InitBuffer();
    //    i = 0;
    //  }
    if (gloCounRes == 0)
        globalCounter++;
    else{
        globalCounter =0;
        gloCounRes = 0;
    }
  }
}
}


int main(int argc, char** argv) {
	loop();
	return 0;
}
