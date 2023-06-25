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

  Vector setPosition(Vector position){
    m_position = position;
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

  Vector getVelocity(){
    return m_velocity;
  }

  Vector setVelocity(Vector velocity){
    m_velocity = velocity;
  }

  void draw() {
    display.fillCircle(m_position.x, m_position.y, 1, WHITE);
  }

  void updatePosition() {
    m_position = {m_position.x += m_velocity.x, m_position.y += m_velocity.y};
  }
};
