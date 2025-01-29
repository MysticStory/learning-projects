#include <gtest/gtest.h>

#include "../src/brick_game/tetris/shape.h"

using namespace s21::tetris;

// Тест конструктора и метода createBlocks
TEST(ShapeTest, ConstructorAndCreateBlocks) {
  Shape shape;

  // Проверяем, что фигура была создана и содержит правильное количество блоков
  EXPECT_EQ(shape.getBlocks().size(), 4);

  // Проверяем, что центр фигуры находится в правильной начальной позиции
  EXPECT_EQ(shape.getCentr(),
            std::make_pair(TETRIS_START_BLOC_X, TETRIS_START_BLOC_Y));
}

// Тест движения вправо
TEST(ShapeTest, MoveRight) {
  Shape shape;
  auto initialBlocks = shape.getBlocks();
  shape.move(0);  // 0 - движение вправо

  for (size_t i = 0; i < initialBlocks.size(); ++i) {
    EXPECT_EQ(shape.getBlocks()[i].first, initialBlocks[i].first + 1);
    EXPECT_EQ(shape.getBlocks()[i].second, initialBlocks[i].second);
  }
}

// Тест движения влево
TEST(ShapeTest, MoveLeft) {
  Shape shape;
  auto initialBlocks = shape.getBlocks();
  shape.move(1);  // 1 - движение влево

  for (size_t i = 0; i < initialBlocks.size(); ++i) {
    EXPECT_EQ(shape.getBlocks()[i].first, initialBlocks[i].first - 1);
    EXPECT_EQ(shape.getBlocks()[i].second, initialBlocks[i].second);
  }
}

// Тест движения вниз
TEST(ShapeTest, MoveDown) {
  Shape shape;
  auto initialBlocks = shape.getBlocks();
  shape.move(2);  // 2 - движение вниз

  for (size_t i = 0; i < initialBlocks.size(); ++i) {
    EXPECT_EQ(shape.getBlocks()[i].first, initialBlocks[i].first);
    EXPECT_EQ(shape.getBlocks()[i].second, initialBlocks[i].second + 1);
  }
}

// Тест вращения фигуры
TEST(ShapeTest, Rotate) {
  Shape shape;
  auto initialBlocks = shape.getBlocks();
  shape.Rotate();  // Вращение фигуры

  // Проверяем, что после вращения координаты блоков изменились правильно
  for (size_t i = 0; i < initialBlocks.size(); ++i) {
    int x = initialBlocks[i].first - shape.getCentr().first;
    int y = initialBlocks[i].second - shape.getCentr().second;
    int rotatedX = -y + shape.getCentr().first;
    int rotatedY = x + shape.getCentr().second;

    EXPECT_EQ(shape.getBlocks()[i].first, rotatedX);
    EXPECT_EQ(shape.getBlocks()[i].second, rotatedY);
  }
}

// Тест на корректность получения типа фигуры
TEST(ShapeTest, GetTypeShape) {
  Shape shape;
  typeShape shapeType = shape.getTypeShape();

  EXPECT_TRUE(shapeType == typeShape::Z || shapeType == typeShape::S ||
              shapeType == typeShape::L || shapeType == typeShape::J ||
              shapeType == typeShape::T || shapeType == typeShape::O ||
              shapeType == typeShape::I);
}

// Тест на правильное задание и получение движения
TEST(ShapeTest, SetAndGetMoved) {
  Shape shape;
  shape.setMoved(Shape::Moved::Rigth);
  EXPECT_EQ(shape.getMoved(), Shape::Moved::Rigth);

  shape.setMoved(Shape::Moved::Left);
  EXPECT_EQ(shape.getMoved(), Shape::Moved::Left);

  shape.setMoved(Shape::Moved::Down);
  EXPECT_EQ(shape.getMoved(), Shape::Moved::Down);
}
