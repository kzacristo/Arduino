#include <Wire.h>

//variavle comparatorio.
int fc = 0;
int sat = 0;
int vetor[8];
String validar = "";
String sFc = "";
String sSat = "";

void setup() {
  Serial.begin(115200); /* begin serial for debug */
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
}

void loop() {
  mestre();

}
void mestre() {
  Wire.beginTransmission(8); /* begin with device address 8 */
  Wire.write("Me envie os dados");  /* sends hello string */
  Wire.endTransmission();    /* stop transmitting */

  Wire.requestFrom(8, 8); /* request & read data of size 13 from slave */
  while (Wire.available()) {
    char rvalor = Wire.read();
    Serial.println(rvalor); 
    validar += rvalor;
  }
  Serial.println();
  IsNumeric( validar);
  delay(1000);
}

//função para validar a string como numerica.
boolean IsNumeric(String validar) {
  if (validar.length() < 1) {
    return false;
  }
  bool bPoint = false;
  for (unsigned char i = 0; i < validar.length(); i++) {
    if (!(isDigit(validar.charAt(i) || validar.charAt(i) == '*') || bPoint)) {
      return false;
    } if (validar.charAt(i) == '*') {
      bPoint = true;
    }
  } return true;
}
