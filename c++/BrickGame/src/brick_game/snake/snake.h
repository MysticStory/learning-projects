#ifndef SNAKE_H_
#define SNAKE_H_

#include <utility>
#include <vector>

#include "../../_config/config_snake.h"
namespace s21 {
namespace snake {
class Snake {
 public:
  enum class Direction { Up, Down, Left, Right };

  Snake() : direction_(Direction::Down), size_(SNAKE_BEGIN_SIZE) {
    // Инициализация тела змейки
    for (int i = 0; i < SNAKE_BEGIN_SIZE; ++i) {
      body_.push_back({SNAKE_START_X, SNAKE_START_Y - i});
    }
  }
  ~Snake() { body_.clear(); }
  void changeDirection(Direction turn) {
    switch (direction_) {
      case Direction::Up:
        if (turn == Direction::Left) {
          direction_ = Direction::Left;
        } else {
          direction_ = Direction::Right;
        }
        break;
      case Direction::Down:
        if (turn == Direction::Left) {
          direction_ = Direction::Right;
        } else {
          direction_ = Direction::Left;
        }
        break;
      case Direction::Left:
        if (turn == Direction::Left) {
          direction_ = Direction::Down;
        } else {
          direction_ = Direction::Up;
        }
        break;
      case Direction::Right:
        if (turn == Direction::Left) {
          direction_ = Direction::Up;
        } else {
          direction_ = Direction::Down;
        }
        break;
    }
  }

  std::pair<int, int> move() {
    auto head = body_.front();
    switch (direction_) {
      case Direction::Up:
        --head.second;
        break;
      case Direction::Down:
        ++head.second;
        break;
      case Direction::Left:
        --head.first;
        break;
      case Direction::Right:
        ++head.first;
        break;
    }

    body_.insert(body_.begin(), head);
    std::pair<int, int> tail = std::make_pair(-1, -1);
    if ((int)body_.size() > size_) {
      tail = body_.back();  // Получаем последний элемент
      body_.pop_back();     // Удаляем последний элемент
    }
    return tail;
  }

  void grow() { ++size_; }

  const std::vector<std::pair<int, int>>& getBody() const { return body_; }
  Direction getDirection() const { return direction_; }
  void setDirection(Direction dir) { direction_ = dir; }
  std::pair<int, int> getHeadPosition() const { return body_.front(); }

 private:
  Direction direction_;
  int size_;
  std::vector<std::pair<int, int>> body_;
};

}  // namespace snake
}  // namespace s21
#endif  // SNAKE_H_