#include <Arduino.h>
#include <mozzi_midi.h>

#define PENTATONIC_NOTES 54

// provides an index of pentatonic notes in the midi note table

unsigned char sPentatonicNotes[PENTATONIC_NOTES] =
{
  0,   2,  4,  7,  9, 
  12, 14, 16, 19, 21, 
  24, 26, 28, 31, 33,
  36, 38, 40, 43, 45,
  48, 50, 52, 55, 57,
  60, 62, 64, 67, 69,
  72, 74, 76, 79, 81,
  84, 86, 88, 91, 93,
  96, 98,100,103,105,
 108,110,112,115,117,
 120,122,124,127 
};

int ledPins[] = {LED_BUILTIN,A0,A1,A2,A3,A4,A5,DD5};

void dispBinary(byte n)
{
  for (byte i = 0; i < 8; i++) {
    bool active = n & 1;
    analogWrite(ledPins[i], active? 1024/2 : 0);
    n /= 2;
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for(int i=0; i < 8; i++){
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(8, OUTPUT);
}
int number = 0;
void loop() {
  static bool goingUp = true;
  int change = 0;
  if(goingUp){
    change = random(-1, 5);
  }else{
    change = random(-5, 1);
  }

  number += change > 0 ? 1 : -1;
  if(number > PENTATONIC_NOTES){
    number=PENTATONIC_NOTES-1;
    goingUp = false;
  }
  else if(number < 0){
    number=0;
    goingUp = true;
  }
  Serial.println(number);
  tone(8, mtof(sPentatonicNotes[number]));
  // put your main code here, to run repeatedly:
  dispBinary(number);
  delay(250);
}