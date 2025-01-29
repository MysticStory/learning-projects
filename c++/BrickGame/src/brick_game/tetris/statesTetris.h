#ifndef STATES_TETRIS_H_
#define STATES_TETRIS_H_

#include <cmath>

#include "../Common/IState.h"

namespace s21::tetris {

class TetrisModel;
enum class GameState {
  MainMenu,       // 0
  Start,          // 1
  Paused,         // 2
  SpawnShape,     // 3
  Moving,         // 4
  Shifting,       // 5
  Attaching,      // 6
  GameOver = 10,  // 10
  Win = 11        // 11
};
class MainMenuState : public IState {
 public:
  explicit MainMenuState(TetrisModel& game);
  void userInput(UserAction action, bool hol [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
};

class StartState : public IState {
 public:
  explicit StartState(TetrisModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
};

class SpawnShapeState : public IState {
 public:
  explicit SpawnShapeState(TetrisModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
};

class MovingState : public IState {
 public:
  explicit MovingState(TetrisModel& game);
  void userInput(UserAction action, bool hold [[maybe_unused]]) override;
  void updateGame() override;
  bool canMove(int dir);

 private:
  TetrisModel& game_;
  bool forceSpeed;
};

class ShiftingState : public IState {
 public:
  explicit ShiftingState(TetrisModel& game);
  void userInput(UserAction action, bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
  bool forceSpeed;
};

class AttachingState : public IState {
 public:
  explicit AttachingState(TetrisModel& game);
  void userInput(UserAction action, bool hold [[maybe_unused]]) override;
  void updateGame() override;
  int clearFullRows();

 private:
  TetrisModel& game_;
  bool forceSpeed;
};

class PausedState : public IState {
 public:
  explicit PausedState(TetrisModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
};

class GameOverState : public IState {
 public:
  explicit GameOverState(TetrisModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  TetrisModel& game_;
};

}  // namespace s21::tetris

#endif  // STATES_TETRIS_H_