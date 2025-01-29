#ifndef SNAKE_GAME_H_
#define SNAKE_GAME_H_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "../Common/fieldBase.h"
#include "snake.h"
#include "statesSnake.h"
namespace s21 {
namespace snake {
class SnakeModel : public IGames {
 public:
  SnakeModel();
  ~SnakeModel();
  Snake& getSnake();
  FieldBase& getField() const;
  GameInfo& getGameInfo();
  bool getExit();
  void setExit();

  void setState(GameState state);
  void setState(int state) override;
  void userInput(UserAction action, bool hold) override;
  void updateGame() override;
  const GameInfo& getGameInfo() const override;
  void resetGame() override;

  void saveGame(const std::string& filepath) const override;
  void loadGame(const std::string& filepath) override;

  void spawnSnake();
  int getState() const;
  std::pair<int, int> getSizeField() override;

 private:
  void initializeStates();
  IState* currentState_;
  bool exit;
  GameInfo game_info_;
  Snake snake_;
  FieldBase* currentField_;  // Указатель на текущее поле
  FieldBase* nextField_;  // Указатель на следующее поле

  std::unique_ptr<IState> mainMenuState_;
  std::unique_ptr<IState> startState_;
  std::unique_ptr<IState> pausedState_;
  std::unique_ptr<IState> spawnFruitState_;
  std::unique_ptr<IState> turnMoveState_;
  std::unique_ptr<IState> eatFruitState_;
  std::unique_ptr<IState> gameOverState_;
  std::unique_ptr<IState> winState_;

  GameState currentGameState_;
};

}  // namespace snake
}  // namespace s21
#endif  // SNAKE_GAME_H_