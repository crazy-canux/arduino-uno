package main

import (
	"arduino-uno/pkg/car"
	"time"
)

func setup() {
	MecanumCar.Init() //初始化电机与七彩灯驱动
}

func loop() {
	mecanumCar.rightLED(true) //开启右边七彩灯闪烁
	mecanumCar.leftLED(true)  //开启左边七彩灯闪烁
	time.Sleep(3 * time.Second)
	mecanumCar.rightLED(false) //关闭右边七彩灯闪烁
	mecanumCar.leftLED(false)  //关闭左边七彩灯闪烁
	mecanumCar.Advance()       //前进
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.Back() //后退
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.TurnLeft() //左转
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.TurnRight() //右转
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.LMove() //左平移
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.RMove() //右平移
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.LUMove() //左上
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.LDMove() //左下
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.RUMove() //右上
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.RDMove() //右下
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.driftLeft() //左漂移
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
	mecanumCar.driftRight() //右漂移
	time.Sleep(3 * time.Second)
	mecanumCar.Stop() //停止
	time.Sleep(1 * time.Second)
}
