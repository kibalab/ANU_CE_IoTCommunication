#include <Arduino.h>

#define USE_TIMER_1     true
#define USE_TIMER_2     true
#include <TimerInterrupt.h>

int LEDInterval = 1000; // 1sec (500ms delayed)
int ThermistorInterval = 1000; // 1sec

int LED_STATE = 0;

void ToggleLED()
{
    LED_STATE = !LED_STATE;
    digitalWrite(13, LED_STATE);
}

double ReadTher()
{
  int raw = analogRead(A0);
  double t = log(((10240000/raw) - 10000));
  t = 1 / (0.001129148 + (0.000234125 * t) + (0.0000000876741 * t * t * t));
  t = t - 273.15;
  return t;
}

void SendSerial()
{
  Serial.println(ReadTher());
}

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  ITimer1.init();
  ITimer1.attachInterruptInterval(LEDInterval/2, ToggleLED);

  ITimer2.init();
  ITimer2.attachInterruptInterval(ThermistorInterval, SendSerial);
}

void loop() {
  if(Serial.available())
  {
    LEDInterval = Serial.readString().toInt();
    ITimer1.attachInterruptInterval(LEDInterval/2, ToggleLED);
  }
}