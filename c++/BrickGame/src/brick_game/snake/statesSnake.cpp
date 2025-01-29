#include "statesSnake.h"

#include "snakeModel.h"

namespace s21 {
namespace snake {
MainMenuState::MainMenuState(SnakeModel& game) : game_(game) {}

void MainMenuState::userInput(UserAction action, bool hol [[maybe_unused]]) {
  if (action == UserAction::Start) {
    game_.setState(GameState::Start);
  } else if (action == UserAction::Terminate) {
    game_.setExit();
  }
}

void MainMenuState::updateGame() {}

StartState::StartState(SnakeModel& game) : game_(game) {}

void StartState::userInput(UserAction action [[maybe_unused]],
                           bool hold [[maybe_unused]]) {}

void StartState::updateGame() {
  game_.resetGame();
  game_.spawnSnake();
  game_.setState(GameState::SpawnFruit);
}

SpawnFruitState::SpawnFruitState(SnakeModel& game) : game_(game) {}

void SpawnFruitState::userInput(UserAction action [[maybe_unused]],
                                bool hold [[maybe_unused]]) {}

void SpawnFruitState::updateGame() {
  auto [x, y] = game_.getField().getRandomEmptyCell();
  game_.getField().setCell(x, y, SNAKE_FOOD_CHAR);
  game_.setState(GameState::TurnMove);
}

TurnMoveState::TurnMoveState(SnakeModel& game)
    : game_(game), forceSpeed(false) {}

void TurnMoveState::userInput(UserAction action, bool hold [[maybe_unused]]) {
  forceSpeed = false;
  switch (action) {
    case UserAction::Left:
      game_.getSnake().changeDirection(Snake::Direction::Left);
      break;
    case UserAction::Right:
      game_.getSnake().changeDirection(Snake::Direction::Right);
      break;
    case UserAction::Action:
      forceSpeed = true;
      break;
    case UserAction::Pause:
      game_.getGameInfo().pause = true;
      game_.setState(GameState::Paused);
      break;
    case UserAction::Terminate:
      game_.setState(GameState::GameOver);
      break;
    default:
      forceSpeed = false;
      break;
  }
}

void TurnMoveState::updateGame() {
  static int count = 0;
  int speed = game_.getGameInfo().speed * (forceSpeed ? 4 : 1);
  if (count >= SNAKE_BASE_SPEED / speed) {
    std::pair<int, int> tail = game_.getSnake().move();
    std::pair<int, int> head = game_.getSnake().getHeadPosition();
    char cell = game_.getField().getCell(head.first, head.second);
    if (cell == SNAKE_FOOD_CHAR) {
      game_.setState(GameState::EatFruit);
    } else if (cell != SNAKE_EMPTY_CHAR) {
      game_.setState(GameState::GameOver);
    }
    game_.getField().setCell(head.first, head.second, SNAKE_BODY_CHAR);
    game_.getField().setCell(tail.first, tail.second, SNAKE_EMPTY_CHAR);

    count = 0;
  } else {
    count++;
  }
}

PausedState::PausedState(SnakeModel& game) : game_(game) {}

void PausedState::userInput(UserAction action [[maybe_unused]],
                            bool hold [[maybe_unused]]) {
  if (UserAction::Pause == action || UserAction::Start == action) {
    game_.getGameInfo().pause = false;
    game_.setState(GameState::TurnMove);
  }
}

void PausedState::updateGame() {}

EatFruitState::EatFruitState(SnakeModel& game) : game_(game) {}

void EatFruitState::userInput(UserAction action [[maybe_unused]],
                              bool hold [[maybe_unused]]) {}

void EatFruitState::updateGame() {
  game_.getSnake().grow();
  game_.getGameInfo().score += SNAKE_SCORE_INCREMENT;
  if (game_.getGameInfo().score / SNAKE_SCORE_INCREMENT >= SNAKE_MAX_LENGTH)
    game_.setState(GameState::Win);
  else {
    if (game_.getGameInfo().score % SNAKE_SCORE_FOR_LEVEL == 0) {
      game_.getGameInfo().level += 1;
      game_.getGameInfo().speed += SNAKE_SPEED_INCREMENT;
    }
    if (game_.getGameInfo().score > game_.getGameInfo().high_score)
      game_.getGameInfo().high_score = game_.getGameInfo().score;
    game_.setState(GameState::SpawnFruit);
  }
}

GameOverState::GameOverState(SnakeModel& game) : game_(game) {}

void GameOverState::userInput(UserAction action [[maybe_unused]],
                              bool hold [[maybe_unused]]) {
  game_.saveGame(PATH_SNAKE);
  if (action == UserAction::Start) {
    game_.resetGame();
    game_.setState(GameState::Start);
  } else if (action == UserAction::Terminate) {
    game_.setExit();
  }
}

void GameOverState::updateGame() {}
}  // namespace snake
}  // namespace s21