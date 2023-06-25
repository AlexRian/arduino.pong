#pragma once

class Sound
{
public:
  Sound(int speakerPin) 
    :m_speakerPin(speakerPin){};

  void makeReadyBeep(){
    tone(m_speakerPin, 1000);
    delay(500);
    noTone(m_speakerPin);
    delay(500);
  }

  void makeGoalBeep(){
    tone(m_speakerPin, 1500);
    delay(500);
    noTone(m_speakerPin);
    delay(500);
  }
private:
  int m_speakerPin;
};