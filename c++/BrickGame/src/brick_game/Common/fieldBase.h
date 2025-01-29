#ifndef FIELD_BASE_H_
#define FIELD_BASE_H_

#include <cstdlib>
#include <stdexcept>
#include <utility>

class FieldBase {
 public:
  FieldBase(int width, int height, int empty_char = 0)
      : width_(width), height_(height), empty_char_(empty_char) {
    if (width <= 0 || height <= 0) {
      throw std::invalid_argument("Отрицательный размер поля");
    }
    allocateField();
    clearField();
  }

  ~FieldBase() {
    for (int i = 0; i < width_; ++i) {  // Освобождаем память по ширине
      delete[] field_[i];
    }
    delete[] field_;
  }

  int getWidth() const { return width_; }
  int getHeight() const { return height_; }
  int** getField() const { return field_; }

  void clearField() {
    for (int x = 0; x < width_; ++x) {
      for (int y = 0; y < height_; ++y) {
        field_[x][y] = empty_char_;  // Символ, обозначающий пустую клетку
      }
    }
  }

  void setCell(int x, int y, int value) {
    if (isValidPosition(x, y)) {
      field_[x][y] = value;
    }
  }

  int getCell(int x, int y) const {
    if (isValidPosition(x, y)) {
      return field_[x][y];
    }
    return -1;  // Возвращаем ошибочное значение если координаты неверны
  }

  bool isEmptyCell(int x, int y) const {
    return isValidPosition(x, y) && getCell(x, y) == empty_char_;
  }

  std::pair<int, int> getRandomEmptyCell() const {
    int x, y;
    do {
      x = rand() % width_;
      y = rand() % height_;
    } while (field_[x][y] != empty_char_);
    return {x, y};
  }
  void copyFrom(const FieldBase& other) {
    if (width_ != other.width_ || height_ != other.height_) {
      throw std::runtime_error("Размер полей не совпадает.");
    }

    for (int i = 0; i < height_; ++i) {
      for (int j = 0; j < width_; ++j) {
        field_[j][i] = other.field_[j][i];
      }
    }
  }

 private:
  bool isValidPosition(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
  }

  void allocateField() {
    field_ = new int*[width_];  // Создаем массив строк по ширине
    for (int i = 0; i < width_; ++i) {
      field_[i] = new int[height_];  // Каждая строка имеет высоту
    }
  }

  int** field_;
  int width_;
  int height_;
  int empty_char_;
};

#endif  // FIELD_BASE_H_