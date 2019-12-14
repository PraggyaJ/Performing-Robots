
//Servo
#include <Servo.h>

//Neopixel
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif


#define MOUTHPIXELS 74
#define EYESPIXELS 25


#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

Adafruit_NeoPixel mouth (MOUTHPIXELS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel eyes (EYESPIXELS, 5, NEO_RGBW + NEO_KHZ800);
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
Servo myservo1;
Servo myservo2;

int posServo1 = 0;
int posServo2 = 0;
int k = 0;
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

void setup(void)
{

  myservo1.attach(9);
  myservo2.attach(10);
  mouth.begin();
  eyes.begin();



  while (!Serial);  // required for Flora & Micro
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit App Controller Example"));
  Serial.println(F("-----------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ) {
      error(F("Couldn't factory reset"));
    }

  }


  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
    delay(500);
    Serial.println("Hello World");
  }



  Serial.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("******************************"));

}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
int grinnum = 0;
void loop(void)
{
  mouth.clear();
  eyes.clear();

  /* Wait for new data to arrive */
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  /* Got a packet! */
  // printHex(packetbuffer, len);

  // Color
  if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    Serial.print ("RGB #");
    if (red < 0x10) Serial.print("0");
    Serial.print(red, HEX);
    if (green < 0x10) Serial.print("0");
    Serial.print(green, HEX);
    if (blue < 0x10) Serial.print("0");
    Serial.println(blue, HEX);
  }

  // Buttons


  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';
    Serial.print ("Button "); Serial.print(buttnum);
    if (pressed) {
      Serial.println(" pressed");
    } else {
      Serial.println(" released");
    }

    while (buttnum == 5 && pressed == true && posServo1 < 120) {
      posServo1 += 10;
      myservo1.write(posServo1);
      myservo2.write(120 - posServo1);
      delay(50);
    }
    while (buttnum == 6 && pressed == true && posServo1 >= 0) {
      posServo1 -= 10;
      myservo1.write(posServo1);
      myservo2.write(120 - posServo1);
      delay(50);
    }

    if (buttnum == 8 && pressed == true && posServo2 < 120) {
      shut();
    }

    if (buttnum == 7 && pressed == true && posServo2 < 120) {
      for (int i = 0; i < 120; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      for (int i = 120; i < 0; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      delay(50);
      for (int i = 0; i < 120; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      delay(50);
      for (int i = 120; i < 0; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      delay(50);
      for (int i = 0; i < 120; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      delay(50);
      for (int i = 120; i < 0; i++)
      {
        myservo1.write(i);
        myservo2.write(i);
        delay(5);
      }
      delay(50);
    }

    if (buttnum == 1 && pressed == true) {
      grinnum = 1;
      load();
      Serial.println("grin num1");
      Serial.println(grinnum);
      analogWrite(5, grinnum);
      //Serial.Write(
      //delay(100);

    }

    if (buttnum == 2 && pressed == true) {
      grinnum = 2;

      
      talk(k%5);
      k++;
      Serial.println("grin num2");
      Serial.println(grinnum);
      analogWrite(5, grinnum);
      //delay(100);
    }

    if (buttnum == 3 && pressed == true) {
      grinnum = 3;
      shout(k%5);
      k++;
      Serial.println("grin num3");
      Serial.println(grinnum);
      analogWrite(5, grinnum);
      //delay(100);
    }


    if (buttnum == 4 && pressed == true) {
      grinnum = 4;
      shut();
      Serial.println("grin num4");
      Serial.println(grinnum);
      analogWrite(5, grinnum);

      mouth.clear();
      eyes.clear();
      //delay(100);
    }

  }

  // GPS Location
  if (packetbuffer[1] == 'L') {
    float lat, lon, alt;
    lat = parsefloat(packetbuffer + 2);
    lon = parsefloat(packetbuffer + 6);
    alt = parsefloat(packetbuffer + 10);
    //    Serial.print("GPS Location\t");
    //    Serial.print("Lat: "); Serial.print(lat, 4); // 4 digits of precision!
    //    Serial.print('\t');
    //    Serial.print("Lon: "); Serial.print(lon, 4); // 4 digits of precision!
    //    Serial.print('\t');
    //    Serial.print(alt, 4); Serial.println(" meters");
  }

  // Accelerometer
  if (packetbuffer[1] == 'A') {
    float x, y, z;
    x = parsefloat(packetbuffer + 2);
    y = parsefloat(packetbuffer + 6);
    z = parsefloat(packetbuffer + 10);
    //    Serial.print("Accel\t");
    //    Serial.print(x); Serial.print('\t');
    //    Serial.print(y); Serial.print('\t');
    //    Serial.print(z); Serial.println();
  }

  // Magnetometer
  if (packetbuffer[1] == 'M') {
    float x, y, z;
    x = parsefloat(packetbuffer + 2);
    y = parsefloat(packetbuffer + 6);
    z = parsefloat(packetbuffer + 10);
    //    Serial.print("Mag\t");
    //    Serial.print(x); Serial.print('\t');
    //    Serial.print(y); Serial.print('\t');
    //    Serial.print(z); Serial.println();
  }

  // Gyroscope
  if (packetbuffer[1] == 'G') {
    float x, y, z;
    x = parsefloat(packetbuffer + 2);
    y = parsefloat(packetbuffer + 6);
    z = parsefloat(packetbuffer + 10);
    //    Serial.print("Gyro\t");
    //    Serial.print(x); Serial.print('\t');
    //    Serial.print(y); Serial.print('\t');
    //    Serial.print(z); Serial.println();
  }

  // Quaternions
  if (packetbuffer[1] == 'Q') {
    float x, y, z, w;
    x = parsefloat(packetbuffer + 2);
    y = parsefloat(packetbuffer + 6);
    z = parsefloat(packetbuffer + 10);
    w = parsefloat(packetbuffer + 14);
    //    Serial.print("Quat\t");
    //    Serial.print(x); Serial.print('\t');
    //    Serial.print(y); Serial.print('\t');
    //    Serial.print(z); Serial.print('\t');
    //    Serial.print(w); Serial.println();
  }

  delay(10);

}

void load() {

  //intial green mouth all

  for (int i = 0; i < 42; i++) {
    mouth.setPixelColor(i, mouth.Color(0, 255, 00));
    mouth.show();
    delay(40);
  }
  for (int j = 0; j < 42; j++) {
    mouth.setPixelColor(j, mouth.Color(0, 0, 00));
    mouth.show();
    delay(40);
  }
  // intil green eyelids

  mouth.setPixelColor(65, mouth.Color(0, 255, 00));
  mouth.setPixelColor(66, mouth.Color(0, 255, 00));
  mouth.setPixelColor(67, mouth.Color(0, 255, 00));
  mouth.setPixelColor(68, mouth.Color(0, 255, 00));
  mouth.setPixelColor(69, mouth.Color(0, 255, 00));
  mouth.setPixelColor(70, mouth.Color(0, 255, 0));
  mouth.setPixelColor(71, mouth.Color(0, 255, 00));
  mouth.setPixelColor(72, mouth.Color(0, 255, 00));

  mouth.setPixelColor(42, mouth.Color(0, 255, 0));
  mouth.setPixelColor(43, mouth.Color(0, 255, 00));
  mouth.setPixelColor(51, mouth.Color(0, 255, 00));
  mouth.setPixelColor(52, mouth.Color(0, 255, 00));
  mouth.setPixelColor(53, mouth.Color(0, 255, 00));
  mouth.setPixelColor(54, mouth.Color(0, 255, 00));
  mouth.setPixelColor(55, mouth.Color(0, 255, 00));
  mouth.setPixelColor(56, mouth.Color(0, 255, 00));
  mouth.setPixelColor(57, mouth.Color(0, 255, 00));
  mouth.show();
  eyes.show();

  // green load sign
  int d = 4;
  while (d > 0) {
    for (int k = 0; k < 5; k++) {
      mouth.setPixelColor(19 + k, mouth.Color(0, 255, 00));
      mouth.show();
      delay(80);
    }
    for (int g = 0; g < 5; g++) {
      mouth.setPixelColor(19 + g, mouth.Color(0, 0, 0));
      mouth.show();
      delay(80);
    }
    d--;
  }

  //white eyes
  for (int o = 59; o < 74; o++) {
    mouth.setPixelColor(o, mouth.Color(5, 10, 5));
    mouth.show();
  }
  for (int p = 42; p < 58; p++) {
    mouth.setPixelColor(p, mouth.Color(5, 10, 5));
  }

  // white line mouth
  for (int kl = 0; kl < 5; kl++) {
    mouth.setPixelColor(19 + kl, mouth.Color(50, 100, 50));
    mouth.show();
    delay(80);
  }

  // LOOK AROUND
  int loop1 = 2;
  while (loop1 > 0) {
    eyes.setPixelColor(3, eyes.Color(0, 0, 0));
    eyes.setPixelColor(10, eyes.Color(0, 0, 0));
    eyes.setPixelColor(0, eyes.Color(255, 255, 255));
    eyes.setPixelColor(7, eyes.Color(255, 255, 255));
    eyes.show();
    mouth.show();
    delay(600);

    eyes.setPixelColor(0, eyes.Color(0, 0, 0));
    eyes.setPixelColor(7, eyes.Color(0, 0, 0));
    eyes.setPixelColor(4, eyes.Color(255, 255, 255));
    eyes.setPixelColor(11, eyes.Color(255, 255, 255));
    eyes.show();
    delay(600);

    eyes.setPixelColor(4, eyes.Color(0, 0, 0));
    eyes.setPixelColor(11, eyes.Color(0, 0, 0));
    eyes.setPixelColor(2, eyes.Color(255, 255, 255));
    eyes.setPixelColor(9, eyes.Color(255, 255, 255));
    eyes.show();
    delay(600);

    eyes.setPixelColor(2, eyes.Color(0, 0, 0));
    eyes.setPixelColor(9, eyes.Color(0, 0, 0));
    eyes.setPixelColor(3, eyes.Color(255, 255, 255));
    eyes.setPixelColor(10, eyes.Color(255, 255, 255));
    eyes.show();
    delay(600);
    loop1--;
  }


  delay(500);
  mouth.clear();
  eyes.clear();


}
void talk (int i) {


  if (i == 0) { //LINE
    mouth.setPixelColor(19, mouth.Color(255, 255, 255));
    mouth.setPixelColor(20, mouth.Color(255, 255, 255));
    mouth.setPixelColor(21, mouth.Color(255, 255, 255));
    mouth.setPixelColor(22, mouth.Color(255, 255, 255));
    mouth.setPixelColor(23, mouth.Color(255, 255, 255));

    mouth.show();
    delay(400);
    mouth.clear();
  }
  else if (i == 2) { //Oh
    mouth.setPixelColor(3, mouth.Color(255, 255, 255));
    mouth.setPixelColor(4, mouth.Color(255, 255, 255));
    mouth.setPixelColor(5, mouth.Color(255, 255, 255));
    mouth.setPixelColor(11, mouth.Color(255, 255, 255));
    mouth.setPixelColor(14, mouth.Color(255, 255, 255));
    mouth.setPixelColor(19, mouth.Color(255, 255, 255));
    mouth.setPixelColor(23, mouth.Color(255, 255, 255));
    mouth.setPixelColor(28, mouth.Color(255, 255, 255));
    mouth.setPixelColor(31, mouth.Color(255, 255, 255));
    mouth.setPixelColor(37, mouth.Color(255, 255, 255));
    mouth.setPixelColor(38, mouth.Color(255, 255, 255));
    mouth.setPixelColor(39, mouth.Color(255, 255, 255));

    mouth.show();
    delay(400);
    mouth.clear();
  }
  else if (i == 3) { //Yuu
    mouth.setPixelColor(4, mouth.Color(255, 255, 255));
    mouth.setPixelColor(12, mouth.Color(255, 255, 255));
    mouth.setPixelColor(13, mouth.Color(255, 255, 255));
    mouth.setPixelColor(20, mouth.Color(255, 255, 255));
    mouth.setPixelColor(22, mouth.Color(255, 255, 255));
    mouth.setPixelColor(29, mouth.Color(255, 255, 255));
    mouth.setPixelColor(30, mouth.Color(255, 255, 255));
    mouth.setPixelColor(38, mouth.Color(255, 255, 255));

    mouth.show();
    delay(400);
    mouth.clear();

  }
  else if (i == 4) { //Yuu

    mouth.setPixelColor(12, mouth.Color(255, 255, 255));
    mouth.setPixelColor(13, mouth.Color(255, 255, 255));
    mouth.setPixelColor(14, mouth.Color(255, 255, 255));
    mouth.setPixelColor(11, mouth.Color(255, 255, 255));
    mouth.setPixelColor(19, mouth.Color(255, 255, 255));
    mouth.setPixelColor(23, mouth.Color(255, 255, 255));
    mouth.setPixelColor(28, mouth.Color(255, 255, 255));
    mouth.setPixelColor(29, mouth.Color(255, 255, 255));
    mouth.setPixelColor(30, mouth.Color(255, 255, 255));
    mouth.setPixelColor(31, mouth.Color(255, 255, 255));

    mouth.show();
    delay(400);
    mouth.clear();

  }

}

void shut() {

  //white eyes
  for (int o1 = 59; o1 < 74; o1++) {
    mouth.setPixelColor(o1, mouth.Color(255, 255, 255));
    mouth.show();
    delay (40);
  }
  for (int p = 42; p < 58; p++) {
    mouth.setPixelColor(p, mouth.Color(255, 255, 255));
    mouth.show();
    delay (40);
  }
  mouth.setPixelColor(3, mouth.Color(255, 255, 255));
  mouth.setPixelColor(4, mouth.Color(255, 255, 255));
  mouth.setPixelColor(5, mouth.Color(255, 255, 255));
  mouth.setPixelColor(11, mouth.Color(255, 255, 255));
  mouth.setPixelColor(14, mouth.Color(255, 255, 255));
  mouth.setPixelColor(19, mouth.Color(255, 255, 255));
  mouth.setPixelColor(23, mouth.Color(255, 255, 255));
  mouth.setPixelColor(28, mouth.Color(255, 255, 255));
  mouth.setPixelColor(31, mouth.Color(255, 255, 255));
  mouth.setPixelColor(37, mouth.Color(255, 255, 255));
  mouth.setPixelColor(38, mouth.Color(255, 255, 255));
  mouth.setPixelColor(39, mouth.Color(255, 255, 255));
  mouth.show();
  delay(100);
  //fade
  for (int o12 = 59; o12 < 74; o12++) {
    mouth.setPixelColor(o12, mouth.Color(0, 200, 50));
    mouth.show();
    delay (20);
  }
  for (int p12 = 42; p12 < 58; p12++) {
    mouth.setPixelColor(p12, mouth.Color(0, 200, 50));
    mouth.show();
    delay (20);
  }
  mouth.setPixelColor(3, mouth.Color(0, 0, 0));
  mouth.setPixelColor(4, mouth.Color(0, 0, 0));
  mouth.setPixelColor(5, mouth.Color(0, 0, 0));
  mouth.setPixelColor(37, mouth.Color(0, 0, 0));
  mouth.setPixelColor(38, mouth.Color(0, 0, 0));
  mouth.setPixelColor(39, mouth.Color(0, 0, 0));

  mouth.setPixelColor(12, mouth.Color(0, 200, 50));
  mouth.setPixelColor(13, mouth.Color(0, 200, 50));
  mouth.setPixelColor(14, mouth.Color(0, 200, 50));
  mouth.setPixelColor(11, mouth.Color(0, 200, 50));
  mouth.setPixelColor(19, mouth.Color(0, 200, 50));
  mouth.setPixelColor(23, mouth.Color(0, 200, 50));
  mouth.setPixelColor(28, mouth.Color(0, 200, 50));
  mouth.setPixelColor(29, mouth.Color(0, 200, 50));
  mouth.setPixelColor(30, mouth.Color(0, 200, 50));
  mouth.setPixelColor(31, mouth.Color(0, 200, 50));
  mouth.show();
  delay (100);


  for (int o2 = 59; o2 < 74; o2++) {
    mouth.setPixelColor(o2, mouth.Color(150, 0, 150));
    mouth.show();
    delay (20);
  }
  for (int p2 = 42; p2 < 58; p2++) {
    mouth.setPixelColor(p2, mouth.Color(150, 0, 150));
    mouth.show();
    delay (20);
  }



  mouth.setPixelColor(14, mouth.Color(0, 0, 0));
  mouth.setPixelColor(11, mouth.Color(0, 0, 0));
  mouth.setPixelColor(19, mouth.Color(0, 0, 0));
  mouth.setPixelColor(23, mouth.Color(0, 0, 0));
  mouth.setPixelColor(28, mouth.Color(0, 0, 0));
  mouth.setPixelColor(31, mouth.Color(0, 0, 0));

  mouth.setPixelColor(4, mouth.Color(150, 0, 150));
  mouth.setPixelColor(12, mouth.Color(150, 0, 150));
  mouth.setPixelColor(13, mouth.Color(150, 0, 150));
  mouth.setPixelColor(20, mouth.Color(150, 0, 150));
  mouth.setPixelColor(22, mouth.Color(150, 0, 150));
  mouth.setPixelColor(29, mouth.Color(150, 0, 150));
  mouth.setPixelColor(30, mouth.Color(150, 0, 150));
  mouth.setPixelColor(38, mouth.Color(150, 0, 150));
  mouth.show();
  delay (100);

  for (int o3 = 59; o3 < 74; o3++) {
    mouth.setPixelColor(o3, mouth.Color(0, 5, 8));
    mouth.show();
    delay (20);
  }
  for (int p3 = 42; p3 < 58; p3++) {
    mouth.setPixelColor(p3, mouth.Color(0, 5, 8));
    mouth.show();
    delay (20);
  }
  mouth.setPixelColor(4, mouth.Color(0, 0, 0));
  mouth.setPixelColor(12, mouth.Color(0, 0, 0));
  mouth.setPixelColor(13, mouth.Color(0, 0, 0));
  mouth.setPixelColor(29, mouth.Color(0, 0, 0));
  mouth.setPixelColor(30, mouth.Color(0, 0, 0));
  mouth.setPixelColor(38, mouth.Color(0, 0, 0));

  mouth.setPixelColor(19, mouth.Color(0, 10, 16));
  mouth.setPixelColor(20, mouth.Color(0, 10, 16));
  mouth.setPixelColor(21, mouth.Color(0, 10, 16));
  mouth.setPixelColor(22, mouth.Color(0, 10, 16));
  mouth.setPixelColor(23, mouth.Color(0, 10, 16));
  mouth.show();
  delay (100);

  for (int o4 = 59; o4 < 74; o4++) {
    mouth.setPixelColor(o4, mouth.Color(00, 00, 00));
    mouth.show();
    delay (20);
  }
  for (int p4 = 42; p4 < 58; p4++) {
    mouth.setPixelColor(p4, mouth.Color(0, 0, 0));
    mouth.show();
    delay (20);
  }

  for (int g = 0; g < 5; g++) {
    mouth.setPixelColor(19 + g, mouth.Color(0, 0, 0));
    mouth.show();
    delay(80);
  }

  for (int gu = 0; gu < 19; gu++) {
    mouth.setPixelColor(gu, eyes.Color(0, 0, 0));
    eyes.show();
  }
  mouth.clear();
  eyes.clear();


}
void shout(int i) {

  if (i == 0) { //LINE

    for (int i = 42; i < 74; i++)
    {
      mouth.setPixelColor(i, mouth.Color(100, 0, 0));
    }
    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
    mouth.setPixelColor(20, mouth.Color(255, 0, 0));
    mouth.setPixelColor(21, mouth.Color(255, 0, 0));
    mouth.setPixelColor(22, mouth.Color(255, 0, 0));
    mouth.setPixelColor(23, mouth.Color(255, 0, 0));

    mouth.show();
    delay(400);
    mouth.clear();
  }
  else if (i == 2) { //Oh

    for (int i = 42; i < 74; i++)
    {
      mouth.setPixelColor(i, mouth.Color(100, 0, 0));
    }
    mouth.setPixelColor(3, mouth.Color(255, 0, 0));
    mouth.setPixelColor(4, mouth.Color(255, 0, 0));
    mouth.setPixelColor(5, mouth.Color(255, 0, 0));
    mouth.setPixelColor(11, mouth.Color(255, 0, 0));
    mouth.setPixelColor(14, mouth.Color(255, 0, 0));
    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
    mouth.setPixelColor(23, mouth.Color(255, 0, 0));
    mouth.setPixelColor(28, mouth.Color(255, 0, 0));
    mouth.setPixelColor(31, mouth.Color(255, 0, 0));
    mouth.setPixelColor(37, mouth.Color(255, 0, 0));
    mouth.setPixelColor(38, mouth.Color(255, 0, 0));
    mouth.setPixelColor(39, mouth.Color(255, 0, 0));

    mouth.show();
    delay(400);
    mouth.clear();
  }
  else if (i == 3) { //Yuu

    for (int i = 42; i < 74; i++)
    {
      mouth.setPixelColor(i, mouth.Color(100, 0, 0));
    }
    mouth.setPixelColor(4, mouth.Color(255, 0, 0));
    mouth.setPixelColor(12, mouth.Color(255, 0, 0));
    mouth.setPixelColor(13, mouth.Color(255, 0, 0));
    mouth.setPixelColor(20, mouth.Color(255, 0, 0));
    mouth.setPixelColor(22, mouth.Color(255, 0, 0));
    mouth.setPixelColor(29, mouth.Color(255, 0, 0));
    mouth.setPixelColor(30, mouth.Color(255, 0, 0));
    mouth.setPixelColor(38, mouth.Color(255, 0, 0));

    mouth.show();
    delay(400);
    mouth.clear();

  }
  else if (i == 4) { //Yuu


    for (int i = 42; i < 74; i++)
    {
      mouth.setPixelColor(i, mouth.Color(100, 0, 0));
    }
    mouth.setPixelColor(12, mouth.Color(255, 0, 0));
    mouth.setPixelColor(13, mouth.Color(255, 0, 0));
    mouth.setPixelColor(14, mouth.Color(255, 0, 0));
    mouth.setPixelColor(11, mouth.Color(255, 0, 0));
    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
    mouth.setPixelColor(23, mouth.Color(255, 0, 0));
    mouth.setPixelColor(28, mouth.Color(255, 0, 0));
    mouth.setPixelColor(29, mouth.Color(255, 0, 0));
    mouth.setPixelColor(30, mouth.Color(255, 0, 0));
    mouth.setPixelColor(31, mouth.Color(255, 0, 0));

    mouth.show();
    delay(400);
    mouth.clear();

  }



  //
  //
  //  mouth.setPixelColor(11, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(12, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(13, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(14, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(19, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(23, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(27, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(32, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(35, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(41, mouth.Color(255, 0, 0));
  //  mouth.show();
  //
  //  int i = 0;
  //  while(i<6){
  //    int speech = random(5);
  //        for (int k = 0; k<18; k++){
  //              int x = random(255);
  //               int v = random(255);
  //             eyes.setPixelColor(k, eyes.Color(50, 255, 0));
  //             eyes.show();
  //             delay(30);
  //             eyes.setPixelColor(k+1, eyes.Color(x,0, v));
  //             eyes.show();
  //             delay(80);
  //         }
  //         //----------------------------------
  //if (i == 0) { //LINE
  //      for (int i=42; i<74; i++)
  //  {
  //    mouth.setPixelColor(i, mouth.Color(100, 0, 0));
  //  }
  //
  //    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(20, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(21, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(22, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(23, mouth.Color(255, 0, 0));
  //
  //    mouth.show();
  //    delay(100);
  //    mouth.clear();
  //  }
  //  else if (i == 2) { //Oh big
  //       for (int i=42; i<74; i++)
  //  {
  //    mouth.setPixelColor(i, mouth.Color(100, 0, 0));
  //  }
  //
  //    mouth.setPixelColor(3, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(4, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(5, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(11, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(14, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(23, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(28, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(31, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(37, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(38, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(39, mouth.Color(255, 0, 0));
  //
  //    mouth.show();
  //    delay(100);
  //    mouth.clear();
  //  }
  //  else if (i == 3) { //Yuu diamond
  //        for (int i=42; i<74; i++)
  //  {
  //    mouth.setPixelColor(i, mouth.Color(100, 0, 0));
  //  }
  //
  //  mouth.setPixelColor(11, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(12, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(13, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(14, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(19, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(23, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(27, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(32, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(35, mouth.Color(255, 0, 0));
  //  mouth.setPixelColor(41, mouth.Color(255, 0, 0));
  //
  //    mouth.show();
  //    delay(100);
  //    mouth.clear();
  //
  //  }
  //  else if (i == 4) { //Yuu eee
  //   for (int i=42; i<74; i++)
  //  {
  //    mouth.setPixelColor(i, mouth.Color(100, 0, 0));
  //  }
  //
  //    mouth.setPixelColor(12, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(13, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(14, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(11, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(19, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(23, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(28, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(29, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(30, mouth.Color(255, 0, 0));
  //    mouth.setPixelColor(31, mouth.Color(255, 0, 0));
  //
  //    mouth.show();
  //    delay(100);
  //    mouth.clear();
  //
  //  }
  //
  //                    //----------------------------------
  //
  //         i++;
  //    }
  //  mouth.clear();
  //  eyes.clear();

}
