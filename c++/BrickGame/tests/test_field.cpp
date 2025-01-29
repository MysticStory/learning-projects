#include <gtest/gtest.h>

#include "../src/brick_game/Common/fieldBase.h"

// Тест конструктора и базовых методов
TEST(FieldBaseTest, ConstructorAndGetters) {
  FieldBase field(10, 20, -1);
  EXPECT_EQ(field.getWidth(), 10);
  EXPECT_EQ(field.getHeight(), 20);

  // Проверка, что поле было инициализировано с правильным значением empty_char
  for (int x = 0; x < field.getWidth(); ++x) {
    for (int y = 0; y < field.getHeight(); ++y) {
      EXPECT_EQ(field.getCell(x, y), -1);
    }
  }
}

// Тест метода setCell и getCell
TEST(FieldBaseTest, SetAndGetCell) {
  FieldBase field(10, 20, 0);

  field.setCell(5, 5, 1);
  EXPECT_EQ(field.getCell(5, 5), 1);

  // Проверка на выход за границы
  EXPECT_EQ(field.getCell(-1, -1), -1);  // Проверка некорректной ячейки
  EXPECT_EQ(field.getCell(10, 20), -1);  // Проверка некорректной ячейки
}

// Тест метода clearField
TEST(FieldBaseTest, ClearField) {
  FieldBase field(10, 20, -1);

  field.setCell(5, 5, 1);
  field.clearField();

  // Проверка, что все ячейки сброшены до empty_char
  for (int x = 0; x < field.getWidth(); ++x) {
    for (int y = 0; y < field.getHeight(); ++y) {
      EXPECT_EQ(field.getCell(x, y), -1);
    }
  }
}

// Тест метода isEmptyCell
TEST(FieldBaseTest, IsEmptyCell) {
  FieldBase field(10, 20, 0);

  field.setCell(5, 5, 1);
  EXPECT_FALSE(field.isEmptyCell(5, 5));
  EXPECT_TRUE(field.isEmptyCell(0, 0));
}

// Тест метода getRandomEmptyCell
TEST(FieldBaseTest, GetRandomEmptyCell) {
  FieldBase field(10, 10, 0);

  field.setCell(0, 0, 1);  // Заполняем одну ячейку
  auto [x, y] = field.getRandomEmptyCell();

  EXPECT_TRUE(field.isEmptyCell(x, y));
  EXPECT_FALSE(x == 0 &&
               y == 0);  // Убедимся, что не выбрана заполненная ячейка
}

// Тест метода copyFrom
TEST(FieldBaseTest, CopyFrom) {
  FieldBase field1(10, 20, 0);
  FieldBase field2(10, 20, 0);

  field1.setCell(5, 5, 1);
  field2.copyFrom(field1);

  EXPECT_EQ(field2.getCell(5, 5), 1);

  // Проверка на выброс исключения при несовпадении размеров
  FieldBase field3(5, 5, 0);
  EXPECT_THROW(field2.copyFrom(field3), std::runtime_error);
}
// Тест выброса исключения при некорректных размерах поля в конструкторе
TEST(FieldBaseTest, ConstructorThrowsOnInvalidDimensions) {
  // Ожидаем выброс исключения при отрицательных значениях ширины и высоты
  EXPECT_THROW(FieldBase field(-1, 10, 0), std::invalid_argument);
  EXPECT_THROW(FieldBase field(10, -1, 0), std::invalid_argument);
  EXPECT_THROW(FieldBase field(-1, -1, 0), std::invalid_argument);
}
// Тест выброса исключения при несовпадении размеров полей в методе copyFrom
TEST(FieldBaseTest, CopyFromThrowsOnSizeMismatch) {
  FieldBase field1(10, 20, 0);
  FieldBase field2(5, 10, 0);  // Поле с другими размерами

  // Ожидаем, что будет выброшено исключение std::runtime_error
  EXPECT_THROW(field1.copyFrom(field2), std::runtime_error);
}