#ifndef TETRIS_MODEL_H_
#define TETRIS_MODEL_H_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "../Common/fieldBase.h"
#include "shape.h"
#include "statesTetris.h"
namespace s21::tetris {

class TetrisModel : public IGames {
 public:
  TetrisModel();
  ~TetrisModel();
  Shape& getShape();
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

  void spawnShape();
  int getState() const;
  std::pair<int, int> getSizeField() override;

 private:
  void initializeStates();
  IState* currentState_;
  bool exit;
  GameInfo game_info_;
  Shape shape_;
  FieldBase* currentField_;  // Указатель на текущее поле
  FieldBase* nextField_;  // Указатель на следующее поле

  std::unique_ptr<IState> mainMenuState_;
  std::unique_ptr<IState> startState_;
  std::unique_ptr<IState> pausedState_;
  std::unique_ptr<IState> spawnShapeState_;
  std::unique_ptr<IState> movingState_;
  std::unique_ptr<IState> shiftingState_;
  std::unique_ptr<IState> attachingState_;
  std::unique_ptr<IState> gameOverState_;

  GameState currentGameState_;
};

}  // namespace s21

#endif  // TETRIS_MODEL_H_