#include "Pin.h"
#include "ShiftRegister.h"
#include "LedMatrix.h"
#include "Snake.h"
#include "JoyStick.h"

typedef enum
{
  START,
  IN_GAME,
  END
} GameState;

typedef enum
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE
} Direction;

uint8_t startScreen[][8]
{
  {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10011001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10011001,
  0b10111101,
  0b11111111
  }, 
  {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10011001,
  0b10111101,
  0b10011001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10011001,
  0b10111101,
  0b10011001,
  0b10011001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10011001,
  0b10111101,
  0b10011001,
  0b10011001,
  0b10000001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10011001,
  0b10111101,
  0b10011001,
  0b10011001,
  0b10000001,
  0b11111111
  },
  {
  0b11111111,
  0b10000001,
  0b10011001,
  0b10111101,
  0b10011001,
  0b10011001,
  0b10000001,
  0b11111111
  }
};

uint8_t startScreenSize = (sizeof(startScreen)/ sizeof(*startScreen));

uint8_t endScreen[8] 
{
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11111111
};

uint8_t field[8];

const uint8_t height = 8;
const uint8_t width = 8;
uint16_t playerScore = 0;
uint32_t completedGame = 0;
uint32_t pressedStart = 0;

Snake snake = Snake({3,3}, 32, 200);
JoyStick stick = JoyStick(A0, A1);
Point fruit;
GameState game;
Direction direction;

//Pin 8 wired to regPin 14, Pin 9 wired to regPin 11, Pin 10 wired to regPin 12
LedMatrix matrix = LedMatrix(Pin(8, OUTPUT), Pin(9, OUTPUT), Pin(10, OUTPUT));

void UpdateField(uint8_t field[8])
{
  matrix.Send(field);
  for (uint8_t i = 0; i < 8; i++)
  {
    field[i] = 0x00;
  }
}

void PlayGame(uint8_t field[8])
{

  //Game over triggers when player length is max or you hit yourself
  if (snake.GetLength() == snake.GetMaxLength() || snake.CheckIfHeadHitsBody()) game = GameState::END, direction = Direction::NONE, completedGame = millis(); 

  if (snake.Eat(fruit))
  {
    fruit = {random(0, width), random(0, height)};
    playerScore += 1;
    snake.AddBody();
  }

  //The block below is for holding a certain direction, reading the 
  //joystick directly, lead to diagonal movement. Which is not allowed
  //------------------------------------------------------------------
  if (stick.GetX() >= 0.5) direction = Direction::RIGHT;
  else if (stick.GetX() <= -0.5) direction = Direction::LEFT;

  if (stick.GetY() >= 0.5) direction = Direction::UP;
  else if (stick.GetY() <= -0.5) direction = Direction::DOWN;

  switch (direction)
  {
    case Direction::RIGHT:
      snake.Move(1, 0, width, height);
      break;
    case Direction::LEFT:
      snake.Move(-1, 0, width, height);
      break;
    case Direction::UP:
      snake.Move(0, 1, width, height);
      break;
    case Direction::DOWN:
      snake.Move(0, -1, width, height);
      break;
  }
  //------------------------------------------------------------------

  SetPoint(field, fruit, 1);
}


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  game = GameState::START;
  direction = Direction::NONE;
}

void loop() {

  switch (game)
  {
    case GameState::START:
      matrix.PlayAnimation(startScreen, startScreenSize, 500);
      if(stick.GetY() <= -0.5)
      {
        game = GameState::IN_GAME;
        snake = Snake({3,3}, 16, 200);
        fruit = {random(0, width), random(0, height)};
      }
      break;

    case GameState::IN_GAME:
      UpdateField(field);
      PlayGame(field);
      snake.DrawOnField(field);
      break;

    case GameState::END:
        matrix.Send(endScreen);
        if (millis() - completedGame >= 2000) game = GameState::START;
      break;
  }
}
