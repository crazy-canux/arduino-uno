
#include "MecanumCar_v4.h"
mecanumCar mecanumCar(3, 2);  //sda-->D3,scl-->D2

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
  //  1100, 1110, 1101?  
  if ((TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue2 == LOW) || (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW))
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }
  //1010???
  if ((TrackSensorLeftValue1 == HIGH &&  TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == LOW))
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }
  //1000
  else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW)
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }
  // 0110, ,  0100?    0101?    
  else if ((TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW) || (TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue2 == LOW))
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }
  //0010???    
  else if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH  && TrackSensorRightValue2 == LOW)
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }
  // 0000
  else if (TrackSensorLeftValue1 == LOW && TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == LOW) 
  {
    Serial.println("right");
    mecanumCar.Turn_Right(15, 15, 15, 15); //右转
  }

  // turn left
  // 0011    0111       0010???     
  else if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  {
    Serial.println("left");
    mecanumCar.Turn_Left(15, 15, 15, 15); // 右转
  }
  // 1011   1010???  
  else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  {
    Serial.println("left");
    mecanumCar.Turn_Left(15, 15, 15, 15); // 右转
  }

  //四路循迹引脚电平状态
  // 0001 , 1001,
  //处理直线
  else if (TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == LOW && TrackSensorRightValue2 == HIGH)
  {
    Serial.println("go go go");
    mecanumCar.Advance(30, 30, 30, 30);
  }
  // 1111
  // else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == HIGH)
  // {
  //   Serial.println("stop");
  //   mecanumCar.Stop();
  // }
}


