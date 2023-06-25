#include <Arduino.h>
#include <EncButton.h>
#include "graphics.h"
#include "entities.h"
#include "gamelogic.h"
#include "sound.h"
#include "indicator.h"

#define POWER_BUTTON_PIN 3
#define FIRST_PLAYER_INPUT_PIN A0
#define SECOND_PLAYER_INPUT_PIN A1

EncButton<EB_TICK, POWER_BUTTON_PIN> powerButton;

Paddle firstPlayerpaddle{{2, 0}, FIRST_PLAYER_INPUT_PIN};
Paddle secondPlayerpaddle{{126, 0}, SECOND_PLAYER_INPUT_PIN};
Ball ball{{64, 32}};
Sound sound(6);
Indicator indicator(7, 8);

Gamelogic gamelogic(sound, indicator);

void setup() {
  Graphics::screenInit();
  sound.makeReadyBeep();

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

  ball.updatePosition();
  gamelogic.checkCollisions(firstPlayerpaddle, secondPlayerpaddle, ball);
  ball.draw();

  display.display();
}
