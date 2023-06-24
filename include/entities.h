#pragma once
#include "graphics.h"

struct Position
{
  int x;
  int y;
};

class Entity
{
public:
  Entity(Position initialPosition) 
    :m_position(initialPosition){};

  Position getPosition(){
    return m_position;
  }

  virtual void draw();
  void move(Position Position);

protected:
  Position m_position;
};

class Paddle : public Entity {
  using Entity::Entity;
public:
  Paddle(Position initialPosition, uint8_t pin)
    : Entity(initialPosition), m_controlPin{ pin } {};
  
  void draw() {
    display.fillRect(m_position.x, map(analogRead(m_controlPin), 0, 1024, 5, 50), 2, 15, WHITE);
  }
private:
  uint8_t m_controlPin;
};

class Ball : public Entity {
  using Entity::Entity;
public:
  void draw() {
    display.fillCircle(m_position.x, m_position.y, 1, WHITE);
  }

  void move(Position position) {
    m_position = position;
  }
};
