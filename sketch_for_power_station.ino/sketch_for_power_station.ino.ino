#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Debug.h>
#include <MFRC522Extended.h>
#include <MFRC522Hack.h>
#include <require_cpp11.h>


/* MOSI: Pin 11 / ICSP-4
  MISO: Pin 12 / ICSP-1
  SCK: Pin 13 / ISCP-3
  SDA: Pin 10
  RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

#include <Servo.h>
Servo S0;
Servo S1;

RFID rfid(SS_PIN, RST_PIN);

unsigned char reading_card[5]; //for reading card
unsigned char master[5] = {205, 182, 67, 213, 237};
unsigned char master2[5] = {54, 141, 192, 50, 73}; // allowed card
unsigned char i;
unsigned char k;
unsigned char N;
unsigned char b;
unsigned char array[5] = {1, 1, 1, 1, 1};
unsigned char massiv[5][2];

void indication(int led);
void allow();
void denied();

void setup()
{
  S0.attach(5);
  S1.attach(6);
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  b = 1;

}

void loop()
{

  S0.write(0);
  S1.write(0);
  //delay(100);
  Serial.println("test");

  if (rfid.isCard())
  {

    if (rfid.readCardSerial())
    {
      /* Reading card */
      Serial.println(" ");
      Serial.println("Card found");
      Serial.println("Cardnumber:");
      for (i = 0; i < 5; i++)
      {
        Serial.print(rfid.serNum[i]);
        Serial.print(" ");
        reading_card[i] = rfid.serNum[i];
      }
      Serial.println();
      //verification
      for (i = 0; i < 5; i++)
      {
        if (reading_card[i] != master[i] && reading_card[i] != master2[i])
        {
          break;
        }
      }
      if (i == 5)
      {
        for (N = 0; N < 5; N++)
        {
          for ( k = 0; k < 5; k++)
          {
            if (reading_card[k] != massiv[k][N])
            {
              break;
            }

          }
          if (k == 5)
          {
            vozvrat(N);
            break;
          }
        }

        if ( N == 5)
        {
          allow();
        }
      }
      else
      {
        denied();

      }
    }
  }
  else {


  }

}

void allow()
{
  Serial.println("Access accept!"); //доступ получен
  for (N = 0; N < 5; N++)
  { Serial.print("N=");
    Serial.println(N);
    if (array[N] == 1)
    { Serial.println("open");
      if (b == 1)
      {
        array[N] = 0;
        Serial.print("massive element=");
        Serial.println(array[N]);
        Serial.println(N);

        break;
      }
    }
  }

  switch (N) {
    case 0:
      //выполняется, когда var равно 1
      for (int i = 0; i < 180; i++) {
        S0.write(i);
        delay(10);
      }
      delay(5000);
      for (int i = 180; i >= 180; i--) {
        S0.write(i);
        delay(10);
      }
      for ( i = 0; i < 5; i++)
      {
        massiv[i][N] = reading_card[i];
        Serial.print(massiv[i][N]);
        Serial.print(" ");
      }
      break;
    case 1:
      //выполняется когда  var равно 2
      for (i = 0; i < 180; i++) {
        S1.write(i);
        delay(10);
      }
      delay(5000);
      for (i = 180; i >= 180; i--) {
        S1.write(i);
        delay(10);
        for ( i = 0; i < 5; i++)
        {
          massiv[i][N] = reading_card[i];
          Serial.print(massiv[i][N]);
          Serial.print(" ");
        }
      }

      break;
    default:
      Serial.println("No allowed batteries");

  }

}
void denied()
{
  Serial.println("Access denied!"); //доступ закрыт

}

void vozvrat(int R)
{
  Serial.println("vozvrat");
  Serial.println(R);
  switch (R) {
    case 0:

      for (int i = 0; i < 180; i++) {
        S0.write(i);
        delay(10);
      }
      delay(5000);
      for (int i = 180; i >= 180; i--) {
        S0.write(i);
        delay(10);
      }
      for ( i = 0; i < 5; i++)
      {
        massiv[i][R] = 0;
        Serial.print(massiv[i][R]);
        Serial.print(" ");
      }
      array[R] = 1;
      break;
    case 1:
      //выполняется когда  var равно 2
      for (i = 0; i < 180; i++) {
        S1.write(i);
        delay(10);
      }
      delay(5000);
      for (i = 180; i >= 180; i--) {
        S1.write(i);
        delay(10);
        for ( i = 0; i < 5; i++)
        {
          massiv[i][R] = 0;
          Serial.print(massiv[i][R]);
          Serial.print(" ");
        }
        array[R] = 1;
      }

      break;


  }

}
