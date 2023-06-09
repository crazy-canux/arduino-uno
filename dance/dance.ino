
#include "MecanumCar_v4.h"
#include <Wire.h>
#include "Adafruit_NeoPixel.h"     //Library file

mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2


// rgb
#define PIN A1                        // Define the pins of the RGB light
#define MAX_LED 8                   //8 RGB light

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );


void setup()
{
  Serial.begin(9600);
  Serial.println("setup ......");

  strip.begin();  
  strip.show();     

  mecanumCar.Init();  //初始化麦轮车驱动
}

void RGB_Light(int i, int R, int G, int B)
{
  Serial.println("light on......");
  uint32_t color = strip.Color(G, R, B);
  strip.setPixelColor(i, color);
  strip.show();
}

void RGB_OFF()
{ 
  Serial.println("light off......");
  uint8_t i = 0;
  uint32_t color = strip.Color(0, 0, 0);
  for(i=0;i<MAX_LED;i++)   
  {
    strip.setPixelColor(i, color);  
  }
  strip.show();
}

void loop()
{
  Serial.println("loop......");

  // 直行加速
  RGB_Light(0, 255, 64, 64);
  mecanumCar.Advance(255, 255, 255, 255);
  delay(500);
  RGB_OFF();

  RGB_Light(1, 255, 165, 0);
  mecanumCar.Back(255, 255, 255, 255);
  delay(500);
  RGB_OFF();

  RGB_Light(2, 138, 255, 64);
  mecanumCar.Turn_Left(255, 255, 255, 255);
  delay(500);
  RGB_OFF();

  RGB_Light(3, 64, 255, 184);
  mecanumCar.Turn_Right(255, 255, 255, 255);
  delay(500);
  RGB_OFF();

  RGB_Light(4, 64, 174, 255);
  mecanumCar.L_Move(255, 255, 255, 255);
  delay(500);
  mecanumCar.R_Move(255, 255, 255, 255);
  delay(500);
  RGB_OFF();

  RGB_Light(5, 126, 64, 255);
  mecanumCar.LU_Move();
  delay(500);
  mecanumCar.LD_Move();
  delay(500);
  RGB_OFF();

  RGB_Light(6, 255, 64, 255);
  mecanumCar.RU_Move();
  delay(500);
  mecanumCar.RD_Move();
  delay(500);
  RGB_OFF();

  RGB_Light(7, 187, 132, 168);
  mecanumCar.drift_left();
  delay(500);
  mecanumCar.drift_right();
  delay(500);
  RGB_OFF();
}


