#include <Arduino.h>
#include <EncButton.h>
#include "graphics.h"
#include "entities.h"
#include "gamelogic.h"

#define POWER_BUTTON_PIN 3
#define FIRST_PLAYER_INPUT_PIN A0
#define SECOND_PLAYER_INPUT_PIN A1

EncButton<EB_TICK, POWER_BUTTON_PIN> powerButton;

Paddle firstPlayerpaddle{Position{2, 0}, FIRST_PLAYER_INPUT_PIN};
Paddle secondPlayerpaddle{Position{126, 0}, SECOND_PLAYER_INPUT_PIN};
Ball ball{Position{64, 32}};
Gamelogic gamelogic;

void setup() {
  Graphics::screenInit();

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  tone(6, 1000);
  delay(500);
  noTone(6);
  delay(500);

  Serial.begin(9600);
}

void loop() {
  if(powerButton.click()){
    Serial.println("Button");
  }
  powerButton.tick();

  display.clearDisplay();

  gamelogic.drawUI();

  firstPlayerpaddle.draw();
  secondPlayerpaddle.draw();
  ball.draw();

  display.display();
}
