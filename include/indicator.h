#pragma once
#include <Arduino.h>

class Indicator
{
public:
  Indicator(int firstPlayerLedPin, int secondPlayerLedPin) 
    :m_firstPlayerLedPin(firstPlayerLedPin), m_secondPlayerLedPin(secondPlayerLedPin){};

  void init(){
    pinMode(m_firstPlayerLedPin, OUTPUT);
    pinMode(m_secondPlayerLedPin, OUTPUT);
  }

  void activateFirstPlayerLed(){
    digitalWrite(m_firstPlayerLedPin, HIGH);
  }

  void deactivateFirstPlayerLed(){
    digitalWrite(m_firstPlayerLedPin, LOW);
  }

  void activateSecondPlayerLed(){
    digitalWrite(m_secondPlayerLedPin, HIGH);
  }

  void deactivateSecondPlayerLed(){
    digitalWrite(m_secondPlayerLedPin, LOW);
  }

private:
  int m_firstPlayerLedPin;
  int m_secondPlayerLedPin;
};