#ifndef CLI_VIEW_H_
#define CLI_VIEW_H_

#include <ncurses.h>

#include "../IView.h"
namespace s21 {

class CliView : public IView {
 public:
  CliView() { initNcurses(); }

  ~CliView() override {
    endwin();  // Завершение работы с ncurses
  }

  void initNcurses() {
    if (initscr() == nullptr) {
      throw std::runtime_error("Failed to initialize ncurses");
    }
    noecho();  // Отключение отображения ввода
    cbreak();  // Выход без необходимости нажимать Enter
    keypad(stdscr, TRUE);  // Включение поддержки функциональных клавиш
    curs_set(0);           // Скрытие курсора
    timeout(0);  // Задержка на получение ввода
  }

  void initialize(int width [[maybe_unused]],
                  int height [[maybe_unused]]) override {
    rows_ = height;  // SNAKE_FIELD_HEIGHT;
    cols_ = width;   // SNAKE_FIELD_WIDTH;
  }
  virtual void displayGameOver(int score [[maybe_unused]]) override {}
  virtual void cleanUp() override {}

  void render(const GameInfo& gameInfo, int currentState) override {
    // clear();
    drawField(gameInfo);
    drawInfoPanel(gameInfo, currentState);
    refresh();
  }

  std::pair<UserAction, bool> getUserInput() override {
    static int count = 0;
    int ch = getch();
    UserAction new_key = UserAction::NO_ACT;
    switch (ch) {
      case KEY_LEFT:
        new_key = UserAction::Left;
        break;
      case KEY_RIGHT:
        new_key = UserAction::Right;
        break;
      case KEY_UP:
        new_key = UserAction::Up;
        break;
      case KEY_DOWN:
        new_key = UserAction::Down;
        break;
      case 'p':
        new_key = UserAction::Pause;
        break;
      case 'q':
        new_key = UserAction::Terminate;
        break;
      case ' ':
        new_key = UserAction::Action;
        break;
      case 's':
        new_key = UserAction::Start;
        break;
      default:
        new_key = UserAction::NO_ACT;
        break;
    }
    if (new_key == UserAction::NO_ACT) {
      count = 0;
    } else {
      ++count;
    }
    return std::make_pair(new_key, count > 5);
  }

 private:
  UserAction lastkey;
  int rows_;
  int cols_;
  void drawBorder() {
    // Верхняя граница
    for (int x = 0; x < cols_ + 2; ++x) {
      mvaddch(0, x, '#');
    }

    // Боковые границы
    for (int y = 0; y < rows_; ++y) {
      mvaddch(y + 1, 0, '#');          // Левая граница
      mvaddch(y + 1, cols_ + 1, '#');  // Правая граница
    }

    // Нижняя граница
    for (int x = 0; x < cols_ + 2; ++x) {
      mvaddch(rows_ + 1, x, '#');
    }
  }

  void drawField(const GameInfo& gameInfo) {
    drawBorder();
    const auto& field = gameInfo.field;
    for (int x = 0; x < cols_; ++x) {
      for (int y = 0; y < rows_; ++y) {
        mvaddch(y + 1, x + 1,
                (char)field[x][y]);  // Игровое поле с учетом рамки
      }
    }
  }

  void drawInfoPanel(const GameInfo& gameInfo, int currentState) {
    int startX = cols_ + 3;  // Панель информации начинается после поля
    mvprintw(1, startX, "Score: %d", gameInfo.score);
    mvprintw(2, startX, "Level: %d", gameInfo.level);
    mvprintw(3, startX, "Speed: %d", gameInfo.speed);
    mvprintw(4, startX, "High Score: %d", gameInfo.high_score);
    mvprintw(5, startX,
             currentState != 10
                 ? (gameInfo.pause ? "Pause     " : "Play       ")
                 : "Game Over");
    mvprintw(6, startX, "Current state: %i", currentState);
    mvprintw(7, startX, "Controls:");
    mvprintw(8, startX, "Arrows: Move");
    mvprintw(10, startX, "'S': Start");
    mvprintw(11, startX, currentState < 10 ? "'P': Pause " : "'Q': Quit  ");
    mvprintw(12, startX,
             currentState < 10 && currentState != 0 ? "'Q': Stop Game"
                                                    : "                  ");
  }
};
}  // namespace s21

#endif  // CLI_VIEW_H_