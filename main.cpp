#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN PA0
#define ECHO_PIN PA1

float distance;

float measureDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if(duration==0)
        return -1;

    return duration * 0.0343 / 2.0;
}

void setup()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    Serial.begin(115200);

    display.setTextSize(2);
    display.setCursor(10,20);
    display.println("START");
    display.display();

    delay(1500);
}

void loop()
{
    distance = measureDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Ultrasonic Sensor");

    display.drawLine(0,12,128,12,SSD1306_WHITE);

    display.setTextSize(2);
    display.setCursor(5,30);

    if(distance<0)
    {
        display.print("No Echo");
    }
    else
    {
        display.print(distance,1);
        display.print(" cm");
    }

    display.display();

    delay(100);
}