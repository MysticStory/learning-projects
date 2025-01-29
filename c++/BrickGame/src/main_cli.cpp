#ifdef TETRIS
#include "brick_game/tetris/tetrisModel.h"
#elif defined(SNAKE)
#include "brick_game/snake/snakeModel.h"
#else
#include "brick_game/snake/snakeModel.h"
#endif
#include "controller/controller.h"
#include "gui/cli/cliView.h"
#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)
int main() {
  s21::CliView view;
#ifdef TETRIS
  s21::tetris::TetrisModel game;
#elif defined(SNAKE)
  s21::snake::SnakeModel game;
#else
  s21::snake::SnakeModel game;
#endif
  s21::GameController<decltype(game), s21::CliView> controller(&game, &view);
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;  // Задержка между кадрами в миллисекундах
  while (true) {
    int start_time = clock();  // Время начала кадра

    auto action = view.getUserInput();
    controller.handleUserAction(action.first, action.second);
    if (game.getExit()) break;
    game.updateGame();  // Обновление игрового состояния
    view.render(game.getGameInfo(),
                game.getState());  // Отрисовка состояния игры

    int frame_time = (clock() - start_time) / CLOCKS_PER_MSEC;
    if (frame_time < frameDelay) {
      napms(frameDelay - frame_time);  // Задержка для поддержания нужного FPS
    }
  }

  std::cout << "End game" << std::endl;
  return 0;
}