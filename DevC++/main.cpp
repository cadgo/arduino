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
byte PASS1[PASSLENGTH] = {'2', '9', '1', '1', '8', '3'};
byte PASS2[PASSLENGTH] = {'1', '0', '4', '1', '4', '2'};
byte CAPTURED[PASSLENGTH];
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

int globalCounter = 0;
int gloCounRes=0;

void AddData(byte data, int pos){
  Serial.println("Agregando ");
  std::cout << data << std::endl;
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
void loop2(){
while(1){
byte key =0;
  std::cin>>key;
  std::cout << "indice " << globalCounter << std::endl;
  //Serial.println("indice ");
  //Serial.println(i);
  if (key != NO_KEY){
    if (globalCounter < PASSLENGTH+1){
      Serial.println("Agregando Datos al buffer");
      std::cout << (byte)key << std::endl;
      //CAPTURED[globalCounter] = key;
      switch(key)
      {
        case 'A':
            comp1 = ComparePass(PASS1);
            comp2 = ComparePass(PASS2);
            Serial.println("Comparing");
            std::cout << comp1 << std::endl;
            std::cout << comp2 << std::endl;
            if ((comp1 == 0) || (comp2 == 0)){
                Serial.println("Password Coorrecto");
                InitBuffer();
            }else{
                Serial.println("Password Incorrecto");
                InitBuffer();
            }
        break;
        default:
            CAPTURED[globalCounter] = key;
            globalCounter++;
        break;
      }
    }else{
        Serial.println("else");
        InitBuffer();
    }
  }
}
}
//void loop(){
//while(1){
//byte key =0;
//  std::cin>>key;
//  std::cout << "indice " << globalCounter << std::endl;
//  //Serial.println("indice ");
//  //Serial.println(i);
//  if (key != NO_KEY){
//    if (globalCounter < PASSLENGTH){
//      Serial.println("Agregando Datos al buffer");
//      std::cout << (byte)key << std::endl;
//      CAPTURED[globalCounter] = key;
//    }
//    else{
//      int comp = ComparePass();
//      Serial.println("Resultado de la comparacion");
//      if ( comp == 0){
//        Serial.println("Password Incorrecto");
//        InitBuffer();
//        gloCounRes = 1;
//      }
//      else{
//        Serial.println("Password correcto");
//        InitBuffer();
//        gloCounRes =1;
//      }
//    }
//    if (gloCounRes == 0)
//        globalCounter++;
//    else{
//        globalCounter =0;
//        gloCounRes = 0;
//    }
//  }
//}
//}


int main(int argc, char** argv) {
	loop2();
	return 0;
}
