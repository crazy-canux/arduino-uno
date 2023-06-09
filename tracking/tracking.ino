
#include "MecanumCar_v4.h"
// #include <Wire.h>
// #include "Adafruit_TCS34725.h"
#include "Adafruit_NeoPixel.h"     //Library file

mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2


// tcs
// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);


// rgb
#define PIN A5                        // Define the pins of the RGB light
#define MAX_LED 8                   //8 RGB light

Adafruit_NeoPixel strip = Adafruit_NeoPixel( MAX_LED, PIN, NEO_RGB + NEO_KHZ800 );
uint8_t i = 0;                            
uint32_t color = strip.Color(0,255,255);   //绿、红、蓝


//循迹红外引脚定义
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      A2                  A1                  A3                   A4
const int TrackSensorLeftPin1  =  A0;  //定义左边第一个循迹红外传感器引脚为A2
const int TrackSensorLeftPin2  =  A1;  //定义左边第二个循迹红外传感器引脚为A1
const int TrackSensorRightPin1 =  A4;  //定义右边第一个循迹红外传感器引脚为A3
const int TrackSensorRightPin2 =  A2;  //定义右边第二个循迹红外传感器引脚为A4

//定义各个循迹红外引脚采集的数据的变量
int TrackSensorLeftValue1;
int TrackSensorLeftValue2;
int TrackSensorRightValue1;
int TrackSensorRightValue2;


void setup()
{
  Serial.begin(9600);
  Serial.println("setup ......");

  // if (tcs.begin()) {
  //   Serial.println("Found tcs sensor");
  // } else {
  //   Serial.println("No TCS34725 found ... check your connections");
  //   while (1);
  // }

  strip.begin();  
  strip.show();     

  //定义四路循迹红外传感器为输入接口
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);

  //四路循迹红外传感器初始化为高电平
  digitalWrite(TrackSensorLeftPin1, HIGH);
  digitalWrite(TrackSensorLeftPin2, HIGH);
  digitalWrite(TrackSensorRightPin1, HIGH);
  digitalWrite(TrackSensorRightPin2, HIGH);

  mecanumCar.Init();  //初始化麦轮车驱动
}

void loop()
{
  Serial.println("loop......");

  for(i=0;i<MAX_LED;i++)   //设置i的值控制点亮灯的序号
  {
    strip.setPixelColor(i,color); 
  }  
  strip.show();  

  // uint16_t red, green, blue, c, colorTemp, lux;
  // tcs.getRawData(&red, &green, &blue, &c);
  // // Figure out some basic hex code for visualization
  // uint32_t sum = c;
  // int r, g, b;
  // r = red; r /= sum;
  // g = green; g /= sum;
  // b = blue; b /= sum;
  // r *= 256; g *= 256; b *= 256;

  // int r1, g1, b1;
  
  // if (!(r<30 && g<30 && b<30) || !(r>220 && g>220 && b>220)){
  //   if (r < 30){
  //     r1=0;
  //   } else if(r > 230){
  //     r1=255;
  //   } else{
  //     r1=204;
  //   }

  //   if (g < 25){
  //     g1=0;
  //   } else if(g >= 25 && g < 75){
  //     g1=51;
  //   } else if(g >= 75 && g < 140) {
  //     g1=102;
  //   } else {
  //     g1=204;
  //   }
 
  //   if (b < 25){
  //     b1=0;
  //   } else if(b >= 25 && b < 100){
  //     b1=51;
  //   } else if(b >= 100 && b < 225) {
  //     b1=204;
  //   } else {
  //     b1=255;
  //   }
  
  //   uint32_t colored = strip.Color(r1,g1,b1);
  //   Serial.println(colored);

  //   for(i=0;i<MAX_LED;i++)   //设置i的值控制点亮灯的序号
  //   {
  //     strip.setPixelColor(i, colored);  //点亮所有RGB灯为蓝色
  //   }
  //   strip.show();

  // }


  //检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
  //未检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
  TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
  TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
  TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
  TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
  Serial.println(TrackSensorLeftValue1);
  Serial.println(TrackSensorLeftValue2);
  Serial.println(TrackSensorRightValue1);
  Serial.println(TrackSensorRightValue2);
  
  //turn right
  //  1100, 1110, 
  if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue2 == LOW) 
  {
    Serial.println("right");
    mecanumCar.Turn_Right(30, 30, 30, 30); //右转
    delay(100);
  }
  // //1010???
  // if ((TrackSensorLeftValue1 == HIGH &&  TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == LOW))
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }
  // //1000
  // else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW)
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }
  // // 0110, ,  0100?    0101?    
  // else if ((TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW) || (TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue2 == LOW))
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }
  // //0010???    
  // else if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH  && TrackSensorRightValue2 == LOW)
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }
  // // 0000
  // else if (TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW) 
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }
  // // 1111
  // else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  // {
  //   Serial.println("right");
  //   mecanumCar.Turn_Right(30, 30, 30, 30); //右转
  //   delay(100);
  // }


  // // turn left
  // // 0011    0111       0010???     
  // else if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  // {
  //   Serial.println("left");
  //   mecanumCar.Turn_Left(30, 30, 30, 30); // 右转
  //   delay(100);
  // }
  // // 1011   1010???  
  // else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  // {
  //   Serial.println("left");
  //   mecanumCar.Turn_Left(30, 30, 30, 30); // 右转
  //   delay(100);
  // }

  //四路循迹引脚电平状态
  // 0001 , 1001, 0000, 1000
  //处理直线
  else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW)
  {
    Serial.println("go go go");
    mecanumCar.Advance(40, 40, 40, 40);
    delay(100);
  }
}


