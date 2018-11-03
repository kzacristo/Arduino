#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS  1000

//para o max30100
PulseOximeter pox;
uint32_t tsLastReport = 0;


//variaveis glovais para converção
String valor_fc = "";
String valor_sat = "";
int fc = 0;
int sat = 0;

void onBeatDetected() {
  Serial.println("Beat!");
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.begin(115200);


  Serial.print("Iniciando pulse oximeter...");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  //detecta a colocação ou não do dedo
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  max30100();
}

void max30100() {
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate: ");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2  ");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    tsLastReport = millis();


    fc = int(pox.getHeartRate());
    sat = int(pox.getSpO2());

    valor_fc = String(fc);
    valor_sat = String(sat);
    
  }
  requestEvent();
}


void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    char c = Wire.read();
    Serial.print(c);

  }
  Serial.println();
}
void requestEvent() {


  Wire.print(valor_fc);
  Wire.print("*");
  Wire.print(valor_sat);

  //Wire.print(enviar);

}
