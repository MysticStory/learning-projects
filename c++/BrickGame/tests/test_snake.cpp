#include <gtest/gtest.h>

#include "../src/brick_game/snake/snake.h"

namespace s21::snake {

// Тестируем инициализацию змейки
TEST(SnakeTest, Initialization) {
  Snake snake;

  // Проверяем начальное направление
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Down);

  // Проверяем размер тела змейки
  EXPECT_EQ(snake.getBody().size(), SNAKE_BEGIN_SIZE);

  // Проверяем позицию головы змейки
  auto head_position = snake.getHeadPosition();
  EXPECT_EQ(head_position.first, SNAKE_START_X);
  EXPECT_EQ(head_position.second, SNAKE_START_Y);
}

// Тестируем смену направления
TEST(SnakeTest, ChangeDirection) {
  Snake snake;

  // Начальное направление вниз
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Down);

  // Смена направления налево
  snake.changeDirection(Snake::Direction::Left);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Right);

  // Смена направления направо
  snake.changeDirection(Snake::Direction::Right);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Down);
}
class SnakeTest1 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Инициализация перед каждым тестом, если нужно
  }

  void TearDown() override {
    // Очистка после каждого теста, если нужно
  }

  Snake snake;  // Создаем объект змейки для тестирования
};
// Тестирование изменения направления для направления Up
TEST_F(SnakeTest1, ChangeDirectionFromUp) {
  snake.setDirection(
      Snake::Direction::Up);  // Устанавливаем начальное направление

  snake.changeDirection(Snake::Direction::Left);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Left);

  snake.changeDirection(Snake::Direction::Right);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Up);
}

// Тестирование изменения направления для направления Down
TEST_F(SnakeTest1, ChangeDirectionFromDown) {
  snake.setDirection(
      Snake::Direction::Down);  // Устанавливаем начальное направление

  snake.changeDirection(Snake::Direction::Left);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Right);

  snake.changeDirection(Snake::Direction::Right);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Down);
}

// Тестирование изменения направления для направления Left
TEST_F(SnakeTest1, ChangeDirectionFromLeft) {
  snake.setDirection(
      Snake::Direction::Left);  // Устанавливаем начальное направление

  snake.changeDirection(Snake::Direction::Left);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Down);

  snake.changeDirection(Snake::Direction::Right);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Left);
}

// Тестирование изменения направления для направления Right
TEST_F(SnakeTest1, ChangeDirectionFromRight) {
  snake.setDirection(
      Snake::Direction::Right);  // Устанавливаем начальное направление

  snake.changeDirection(Snake::Direction::Left);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Up);

  snake.changeDirection(Snake::Direction::Right);
  EXPECT_EQ(snake.getDirection(), Snake::Direction::Right);
}
// Тестируем движение змейки
TEST(SnakeTest, Move) {
  Snake snake;

  // Двигаемся вниз
  auto initial_head = snake.getHeadPosition();
  snake.move();
  auto new_head = snake.getHeadPosition();

  EXPECT_EQ(new_head.first, initial_head.first);
  EXPECT_EQ(new_head.second, initial_head.second + 1);

  // Двигаемся вправо
  snake.changeDirection(Snake::Direction::Right);
  initial_head = snake.getHeadPosition();
  snake.move();
  new_head = snake.getHeadPosition();

  EXPECT_EQ(new_head.first, initial_head.first - 1);
  EXPECT_EQ(new_head.second, initial_head.second);
}

// Тестируем рост змейки
TEST(SnakeTest, Grow) {
  Snake snake;

  // Изначальный размер
  int initial_size = snake.getBody().size();

  // Растем
  snake.grow();
  snake.move();

  // Проверяем, что змейка увеличилась
  EXPECT_EQ(snake.getBody().size(), initial_size + 1);
  snake.move();
  EXPECT_EQ(snake.getBody().size(), initial_size + 1);
}

}  // namespace s21::snake