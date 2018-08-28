#include <LCD5110_Basic.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS  1000
//para o lcd nokia5110
LCD5110 tela(8,9,10,12,11);
/*Cria objeto da classe LCD5110
CLK – Pino 8
DIN – Pino 9
DC – Pino 10
RST – Pino 12
CE – Pino 11
*/

//Obtendo as fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];


//para o max30100
PulseOximeter pox;
uint8_t tsLastReport = 0;

//para transmissão para o nodeMCU
char enviar[3];
String pmestre;
int fc = 0;
int sat = 0;
int cont = 0;

void onBeatDetected(){
    Serial.println("Beat!");
    tela.clrScr(); 
    tela.setFont(SmallFont);
    tela.print("Beat!", CENTER, 24);
    delay(1000);
}
void setup(){
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);

  tela.InitLCD();//inicializando o lcd
  
  Serial.print("Iniciando pulse oximeter...");
  if(!pox.begin()){
    Serial.println("FAILED");
    for(;;);
  }else{
    Serial.println("SUCCESS");
  }
 //detecta a colocação ou não do dedo 
 pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop(){
   max30100();
}

void max30100(){
   pox.update();
      if(millis() - tsLastReport > REPORTING_PERIOD_MS){
       /* Serial.print("Heart rate: ");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2  ");
        Serial.print(pox.getSpO2());
        Serial.println("%");*/
        tsLastReport = millis();

        fc = int(pox.getHeartRate());
        sat = int(pox.getSpO2());
        
        tela.setFont(SmallFont);
        tela.print("FC", LEFT,0);
        tela.setFont(MediumNumbers);
        tela.printNumI(fc,CENTER,0);
        tela.setFont(SmallFont);
        tela.print("bpm",RIGHT,0);
        tela.setFont(SmallFont);
        tela.print("SAT", LEFT,24);
        tela.setFont(MediumNumbers);
        tela.printNumI(sat,CENTER,24);
        tela.setFont(SmallFont);
        tela.print("%",RIGHT,24);
        //delay(1000);
        
        enviar[0] = char(fc);
        enviar[1] = char(sat);
        enviar[2] = ';';

        pmestre = (char(fc)+char(sat)+";");
        
        requestEvent(pmestre);
          
       
        
      }  
}
void receiveEvent(int howMany){
  while(0<Wire.available()){
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void requestEvent(String pmestre){

    for(int x=0;x>=3;x++){
    
    }
    tela.clrScr(); 
    Wire.write(pmestre);
    Serial.println("cheguei");
   
}

