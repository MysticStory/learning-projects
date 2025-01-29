#ifndef CONFIG_SNAKE_H_
#define CONFIG_SNAKE_H_

#include <string>
namespace s21::snake {
// путь сохранение и название файла
static inline const std::string PATH_SNAKE = "highScoreSnake.txt";
// Размеры игрового поля для Змейки
static constexpr int SNAKE_FIELD_HEIGHT = 20;
static constexpr int SNAKE_FIELD_WIDTH = 10;

// Начальное положение Змейки
static constexpr int SNAKE_START_Y = 10;
static constexpr int SNAKE_START_X = 5;

// Скорость движения змейки
static constexpr int SNAKE_INITIAL_SPEED = 5;
static constexpr int SNAKE_BASE_SPEED = 160;

static constexpr int SNAKE_BEGIN_SIZE = 4;
// Максимальная длина змейки
static constexpr int SNAKE_MAX_LENGTH = 200;

// Скорость увеличения сложности
static constexpr int SNAKE_SPEED_INCREMENT = 1;
static constexpr int SNAKE_SCORE_INCREMENT = 1;
static constexpr int SNAKE_SCORE_FOR_LEVEL = 5;

// Определение символов для отображения на игровом поле
static constexpr char SNAKE_BODY_CHAR = '#';
static constexpr char SNAKE_FOOD_CHAR = '*';
static constexpr char SNAKE_EMPTY_CHAR = '.';
}  // namespace s21::snake
#endif  // CONFIG_SNAKE_H_
