#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "../brick_game/Common/IGames.h"
#include "../gui/IView.h"

namespace s21 {

template <class Model, class View>
class GameController {
 public:
  GameController(Model *model, View *view) : model_(model), view_(view) {
    auto fieldSize = model_->getSizeField();
    view_->initialize(fieldSize.first, fieldSize.second);
  }

  ~GameController() = default;

  void handleUserAction(UserAction action, bool hold) {
    processAction(action, hold);
    updateView();
  }

  void resetGame() {
    model_->resetGame();
    updateView();
  }

 private:
  void processAction(UserAction action, bool hold) {
    model_->userInput(action, hold);
    model_->updateGame();
  }

  void updateView() {
    view_->render(model_->getGameInfo(), model_->getState());
  }

  Model *model_;
  View *view_;
};

}  // namespace s21

#endif  // GAME_CONTROLLER_H_