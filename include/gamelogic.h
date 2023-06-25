#pragma once
#include "sound.h"
#include "indicator.h"

class Gamelogic
{
public:
  Gamelogic(Sound& sound, Indicator& indicator) 
    :m_sound(sound), m_indicator(indicator){};
  
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

  void returnBallToInitialPosition(Ball& ball){
    ball.setVelocity({0,0});
    ball.setPosition({64, 32});
    delay(1000);
    ball.setVelocity({1,0});
  }

  void checkCollisions(Paddle& firstPlayerpaddle, Paddle& secondPlayerpaddle, Ball& ball) {
    Serial.println(abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y));

    if (abs(secondPlayerpaddle.getPosition().x - ball.getPosition().x) < 2) {
      if(abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y) < 5){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y - 1});
      }else if(abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y) > 5 && abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y) < 10){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y});
      }else if(abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y) > 10 && abs(secondPlayerpaddle.getPosition().y - ball.getPosition().y) < 15){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y + 1});
      }
    }

    if (abs(firstPlayerpaddle.getPosition().x - ball.getPosition().x) < 2) {
      if(abs(firstPlayerpaddle.getPosition().y - ball.getPosition().y) < 5){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y - 1});
      }else if(abs(firstPlayerpaddle.getPosition().y - ball.getPosition().y) > 5 && abs(firstPlayerpaddle.getPosition().y - ball.getPosition().y) < 10){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y});
      }else if(abs(firstPlayerpaddle.getPosition().y - ball.getPosition().y) > 10 && abs(firstPlayerpaddle.getPosition().y - ball.getPosition().y) < 15){
        ball.setVelocity({ball.getVelocity().x * -1, ball.getVelocity().y + 1});
      }
    }

    if(ball.getPosition().y < 2 || ball.getPosition().y > 62){
      ball.setVelocity({ball.getVelocity().x, ball.getVelocity().y * -1});
    }

    if(ball.getPosition().x < -10){
      m_indicator.activateSecondPlayerLed();
      m_sound.makeGoalBeep();
      addSecondPlayerScore();
      returnBallToInitialPosition(ball);
      m_indicator.deactivateSecondPlayerLed();
    }

    if(ball.getPosition().x > 135){
      m_indicator.activateFirstPlayerLed();
      m_sound.makeGoalBeep();
      addFirstPlayerScore();
      returnBallToInitialPosition(ball);
      m_indicator.deactivateFirstPlayerLed();
    }

  }

private:
  int m_firstPlayerScore = 0;
  int m_secondPlayerScore = 0;
  Sound& m_sound;
  Indicator& m_indicator;
};