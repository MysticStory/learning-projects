#ifndef SHAPE_H_
#define SHAPE_H_

#include <array>
#include <utility>
#include <vector>

#include "../../_config/config_tetris.h"
namespace s21::tetris {

class Shape {
 public:
  using Cords = std::pair<int, int>;
  enum Moved { Rigth, Left, Down, NO };
  Shape() : typeShape_(getRandomShape()), moved_(Moved::NO) {
    createBlocks(typeShape_);
  }
  ~Shape() { blocks_.clear(); }

  typeShape getRandomShape() {
    int randomIndex = std::rand() % 7;
    return static_cast<typeShape>(randomIndex);
  }
  void createBlocks(typeShape shape) {
    blocks_.clear();
    // Получение координат фигуры на основе выбранного типа
    const auto& coords = shapeCoordinates[static_cast<int>(shape)];
    // Создание блоков на основе координат и стартовых позиций
    for (const auto& coord : coords) {
      blocks_.emplace_back(Cords{TETRIS_START_BLOC_X + coord.first,
                                 TETRIS_START_BLOC_Y + coord.second});
    }
    centr_ = std::make_pair(TETRIS_START_BLOC_X, TETRIS_START_BLOC_Y);
  }
  void move(int dir) {
    switch (dir) {
      case 2:
        moveDown();
        break;

      case 0:
        moveRigth();
        break;

      case 1:
        moveLeft();
        break;

      default:
        break;
    }
  }

  void moveDown() {
    for (auto& cord : blocks_) {
      cord.second += 1;
    }
    centr_.second += 1;
  }
  void moveLeft() {
    for (auto& cord : blocks_) {
      cord.first -= 1;
    }
    centr_.first -= 1;
  }
  void moveRigth() {
    for (auto& cord : blocks_) {
      cord.first += 1;
    }
    centr_.first += 1;
  }
  void Rotate() {
    if (typeShape_ == typeShape::O) return;

    int rotationMatrix[2][2] = {{0, -1}, {1, 0}};

    for (auto& cord : blocks_) {
      int x = cord.first - centr_.first;
      int y = cord.second - centr_.second;
      cord.first =
          x * rotationMatrix[0][0] + y * rotationMatrix[0][1] + centr_.first;
      cord.second =
          x * rotationMatrix[1][0] + y * rotationMatrix[1][1] + centr_.second;
    }
  }
  const std::vector<Cords>& getBlocks() const { return blocks_; }
  void setBlocks(std::vector<Cords> bloks) { blocks_ = bloks; }
  typeShape getTypeShape() const { return typeShape_; }
  Moved getMoved() { return moved_; }
  void setMoved(Moved moved) {
    if (moved_ != Moved::Down) moved_ = moved;
  }
  Cords getCentr() const { return centr_; }
  void setCentr(const Cords& centr) { centr_ = centr; }

 private:
  typeShape typeShape_;
  std::vector<Cords> blocks_;
  Cords centr_;
  Moved moved_;
};

}  // namespace s21

#endif  // SHAPE_H_