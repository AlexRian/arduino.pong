#pragma once
#include "graphics.h"

struct Vector
{
  int x;
  int y;
};

class Entity
{
public:
  Entity(Vector initialPosition) 
    :m_position(initialPosition){};

  Vector getPosition(){
    return m_position;
  }

  virtual void draw();
  void move(Vector Position);

protected:
  Vector m_position;
};

class Paddle : public Entity {
  using Entity::Entity;
public:
  Paddle(Vector initialPosition, uint8_t pin)
    : Entity(initialPosition), m_controlPin{ pin } {};
  
  void draw() {
    m_position.y = map(analogRead(m_controlPin), 0, 1024, 5, 50);
    display.fillRect(m_position.x, m_position.y, 2, 15, WHITE);
  }
private:
  uint8_t m_controlPin;
};

class Ball : public Entity {
  using Entity::Entity;
private:
  Vector m_velocity = {1, 0};
public:
  void draw() {
    display.fillCircle(m_position.x, m_position.y, 1, WHITE);
  }

  void checkCollisions(Paddle& firstPlayerpaddle, Paddle& secondPlayerpaddle) {
    Serial.println(abs(secondPlayerpaddle.getPosition().y - m_position.y));

    if (abs(secondPlayerpaddle.getPosition().x - m_position.x) < 2) {
      if(abs(secondPlayerpaddle.getPosition().y - m_position.y) < 5){
        m_velocity = {m_velocity.x * -1, m_velocity.y - 1};
      }else if(abs(secondPlayerpaddle.getPosition().y - m_position.y) > 5 && abs(secondPlayerpaddle.getPosition().y - m_position.y) < 10){
        m_velocity = {m_velocity.x * -1, m_velocity.y};
      }else if(abs(secondPlayerpaddle.getPosition().y - m_position.y) > 10 && abs(secondPlayerpaddle.getPosition().y - m_position.y) < 15){
        m_velocity = {m_velocity.x * -1, m_velocity.y + 1};
      }
    }

    if (abs(firstPlayerpaddle.getPosition().x - m_position.x) < 2) {
      if(abs(firstPlayerpaddle.getPosition().y - m_position.y) < 5){
        m_velocity = {m_velocity.x * -1, m_velocity.y - 1};
      }else if(abs(firstPlayerpaddle.getPosition().y - m_position.y) > 5 && abs(firstPlayerpaddle.getPosition().y - m_position.y) < 10){
        m_velocity = {m_velocity.x * -1, m_velocity.y};
      }else if(abs(firstPlayerpaddle.getPosition().y - m_position.y) > 10 && abs(firstPlayerpaddle.getPosition().y - m_position.y) < 15){
        m_velocity = {m_velocity.x * -1, m_velocity.y + 1};
      }
    }

    if(m_position.y < 2 || m_position.y > 62){
      m_velocity = {m_velocity.x, m_velocity.y * -1};
    }
  }

  void updatePosition() {
    m_position = {m_position.x += m_velocity.x, m_position.y += m_velocity.y};
  }
};
