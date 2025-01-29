#include <gtest/gtest.h>

#include "../src/brick_game/snake/snakeModel.h"
#include "../src/brick_game/snake/statesSnake.h"

namespace s21::snake {

// Тестирование состояния MainMenu
TEST(StateTest, MainMenuState) {
  SnakeModel model;
  model.setState(GameState::MainMenu);

  // Проверяем, что начальное состояние MainMenu
  ASSERT_EQ(model.getState(), static_cast<int>(GameState::MainMenu));

  // Пытаемся начать игру
  model.userInput(UserAction::Start, false);
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::Start));

  // Проверяем завершение игры
  model.setState(GameState::MainMenu);
  model.userInput(UserAction::Terminate, false);
  EXPECT_TRUE(model.getExit());
}

// Тестирование состояния Start
TEST(StateTest, StartState) {
  SnakeModel model;
  model.setState(GameState::Start);

  // Проверяем, что начальное состояние Start
  ASSERT_EQ(model.getState(), static_cast<int>(GameState::Start));

  // Проверяем, что после обновления игры состояние изменяется на SpawnFruit
  model.updateGame();
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::SpawnFruit));
}

// Тестирование состояния SpawnFruit
TEST(StateTest, SpawnFruitState) {
  SnakeModel model;
  model.setState(GameState::SpawnFruit);

  // Проверяем, что состояние изменяется на TurnMove после генерации фрукта
  model.updateGame();
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::TurnMove));
}

TEST(StateTest, Win_) {
  SnakeModel model;
  model.getGameInfo().score = SNAKE_SCORE_INCREMENT * SNAKE_MAX_LENGTH;
  model.setState(GameState::EatFruit);
  model.updateGame();
  EXPECT_EQ(model.getGameInfo().score,
            SNAKE_SCORE_INCREMENT + SNAKE_SCORE_INCREMENT * SNAKE_MAX_LENGTH);

  EXPECT_EQ(model.getState(), static_cast<int>(GameState::Win));
}

TEST(StateTest, EmptyState) {
  SnakeModel model;
  model.setState(GameState::MainMenu);
  EXPECT_NO_THROW(model.updateGame());

  model.setState(GameState::EatFruit);
  EXPECT_NO_THROW(model.userInput(UserAction::Start, false));
  EXPECT_NO_THROW(model.userInput(UserAction::Terminate, false));
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::EatFruit));

  model.setState(GameState::Start);
  EXPECT_NO_THROW(model.userInput(UserAction::Start, false));
  EXPECT_NO_THROW(model.userInput(UserAction::Terminate, false));
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::Start));
}

TEST(StateTest, UpLevel) {
  SnakeModel model;
  model.getGameInfo().score = SNAKE_SCORE_FOR_LEVEL - 1;
  model.setState(GameState::EatFruit);
  model.updateGame();
  EXPECT_EQ(model.getGameInfo().level, 2);
}
TEST(StateTest, MoveColission) {
  SnakeModel model;
  model.setState(GameState::Start);
  while (model.getState() != static_cast<int>(GameState::GameOver))
    model.updateGame();
  EXPECT_EQ(model.getGameInfo().level, 1);
}
// Тестирование состояния TurnMove
TEST(StateTest, TurnMoveState) {
  SnakeModel model;
  model.setState(GameState::TurnMove);

  // Проверяем, что направление змеи изменяется при нажатии клавиш
  model.userInput(UserAction::Left, false);
  EXPECT_EQ(
      model.getSnake().getDirection(),
      Snake::Direction::Right);  // Проверьте правильность изменения направления

  // Обновление игры
  model.updateGame();
  // Здесь можно проверить перемещение змейки или другие аспекты
}

// Тестирование инициализации модели
TEST(SnakeModelTest, Initialization) {
  SnakeModel model;

  // Проверка начальных значений
  EXPECT_FALSE(model.getExit());
  EXPECT_EQ(model.getSnake().getBody().size(), SNAKE_BEGIN_SIZE);
  EXPECT_EQ(model.getGameInfo().score, 0);
}

TEST(SnakeModelTest, getFieldSize) {
  SnakeModel model;

  auto size_ = model.getSizeField();
  EXPECT_EQ(size_.first, SNAKE_FIELD_WIDTH);
  EXPECT_EQ(size_.second, SNAKE_FIELD_HEIGHT);
}

TEST(SnakeModelTest, setState_int) {
  SnakeModel model;

  model.setState(11);
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::Win));
}

// Тестирование сохранения и загрузки игры
TEST(SnakeModelTest, SaveLoadGame) {
  SnakeModel model;

  model.getGameInfo().high_score = 42;
  model.saveGame("test_save.txt");

  SnakeModel new_model;
  new_model.loadGame("test_save.txt");

  EXPECT_EQ(new_model.getGameInfo().high_score, 42);
}

// Тестирование обновления игры
TEST(SnakeModelTest, UpdateGame) {
  SnakeModel model;

  model.setState(GameState::TurnMove);
  model.updateGame();

  EXPECT_EQ(model.getState(), static_cast<int>(GameState::TurnMove));
}
// Тестирование основного игрового процесса
TEST(IntegrationTest, BasicGameplay) {
  SnakeModel model;

  // Начинаем игру
  model.userInput(UserAction::Start, false);
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::Start));

  // Переходим к состоянию SpawnFruit
  model.updateGame();
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::SpawnFruit));

  // Обновляем игру, чтобы перейти к TurnMove и проверить движение змейки
  model.updateGame();
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::TurnMove));

  // Проверяем, что игра может перейти в GameOver
  model.userInput(UserAction::Terminate, false);
  EXPECT_EQ(model.getState(), static_cast<int>(GameState::GameOver));

  // Проверяем завершение игры
  model.userInput(UserAction::Terminate, false);
  EXPECT_TRUE(model.getExit());
}

}  // namespace s21::snake