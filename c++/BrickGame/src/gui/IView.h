#ifndef IVIEW_H_
#define IVIEW_H_

#include "../brick_game/Common/IGames.h"

namespace s21 {

class IView {
 public:
  virtual void initialize(int rows, int cols) = 0;
  virtual void render(const GameInfo& gameInfo, int currentState) = 0;
  virtual std::pair<UserAction, bool> getUserInput() = 0;
  virtual void displayGameOver(int score) = 0;
  virtual void cleanUp() = 0;

  virtual ~IView() = default;
};

}  // namespace s21

#endif  // IVIEW_H_