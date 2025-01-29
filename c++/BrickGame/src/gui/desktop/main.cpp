#include <QApplication>
#include <QTimer>

#include "../../controller/controller.h"
#include "qtview.h"
#ifdef TETRIS
#include "../../brick_game/tetris/tetrisModel.h"
#elif defined(SNAKE)
#include "../../brick_game/snake/snakeModel.h"
#else
#include "../../brick_game/snake/snakeModel.h"
#endif
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::QtView view;
#ifdef TETRIS
  s21::tetris::TetrisModel game;
#elif defined(SNAKE)
  s21::snake::SnakeModel game;
#else
  s21::snake::SnakeModel game;
#endif
  s21::GameController<decltype(game), s21::QtView> controller(&game, &view);

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  QTimer timer;
  QObject::connect(&timer, &QTimer::timeout, [&]() {
    auto action = view.getUserInput();
    controller.handleUserAction(action.first, action.second);
    if (game.getExit()) {
      app.quit();
    }
    game.updateGame();
    view.render(game.getGameInfo(), game.getState());
  });
  timer.start(frameDelay);

  view.show();
  return app.exec();
}
