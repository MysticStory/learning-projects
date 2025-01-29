#include <gtest/gtest.h>

#include "../src/brick_game/snake/snakeModel.h"
#include "../src/brick_game/snake/statesSnake.h"

namespace s21 {
namespace snake {

class EmptyStateTest : public ::testing::Test {
 protected:
  SnakeModel game;

  void testState(GameState initialState, GameState newState,
                 UserAction action) {
    game.setState(initialState);
    EXPECT_NO_THROW(game.updateGame());
    EXPECT_NO_THROW(game.userInput(action, false));
    EXPECT_EQ(game.getState(), static_cast<int>(newState));
  }
};

// Тест StartState
TEST_F(EmptyStateTest, StartState) {
  testState(GameState::Start, GameState::SpawnFruit, UserAction::Start);
}

// Тест SpawnFruitState
TEST_F(EmptyStateTest, SpawnFruitState) {
  testState(GameState::SpawnFruit, GameState::TurnMove, UserAction::Start);
}

// Тест PausedState
TEST_F(EmptyStateTest, PausedState) {
  testState(GameState::Paused, GameState::TurnMove, UserAction::Start);
  testState(GameState::Paused, GameState::TurnMove, UserAction::Pause);
}

// Тест EatFruitState
TEST_F(EmptyStateTest, EatFruitState) {
  testState(GameState::EatFruit, GameState::SpawnFruit, UserAction::Start);
}

// Тест GameOverState
TEST_F(EmptyStateTest, GameOverState) {
  testState(GameState::GameOver, GameState::Start, UserAction::Start);
  testState(GameState::GameOver, GameState::GameOver, UserAction::Terminate);
}

}  // namespace snake
}  // namespace s21
