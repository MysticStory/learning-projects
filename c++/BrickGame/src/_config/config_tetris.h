#ifndef CONFIG_TETRIS_H_
#define CONFIG_TETRIS_H_

#include <array>
#include <string>
namespace s21::tetris {
enum class typeShape { Z, S, L, J, T, O, I };
static const std::array<std::array<std::pair<int, int>, 4>, 7>
    shapeCoordinates = {{
        {{{0, -1}, {0, 0}, {-1, 0}, {-1, 1}}},  // Z
        {{{0, -1}, {0, 0}, {1, 0}, {1, 1}}},    // S
        {{{-1, -1}, {0, -1}, {0, 0}, {0, 1}}},  // L
        {{{1, -1}, {0, -1}, {0, 0}, {0, 1}}},   // J
        {{{-1, 0}, {0, 0}, {1, 0}, {0, 1}}},    // T
        {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}},     // O
        {{{0, -1}, {0, 0}, {0, 1}, {0, 2}}}     // I
    }};
// Путь для сохранения и название файла рекорда
static inline const std::string PATH_TETRIS = "highScoreTetris.txt";

// Размеры игрового поля для Tetris
static constexpr int TETRIS_FIELD_HEIGHT = 20;
static constexpr int TETRIS_FIELD_WIDTH = 10;

static constexpr int TETRIS_START_BLOC_X = 5;
static constexpr int TETRIS_START_BLOC_Y = 1;

// Скорость игры
static constexpr int TETRIS_INITIAL_SPEED = 5;
static constexpr int TETRIS_BASE_SPEED = 150;

// Скорость увеличения сложности
static constexpr int TETRIS_SPEED_INCREMENT = 1;
static constexpr int TETRIS_SCORE_INCREMENT = 100;
static constexpr int TETRIS_SCORE_FOR_LEVEL = 600;
// Определение символов для отображения на игровом поле
static constexpr char TETRIS_BLOCK_CHAR = '#';
static constexpr char TETRIS_EMPTY_CHAR = '.';
}  // namespace s21::tetris
#endif  // CONFIG_TETRIS_H_