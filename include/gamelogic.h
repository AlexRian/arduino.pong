#pragma once

class Gamelogic
{
public:
  void drawUI(){
    display.setCursor(54, 0);
    display.print(m_firstPlayerScore);
    display.setCursor(70, 0);
    display.print(m_secondPlayerScore);   
  }

  void addFirstPlayerScore(){
    m_firstPlayerScore++;
  }

  void addSecondPlayerScore(){
    m_secondPlayerScore++;
  }

private:
  int m_firstPlayerScore = 0;
  int m_secondPlayerScore = 0;
};