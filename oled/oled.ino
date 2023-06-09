#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {

  Serial.begin(9600);
  Serial.println("setup...");

// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
display.begin(SSD1306_SWITCHCAPVCC, 0x3D); // initialize with the I2C addr 0x3D (for the 128x64)
// init done

// Show image buffer on the display hardware.
// Since the buffer is intialized with an Adafruit splashscreen
// internally, this will display the splashscreen.
display.display();
delay(2000);

// Clear the buffer.
display.clearDisplay();
}

void loop() {
Serial.println("loop...");
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("Hello");
display.setTextSize(2);
display.println("HEC-2023");
display.display();
delay(250);
}
