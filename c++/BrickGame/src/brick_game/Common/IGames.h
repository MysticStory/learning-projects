#ifndef IGAMES_H_
#define IGAMES_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
// Перечисление для возможных действий пользователя
enum class UserAction {
  NO_ACT = 0,
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
};

// Структура для хранения информации о состоянии игры
struct GameInfo {
  int** field;     // Основное игровое поле
  int** next;      // Следующее состояние
  int score;       // Текущий счёт
  int high_score;  // Рекордный счёт
  int level;       // Уровень игры
  int speed;       // Скорость игры
  bool pause;      // Состояние паузы

  GameInfo()
      : field(nullptr),
        next(nullptr),
        score(0),
        high_score(0),
        level(1),
        speed(1),
        pause(false) {}
};

// Абстрактный базовый класс для всех игр
class IGames {
 public:
  virtual ~IGames() = default;

  // Обработка действий пользователя
  virtual void userInput(UserAction action, bool hold) = 0;

  // Обновление состояния игры
  virtual void updateGame() = 0;

  // Получение информации о текущем состоянии игры
  virtual const GameInfo& getGameInfo() const = 0;

  // Сброс игры к начальному состоянию
  virtual void resetGame() = 0;

  // Сохранение текущего состояния игры
  virtual void saveGame(const std::string& filepath) const = 0;

  // Загрузка состояния игры из файла
  virtual void loadGame(const std::string& filepath) = 0;

  // Установка состояния игры
  virtual void setState(int state) = 0;

  // Получение текущего состояния игры
  virtual int getState() const = 0;

  virtual std::pair<int, int> getSizeField() = 0;
};

}  // namespace s21

#endif  // IGAMES_H_