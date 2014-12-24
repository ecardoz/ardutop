/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any 
redistribution
*********************************************************************/

/********************************************************************
Modified by Siew Wai Hung - February 2013
http://waihung.net
Display bitmap images on PCD8544 GLCD
Bitmap images are 80 x 45 in size
MSB to LSB Left to Right

Thanks to Adafruit's Library and 
Image2GLCD.exe by Jirawat Kongkaen http://avrportal.com
********************************************************************/

/********************************************************************
Adapted by Edgar Casanova Cardoz - Diciembre 2014
http://idun.com.mx
Display bitmap images on PCD8544 GLCD

********************************************************************/


#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <MemoryFree.h>

const unsigned char PROGMEM idun [] = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x7c,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x7e,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x7e,0x0,0x0,0x1f,0x80,0x1f,0xe0,0x0,0x0,0x0,0x0,
0x7e,0x0,0x0,0x1f,0x80,0x7f,0xfc,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1f,0x81,0xff,0xff,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1f,0x83,0xff,0xff,0x80,0x0,0x0,0x0,
0x78,0x0,0x7c,0x1f,0x87,0xff,0xff,0xc0,0x3,0xf0,0x0,
0x7c,0x1,0xff,0x1f,0x88,0x1f,0xf8,0x20,0x1f,0xfc,0x0,
0x7e,0x3,0xff,0x9f,0x98,0x1f,0xf0,0x30,0x7f,0xff,0x0,
0x7e,0x7,0xff,0xff,0x98,0x1f,0xf0,0x30,0xff,0xff,0x80,
0x7e,0xf,0xff,0xff,0xb8,0x1f,0xf0,0x39,0xff,0xff,0xc0,
0x7e,0x1f,0xf1,0xff,0xb8,0x1f,0xf0,0x39,0xfc,0x1f,0xc0,
0x7e,0x1f,0xc0,0x7f,0xb8,0x1f,0xf0,0x39,0xf8,0xf,0xe0,
0x7e,0x1f,0x80,0x7f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x80,0x3f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x1f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xf8,0x1f,0xf0,0x3f,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xb8,0x1f,0xf0,0x3b,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0xb8,0x1f,0xf0,0x3b,0xf0,0x7,0xe0,
0x7e,0x3f,0x0,0x3f,0x38,0x1f,0xe0,0x33,0xf0,0x7,0xe0,
0x7e,0x1f,0x80,0x3f,0x18,0x1f,0xf0,0x33,0xf0,0x7,0xe0,
0x7e,0x1f,0xc0,0x7f,0x8,0xf,0xe0,0x63,0xf0,0x7,0xe0,
0x7e,0x1f,0xe1,0xfe,0xc,0x7,0x80,0x63,0xf0,0x7,0xe0,
0x7e,0xf,0xff,0xfe,0x4,0x0,0x0,0xc3,0xf0,0x7,0xe0,
0x7e,0xf,0xff,0xfc,0x2,0x0,0x0,0x83,0xf0,0x7,0xe0,
0x7e,0x7,0xff,0xf8,0x1,0x0,0x1,0x3,0xf0,0x7,0xe0,
0x7e,0x1,0xff,0xe0,0x0,0xc0,0x6,0x3,0xf0,0x3,0xe0,
0x0,0x0,0x3f,0x0,0x0,0x3f,0xf8,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0  
};

// Please use a level shifter (ex. 74HC4050) 
//  if you're using a 5V Arduino
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 3, 4);

int potPin = 5;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int led = 9;       // led azul del LCD

void setup()   {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
  display.begin();

  pinMode(2, INPUT);
  
  for(int i=0; i<=50; i++){
    display.setContrast(i);
    delay(5);
  }
  
  screensplash();
  display.setContrast(50);
  analogWrite(led,250);  
}


void loop() {
  int sizeStream = 20;
  char stream[sizeStream];
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  if(Serial.available()){
    delay(10);
    Serial.readBytes(stream, sizeStream);
    //Serial.println(stream);
    Serial.flush();
    monitorBase();
    
    printCpuPercent(35, 0, stream[0],  stream[1],  stream[2]);
    //display.fillRect(60, 0,  20, 7, WHITE);    
    drawBar(stream[0],  stream[1],  stream[2],  0);
    
    printCpuPercent(35, 8, stream[3],  stream[4],  stream[5]);
    //display.fillRect(60, 8,  20, 7, WHITE);
    drawBar(stream[3],  stream[4],  stream[5],  8);
    
    printCpuPercent(35, 16, stream[6],  stream[7],  stream[8]);
    //display.fillRect(60, 16,  20, 7, WHITE);
    drawBar(stream[6],  stream[7],  stream[8],  16);
    
    printCpuPercent(35, 24, stream[9],  stream[10], stream[11]);
    //display.fillRect(60, 24,  20, 7, WHITE);
    drawBar(stream[9],  stream[10], stream[11], 24);    
    
    printMem(35, 32, stream[12], stream[13], stream[14], stream[15]);
    printMem(35, 40, stream[16], stream[17], stream[18], stream[19]);
    
    display.display();
    Serial.end();    
    Serial.begin(9600);
  }
  int p = analogRead(potPin);
  analogWrite(led,p/5);
  
}

void drawBar(char b1, char b2, char b3, int inicio_barra){
  char buffer[4];
  buffer[0] = b1;
  buffer[1] = b2;
  buffer[2] = b3;
  buffer[3] = '\0';
  int b = atoi(buffer);
  b = b/5;
  display.fillRect(60, inicio_barra,  b, 7, BLACK);
}

void screensplash(){
  int b = 1;
  display.clearDisplay();
  display.drawBitmap(0, 0, idun, 84, 48, BLACK);
  display.display();
  delay(500);
  display.clearDisplay();
}

void printCpuPercent(int x, int y, char b1, char b2, char b3){
  char buffer[4];
  buffer[0] = b1;
  buffer[1] = b2;
  buffer[2] = b3;
  buffer[3] = '\0';
  display.setTextSize(1);
  display.setCursor(x, y);
  display.println(buffer);
}

void printMem(int x, int y, char b1, char b2, char b3, char b4){
  char buffer[5];
  buffer[0] = b1;
  buffer[1] = b2;
  buffer[2] = b3;
  buffer[3] = b4;
  buffer[4] = '\0';
  display.setTextSize(1);
  display.setCursor(x, y);
  display.println(buffer);
}

void monitorBase(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("CPU 0:   %\nCPU 1:   %\nCPU 2:   %\nCPU 3:   %\nuRAM:     MB\nfRAM:     MB");
  display.display();
}
