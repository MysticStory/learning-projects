#ifndef STATES_H_
#define STATES_H_

#include "../Common/IState.h"

namespace s21 {
namespace snake {
class SnakeModel;
enum class GameState {
  MainMenu,       // 0
  Start,          // 1
  Paused,         // 2
  SpawnFruit,     // 3
  TurnMove,       // 4
  EatFruit,       // 5
  GameOver = 10,  // 10
  Win = 11        // 11
};
class MainMenuState : public IState {
 public:
  explicit MainMenuState(SnakeModel& game);
  void userInput(UserAction action, bool hol [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

class StartState : public IState {
 public:
  explicit StartState(SnakeModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

class SpawnFruitState : public IState {
 public:
  explicit SpawnFruitState(SnakeModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

class TurnMoveState : public IState {
 public:
  explicit TurnMoveState(SnakeModel& game);
  void userInput(UserAction action, bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
  bool forceSpeed;
};

class PausedState : public IState {
 public:
  explicit PausedState(SnakeModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

class EatFruitState : public IState {
 public:
  explicit EatFruitState(SnakeModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

class GameOverState : public IState {
 public:
  explicit GameOverState(SnakeModel& game);
  void userInput(UserAction action [[maybe_unused]],
                 bool hold [[maybe_unused]]) override;
  void updateGame() override;

 private:
  SnakeModel& game_;
};

}  // namespace snake
}  // namespace s21
#endif  // STATES_H_