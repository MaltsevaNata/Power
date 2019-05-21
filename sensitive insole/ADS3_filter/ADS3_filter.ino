#include <Wire.h> 
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
Adafruit_ADS1115 ads_2(0x49);
Adafruit_ADS1115 ads_3(0x4A);

// переменные для калмана
float varVolt = 5;  // среднее отклонение (ищем в excel)
float varProcess = 0.05; // скорость реакции на изменение (подбирается вручную)
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;
// переменные для калмана
//ЭТО ВСЕ НУЖНО ПРОВЕРИТЬ
float Volt = 0.0;
float data [10];
String message = "";


void setup(void)
{
  Serial.begin(9600);
  ads.begin();
  ads_2.begin();
  ads_3.begin();

}

void loop(void)
{
  int n;
  int16_t adc [10];  // we read from the ADC, we have a sixteen bit integer as a result
  for (int i = 0; i <= 9; i++) {
    n = i;
    if (n >= 4 && n < 8)
      n = n - 4;
    if (n >= 8)
      n = n - 8;
    adc [i] = ads.readADC_SingleEnded(n);
    data[i] = Voltage(adc[i]);
  }
  int mVolt [10];
  float filtered[10];
  for (int i = 0; i <= 9; i++) {
    mVolt[i] = milVolt(data[i]);
    filtered[i] = filter(mVolt[i]);
  }



  Serial.println("$");
  for (int i = 0; i <= 9; i++) {
    Serial.println(mVolt[i]);
    Serial.println(" ");
    Serial.println(filtered[i]);
    Serial.println(" ");
  }
  Serial.println(";");

  for (int i = 0; i <= 9; i++) {
    if ((data[i] >= 0) && (data[i] < 1)) {
      if (mVolt[i] < 100) message = message + 0; //Serial.print("0");
      if (mVolt[i] < 10) message = message + 0; //Serial.print("0");
      message = message + mVolt[i]; //Serial.print(mVolt[i]);
    }
    else {
      message = message + "010"; //Serial.print("001");
    }
  }

  /*Serial.println(message);
    message = "";*/

  /*
    // delay(500);
    /* Serial.print("  | ");
    Serial.print("AIN1: ");
    Serial.print(adc1);
    Serial.print("\tVoltage: ");
    Serial.print(Voltage (adc1), 7);
     Serial.print("  | ");
    Serial.print("AIN2: ");
    Serial.print(adc2);
    Serial.print("\tVoltage: ");
    Serial.print(Voltage (adc2), 7);*/
  //Serial.print("\tMax: ");
  //Serial.print(max);
  // Serial.println();

}


float Voltage (int16_t adc) {
  Volt = (adc * 0.1875) / 1000;
  return Volt;

}

int milVolt (float Volt) {
  int rez = (int)(Volt * 1000);
  return rez;
}



float filter(float val) {  //функция фильтрации
  Pc = P + varProcess;
  G = Pc / (Pc + varVolt);
  P = (1 - G) * Pc;
  Xp = Xe;
  Zp = Xp;
  Xe = G * (val - Zp) + Xp; // "фильтрованное" значение
  return (Xe);
}
