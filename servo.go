package main

import (
	"machine"
	"time"
)

func main() {
	pin := machine.PB1
	pin.Configure(machine.PinConfig{Mode: machine.PinInput})

	for angle := uint8(0); angle < 180; angle++ {
		servoPulse(pin, angle)
	}

	for angle := uint8(180); angle > 0; angle-- {
		servoPulse(pin, angle)
	}
}

func servoPulse(pin machine.Pin, myangle uint8) {
	pulsewidth := mapValue(int(myangle), 0, 180, 500, 2500)

	pin.High()
	time.Sleep(time.Duration(pulsewidth) * time.Microsecond)
	pin.Low()
	time.Sleep(time.Duration(20-pulsewidth/1000) * time.Millisecond)
}

func mapValue(x, inMin, inMax, outMin, outMax int) int {
	return (x-inMin)*(outMax-outMin)/(inMax-inMin) + outMin
}
