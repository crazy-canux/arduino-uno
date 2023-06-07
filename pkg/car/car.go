package car

import (
	"fmt"
	"time"
)

const (
	speedUpperL = 80
	speedLowerL = 80
	speedUpperR = 80
	speedLowerR = 80
)

type MecanumCar struct {
	SDA, SCL int
}

func NewMecanumCar(sda, scl int) *MecanumCar {
	return &MecanumCar{
		SDA: sda,
		SCL: scl,
	}
}

func (mc *MecanumCar) Init() {
	time.Sleep(1 * time.Second)
	mc.rightLED(0)
	mc.leftLED(0)
	mc.Stop()
}

func (mc *MecanumCar) Stop() {
	mc.motorUpperL(0, 0)
	mc.motorLowerL(0, 0)
	mc.motorUpperR(0, 0)
	mc.motorLowerR(0, 0)
}

func (mc *MecanumCar) Advance() {
	mc.motorUpperL(1, speedUpperL)
	mc.motorLowerL(1, speedLowerL)
	mc.motorUpperR(1, speedUpperR)
	mc.motorLowerR(1, speedLowerR)
}

func (mc *MecanumCar) Back() {
	mc.motorUpperL(0, speedUpperL)
	mc.motorLowerL(0, speedLowerL)
	mc.motorUpperR(0, speedUpperR)
	mc.motorLowerR(0, speedLowerR)
}

func (mc *MecanumCar) TurnLeft() {
	mc.motorUpperL(0, speedUpperL)
	mc.motorLowerL(0, speedLowerL)
	mc.motorUpperR(1, speedUpperR)
	mc.motorLowerR(1, speedLowerR)
}

func (mc *MecanumCar) TurnRight() {
	mc.motorUpperL(1, speedUpperL)
	mc.motorLowerL(1, speedLowerL)
	mc.motorUpperR(0, speedUpperR)
	mc.motorLowerR(0, speedLowerR)
}

func (mc *MecanumCar) LMove() {
	mc.motorUpperL(0, speedUpperL)
	mc.motorLowerL(1, speedLowerL)
	mc.motorUpperR(1, speedUpperR)
	mc.motorLowerR(0, speedLowerR)
}

func (mc *MecanumCar) RMove() {
	mc.motorUpperL(1, speedUpperL)
	mc.motorLowerL(0, speedLowerL)
	mc.motorUpperR(0, speedUpperR)
	mc.motorLowerR(1, speedLowerR)
}

func (mc *MecanumCar) LUMove() {
	mc.motorUpperL(0, 0)
	mc.motorLowerL(1, speedLowerL)
	mc.motorUpperR(1, speedUpperR)
	mc.motorLowerR(0, 0)
}

func (mc *MecanumCar) LDMove() {
	mc.motorUpperL(0, speedUpperL)
	mc.motorLowerL(0, 0)
	mc.motorUpperR(0, 0)
	mc.motorLowerR(0, speedLowerR)
}

func (mc *MecanumCar) RUMove() {
	mc.motorUpperL(1, speedUpperL)
	mc.motorLowerL(0, 0)
	mc.motorUpperR(0, 0)
	mc.motorLowerR(1, speedLowerR)
}

func (mc *MecanumCar) RDMove() {
	mc.motorUpperL(0, 0)
	mc.motorLowerL(0, speedLowerL)
	mc.motorUpperR(0, speedUpperR)
	mc.motorLowerR(0, 0)
}

func (mc *MecanumCar) DriftLeft() {
	mc.motorUpperL(0, 0)
	mc.motorLowerL(0, speedLowerL)
	mc.motorUpperR(0, 0)
	mc.motorLowerR(1, speedLowerR)
}

func (mc *MecanumCar) DriftRight() {
	mc.motorUpperL(0, 0)
	mc.motorLowerL(1, speedLowerL)
	mc.motorUpperR(0, 0)
	mc.motorLowerR(0, speedLowerR)
}

func (mc *MecanumCar) MotorUpperL(stateL bool, left1 int) {
	if stateL {
		pwmOut(3, 0)
		pwmOut(4, left1)
	} else {
		pwmOut(3, left1)
		pwmOut(4, 0)
	}
}

func (mc *MecanumCar) MotorLowerL(stateL bool, left1 int) {
	if stateL {
		pwmOut(7, 0)
		pwmOut(8, left1)
	} else {
		pwmOut(7, left1)
		pwmOut(8, 0)
	}
}

func (mc *MecanumCar) MotorUpperR(stateR bool, right1 int) {
	if stateR {
		pwmOut(1, 0)
		pwmOut(2, right1)
	} else {
		pwmOut(1, right1)
		pwmOut(2, 0)
	}
}

func (mc *MecanumCar) MotorLowerR(stateR bool, right1 int) {
	if stateR {
		pwmOut(5, 0)
		pwmOut(6, right1)
	} else {
		pwmOut(5, right1)
		pwmOut(6, 0)
	}
}

func (mc *MecanumCar) RightLED(onoff bool) {
	digitalWriteP55(onoff)
}

func (mc *MecanumCar) LeftLED(onoff bool) {
	digitalWriteP54(onoff)
}

func (mc *MecanumCar) DigitalWriteP55(val bool) {
	writeByte(0x0A, val)
}

func (mc *MecanumCar) DigitalWriteP54(val bool) {
	writeByte(0x09, val)
}

func (mc *MecanumCar) PwmOut(ch, pwm uint8) {
	writeByte(ch, pwm)
}

func (mc *MecanumCar) WriteByte(addr, dat uint8) {
	i2cStart()
	i2cSendByte(0x30 << 1)
	i2cRecvACK()
	i2cSendByte(addr)
	i2cRecvACK()
	i2cSendByte(dat)
	i2cRecvACK()
	i2cStop()
}

func (mc *MecanumCar) I2cStart() {
	digitalWrite(sda, HIGH)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(scl, HIGH)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(sda, LOW)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(scl, LOW)
	time.Sleep(1 * time.Microsecond)
}

func (mc *MecanumCar) I2cStop() {
	digitalWrite(scl, LOW)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(sda, LOW)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(scl, HIGH)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(sda, HIGH)
	time.Sleep(1 * time.Microsecond)
}

func (mc *MecanumCar) I2cSendACK(ack bool) {
	digitalWrite(sda, ack)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(scl, HIGH)
	time.Sleep(1 * time.Microsecond)
	digitalWrite(scl, LOW)
	time.Sleep(1 * time.Microsecond)
}

func (mc *MecanumCar) I2cRecvACK() bool {
	var cy bool
	digitalWrite(scl, LOW)
	//digitalWrite(sda, HIGH) //释放总线，<这里不拉高波形更好。。。>
	pinMode(sda, INPUT) //这里要读取信号，所以数据线设置为INPUT
	digitalWrite(scl, HIGH)
	time.Sleep(1 * time.Microsecond)
	cy = digitalRead(sda)
	digitalWrite(scl, LOW)
	pinMode(sda, OUTPUT) //必须要重新设置输出模式
	return cy
}

func (mc *MecanumCar) I2cSendByte(dat byte) { //dat是要发送的一个字节的数据
	for i := 0; i < 8; i++ { //高位开始传输
		digitalWrite(scl, LOW)
		time.Sleep(1 * time.Microsecond)
		if dat&0x80 != 0 {
			digitalWrite(sda, HIGH) //置1
		} else {
			digitalWrite(sda, LOW) //置0
		}
		dat <<= 1
		time.Sleep(1 * time.Microsecond) //延时
		digitalWrite(scl, HIGH)          //拉高时钟线 读取数据
		time.Sleep(1 * time.Microsecond)
	}
}

func (mc *MecanumCar) I2cRecvByte() byte {
	digitalWrite(sda, HIGH) //释放总线
	var dat byte            //dat是存放接收到的一个字节的数据
	pinMode(sda, INPUT)     //这里要读取信号，所以数据线设置为INPUT
	for i := 0; i < 8; i++ {
		digitalWrite(scl, HIGH)
		time.Sleep(1 * time.Microsecond)
		dat <<= 1
		if digitalRead(sda) != 0 {
			dat++
		}
		time.Sleep(1 * time.Microsecond)
		digitalWrite(scl, LOW)
		time.Sleep(1 * time.Microsecond)
	}
	pinMode(sda, OUTPUT)
	return dat
}
