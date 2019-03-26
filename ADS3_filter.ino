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

float Volt = 0.0;
float data0;
float data1;
float data2;
float data3;

float data4;
float data5;
float data6;
float data7;

float data8;
float data9;
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

  int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result
  int16_t adc1;
  int16_t adc2;
  int16_t adc3;
  int16_t adc4;
  int16_t adc5;
  int16_t adc6;
  int16_t adc7;
  int16_t adc8;
  int16_t adc9;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  adc4 = ads_2.readADC_SingleEnded(0);
  adc5 = ads_2.readADC_SingleEnded(1);
  adc6 = ads_2.readADC_SingleEnded(2);
  adc7 = ads_2.readADC_SingleEnded(3);

  adc8 = ads_3.readADC_SingleEnded(0);
  adc9 = ads_3.readADC_SingleEnded(1);

  data0 = Voltage(adc0); 

  data1 = Voltage(adc1);

  data2 = Voltage(adc2);

  data3 = Voltage(adc3);

  data4 = Voltage(adc4);

  data5 = Voltage(adc5);

  data6 = Voltage(adc6);

  data7 = Voltage(adc7);

  data8 = Voltage(adc8);

  data9 = Voltage(adc9);

  int mVolt0 = milVolt(data0);
  int mVolt1 = milVolt(data1);
  int mVolt2 = milVolt(data2);
  int mVolt3 = milVolt(data3);

  int mVolt4 = milVolt(data4);
  int mVolt5 = milVolt(data5);
  int mVolt6 = milVolt(data6);
  int mVolt7 = milVolt(data7);

  int mVolt8 = milVolt(data8);
  int mVolt9 = milVolt(data9);

  float filtered0 = filter(mVolt0);
  float filtered1 = filter(mVolt1);
  float filtered2 = filter(mVolt2);
  float filtered3 = filter(mVolt3);
  
  float filtered4 = filter(mVolt4);
  float filtered5 = filter(mVolt5);
  float filtered6 = filter(mVolt6);
  float filtered7 = filter(mVolt7);

  float filtered8 = filter(mVolt8);
  float filtered9 = filter(mVolt9);
  
  Serial.println("$");
  Serial.println(mVolt0);
   Serial.println(" ");
   Serial.println(filtered0);
   Serial.println(" ");
   Serial.println(filtered1);
    Serial.println(" ");
   Serial.println(filtered2);
      Serial.println(" ");
   Serial.println(filtered3);
   Serial.println(" ");
   
   Serial.println(filtered4);
    Serial.println(" ");
   Serial.println(filtered5);
     Serial.println(" ");
   Serial.println(filtered6);
    Serial.println(" ");
   Serial.println(filtered7);

   Serial.println(" ");
   Serial.println(filtered8);
    Serial.println(" ");
   Serial.println(filtered9);
   
   Serial.println(";");
 
// Serial.println(mVolt1);
  if ((data0 >= 0) && (data0 < 1)) {
    if (mVolt0 < 100) message = message + 0; //Serial.print("0");
    if (mVolt0 < 10) message = message + 0; //Serial.print("0");
    message = message + mVolt0; //Serial.print(mVolt0);
  }
  else {
    message = message + "010"; //Serial.print("001");
  }

  if ((data1 >= 0) && (data1 < 1)) {
    if (mVolt1 < 100) message = message + 0; // Serial.print("0");
    if (mVolt1 < 10) message = message + 0; //Serial.print("0");
    message = message + mVolt1; // Serial.print(mVolt1);
  }
  else {
    message = message + "010"; // Serial.print("001");
  }

  if ((data2 >= 0) && (data2 < 1)) {
    if (mVolt2 < 100) message = message + 0; //Serial.print("0");
    if (mVolt2 < 10) message = message + 0; //Serial.print("0");
    message = message + mVolt2; //Serial.print(mVolt2);
    //delay(300);
  }
  else {
    message = message + "010"; //Serial.print("001");
  }

  if ((data3 >= 0) && (data3 < 1)) {
    if (mVolt3 < 100) message = message + 0; //Serial.print("0");
    if (mVolt3 < 10) message = message + 0; //Serial.print("0");
    message = message + mVolt3; //Serial.println(mVolt3);
    //delay(400);
  }
  else {
    message = message + "010"; //Serial.println("001");
  }

  if ((data4 >= 0) && (data4 < 1)) {
    if (mVolt4 < 100) message = message + 0; //Serial.print("0");
    if (mVolt4 < 10) message = message + 0; //Serial.print("0");*/
    message = message + mVolt4; //Serial.println(mVolt3);
    //delay(80);
  }
  else {
    message = message + "010"; //Serial.println("001");
  }

  if ((data5 >= 0) && (data5 < 1)) {
    if (mVolt5 < 100) message = message + 0; //Serial.print("0");
    if (mVolt5 < 10) message = message + 0; //Serial.print("0");*/
    message = message + mVolt5; //Serial.println(mVolt3);
    //delay(80);
  }
  else {
    message = message + "010"; //Serial.println("001");
  }

  if ((data6 >= 0) && (data6 < 1)) {
    if (mVolt6 < 100) message = message + 0; //Serial.print("0");
    if (mVolt6 < 10) message = message + 0; //Serial.print("0");*/
    message = message + mVolt6; //Serial.println(mVolt3);
    // delay(10);
  }
  else {
    message = message + "010"; //Serial.println("001");
  }

  if ((data7 >= 0) && (data7 < 1)) {
    if (mVolt7 < 100) message = message + 0; //Serial.print("0");
    if (mVolt7 < 10) message = message + 0; //Serial.print("0");*/
    message = message + mVolt7; //Serial.println(mVolt3);
    //delay(10);
  }
  else {
    message = message + "010"; //Serial.println("001");
  }

  if ((data8 >= 0) && (data8 < 1)) {
    if (mVolt8 < 100) message = message + 0; //Serial.print("0");
    if (mVolt8 < 10) message = message + 0; //Serial.print("0");*/
  message = message + mVolt8; //Serial.println(mVolt3);
  //delay(10);
   }
    else {
     message = message + "010"; //Serial.println("001");
    }
  
  if ((data9 >= 0) && (data9 < 1)) {
    if (mVolt9 < 100) message = message + 0; //Serial.print("0");
    if (mVolt9 < 10) message = message + 0; //Serial.print("0");*/
  message = message + mVolt9; //Serial.println(mVolt3);
  delay(10);
   }
    else {
     message = message + "010"; //Serial.println("001");
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
  G = Pc/(Pc + varVolt);
  P = (1-G)*Pc;
  Xp = Xe;
  Zp = Xp;
  Xe = G*(val-Zp)+Xp; // "фильтрованное" значение
  return(Xe);
}



  
