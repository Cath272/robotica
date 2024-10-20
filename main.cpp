#include <Arduino.h>

#define led1 10
#define led2 9
#define led3 8
#define led4 7

#define red 4
#define green 5
#define blue 6

// blink button
#define btn2 3
// stop button
#define btn1 2

// Variables will change:
int ledbuttonState = LOW;   // the current state of the output pin
int buttonState;            // the current reading from the input pin
int lastButtonState = HIGH; // the previous reading from the input pin

int StopState = LOW;            // the current state of the output pin
int StopbuttonState;            // the current reading from the input pin
int StoplastButtonState = HIGH; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;
unsigned long StoplastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelayStop = 1000;

int ledState = LOW; // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated

// constants won't change:
const long interval = 500;

int i = 0;
int ledNum = 10;

// function that stops the charging and blinks 3 times
void chargingStop()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    delay(400);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    delay(400);
  }
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  ledbuttonState = HIGH;
  ledNum = 10;
}

void setup()
{
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  digitalWrite(red, LOW);
}

void loop()
{
  // reads the states of the 2 buttons every loop
  int reading = digitalRead(btn1);
  int stop = digitalRead(btn2);

  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH)
      {
        ledbuttonState = !ledbuttonState;
      }
    }
  }

  if (stop != StoplastButtonState)
  {
    // reset the debouncing timer
    StoplastDebounceTime = millis();
  }

  if ((millis() - StoplastDebounceTime) > debounceDelayStop)
  {

    if (stop != StopbuttonState)
    {
      StopbuttonState = stop;

      if (StopbuttonState == HIGH)
      {
        StopState = !StopState;

        chargingStop();
      }
    }
  }

  // start the charging cycle
  if (!ledbuttonState)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    if (millis() - previousMillis >= interval)
    {
      // save the last time you blinked the LED
      previousMillis = millis();

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW)
      {
        ledState = HIGH;
      }
      else
      {
        ledState = LOW;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(ledNum, ledState);

      //cycles the leds from pin 10 to pin 7, blinking them eatch for 3s
      if (ledState)
      {

        i++;
        if (i == 3)
        {
          i = 0;
          ledNum--;
          if (ledNum == 6)
          {
            chargingStop();
          }
        }
      }
    }
  }
  else
  {
    digitalWrite(red, LOW);
    digitalWrite(7, LOW);
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  StoplastButtonState = stop;
}
