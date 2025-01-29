#ifndef ISTATE_H_
#define ISTATE_H_

#include "IGames.h"
namespace s21 {

class IState {
 public:
  virtual ~IState() = default;
  virtual void userInput(UserAction action, bool hold) = 0;
  virtual void updateGame() = 0;
};

}  // namespace s21
#endif