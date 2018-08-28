#include <Wire.h>

char receber[3];
int fc = 0;
int sat = 0;

void setup() {
 Serial.begin(115200); /* begin serial for debug */
Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
 Wire.beginTransmission(6); /* begin with device address 3 */
 Wire.write("Hello Arduino");  /* sends hello string */
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(6,7); /* request & read data of size 13 from slave */
 while(Wire.available()){
     for(int x=0; x>=3; x++){
        receber[x] = char(Wire.read());
        Serial.println(receber[x]);  
      }
 }
 Serial.println("ola");
 delay(1000);
}
