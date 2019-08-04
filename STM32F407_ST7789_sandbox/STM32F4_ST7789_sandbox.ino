/* 
 * Board Managaer package: STM32 Cores by STMicroelectronics
 * Board: Generic STM32F4 series
 * Board part number: Black F407VE
 * TFT library: https://github.com/ananevilya/Arduino-ST7789-Library
 * 
 * Based on the graphicstest.ino included in the library
 * By LouD - 2019
 * 
 */

#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include <stdarg.h>

#define TFT_DC    PE10 // SPI data / command selection pin
#define TFT_RST   PE8 // reset pin

Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST); // Hardware SPI (PB3 (SCK), PB5(MOSI) no CS pin)

#define LED0 PA6 // initialize led 0 pin
#define LED1 PA7 // initialize led 1 pin

const unsigned long led0interval = 150; // blink interval for led 0
const unsigned long led1interval = 250; // blink interval for led 1
unsigned long led0timer; // led0 number storage
unsigned long led1timer; // led1 number storage

const unsigned long tftinterval = 2500; // led refresh interval
unsigned long tfttimer; // tft number storage

unsigned long textcounter;
unsigned long previouscounts;

void setup() {
  Serial.begin(9600); // start serial port
  Serial.println("\n\rStarting ST7789 TFT");  
  SPI.begin(); // start SPI

  tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels

  uint16_t time = millis();
  //tft.fillScreen(BLACK); // fill tft background 
  time = millis() - time;
  serialprint2("Initialized in %d milliseconds", time);
  Serial.println();

  // initialize timers
  tfttimer = millis();
  led0timer = millis();
  led1timer = millis();

  textcounter = 0;
  previouscounts = 0;

  //initialize leds
  pinMode(LED0, OUTPUT); // set led 0 pin to output
  pinMode(LED1, OUTPUT); // set led 1 pin to output
}


void loop() {

  if ( (millis () - led0timer) >= led0interval)
    blinker0 ();

  if ( (millis () - led1timer) >= led1interval)
    blinker1 ();

  if ( (millis () - tfttimer) >= tftinterval) {
      if (textcounter == previouscounts) {
        Serial.println("tfttext before ++");
        Serial.println(textcounter);
        Serial.println(previouscounts);
        tfttext ();
        textcounter++;
        Serial.println("tfttext after ++");
        Serial.println(textcounter);
        Serial.println(previouscounts);
      } else {
        Serial.println("iloveyou before ==");
        Serial.println(textcounter);
        Serial.println(previouscounts);
        iloveyou ();
        previouscounts = textcounter;
        Serial.println("iloveyou after ==");
        Serial.println(textcounter);
        Serial.println(previouscounts);
      }
  }
}

void blinker0() {
  if (digitalRead (LED0) == LOW)
    digitalWrite (LED0, HIGH);
  else
    digitalWrite (LED0, LOW);
  led0timer = millis();
}

void blinker1() {
  if (digitalRead (LED1) == LOW)
    digitalWrite (LED1, HIGH);
  else
    digitalWrite (LED1, LOW);
  led1timer = millis();
}

void tfttext() {
  tft.fillScreen(0xFFC0CB);
  tft.setTextWrap(false);
  tft.setTextSize(7);
  tft.setTextColor(WHITE);
  tft.setCursor(15,30);
  tft.print("LIEVE");
  tft.setCursor(15,86);
  tft.print("KITTY");
  //tft.print(8675309, HEX);
  tfttimer = millis();
}

void iloveyou() {
  tft.fillScreen(0xFFC0CB);
  tft.setTextWrap(false);
  tft.setTextSize(7);
  tft.setTextColor(WHITE);
  tft.setCursor(99,30);
  tft.print("I");
  tft.setCursor(36,86);
  tft.print("LOVE");
  tft.setCursor(57,142);
  tft.print("YOU");
  tfttimer = millis();
}

void serialprint2(char *format,...) // credits go to unknown on the Arduino forum
{
 char buff[128];
 va_list args;
 va_start (args,format);
 vsnprintf(buff,sizeof(buff),format,args);
 va_end (args);
 buff[sizeof(buff)/sizeof(buff[0])-1]='\0';
 Serial.print(buff);
}
