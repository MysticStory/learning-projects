#include <gtest/gtest.h>

#include "../src/brick_game/tetris/statesTetris.h"
#include "../src/brick_game/tetris/tetrisModel.h"

namespace s21::tetris {

TEST(MainMenuStateTest, StartGame) {
  TetrisModel game;
  MainMenuState mainMenu(game);

  mainMenu.userInput(UserAction::Start, false);

  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Start));
}

TEST(StartStateTest, TransitionToSpawnShape) {
  TetrisModel game;
  StartState startState(game);

  startState.updateGame();

  EXPECT_EQ(game.getState(), static_cast<int>(GameState::SpawnShape));
}

TEST(SpawnShapeStateTest, SpawnNewShape) {
  TetrisModel game;
  SpawnShapeState spawnShape(game);

  game.setState(GameState::SpawnShape);
  spawnShape.updateGame();

  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Moving));
}

TEST(MovingStateTest, MoveRightWithoutCollision) {
  TetrisModel game;
  game.setState(GameState::Moving);
  game.getShape().setBlocks({{4, 0}, {5, 0}, {6, 0}, {7, 0}});
  MovingState movingState(game);

  movingState.userInput(UserAction::Right, false);
  movingState.updateGame();

  auto blocks = game.getShape().getBlocks();
  EXPECT_EQ(blocks[0], std::make_pair(5, 0));
  EXPECT_EQ(blocks[1], std::make_pair(6, 0));
  EXPECT_EQ(blocks[2], std::make_pair(7, 0));
  EXPECT_EQ(blocks[3], std::make_pair(8, 0));
}

TEST(TestModel, getSetExist) {
  TetrisModel game;
  game.setState(GameState::Start);
  game.setExit();
  EXPECT_EQ(game.getExit(), true);
}
TEST(TestModel, getFieldSize) {
  TetrisModel model;

  auto size_ = model.getSizeField();
  EXPECT_EQ(size_.first, TETRIS_FIELD_WIDTH);
  EXPECT_EQ(size_.second, TETRIS_FIELD_HEIGHT);
}

TEST(TestModel, errorState) {
  TetrisModel game;
  EXPECT_THROW(game.setState(22), std::invalid_argument);
}
TEST(TestModel, MainMenuState_) {
  TetrisModel game;
  game.setState(GameState::MainMenu);
  EXPECT_NO_THROW(game.updateGame());
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_EQ(game.getExit(), true);
}

TEST(TestModel, StartState_) {
  TetrisModel game;
  game.setState(GameState::Start);
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_NO_THROW(game.userInput(UserAction::Left, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Start));
}
TEST(TestModel, AtathState_) {
  TetrisModel game;
  game.setState(GameState::Attaching);
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_NO_THROW(game.userInput(UserAction::Left, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Attaching));
}
TEST(TestModel, SpawnState_) {
  TetrisModel game;
  game.setState(GameState::SpawnShape);
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_NO_THROW(game.userInput(UserAction::Left, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::SpawnShape));
}
TEST(TestModel, ShiftState_) {
  TetrisModel game;
  game.setState(GameState::Shifting);
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_NO_THROW(game.userInput(UserAction::Left, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Shifting));
}
TEST(TestModel, MoveShift) {
  TetrisModel game;
  game.setState(GameState::Start);
  game.updateGame();
  game.updateGame();
  auto pos = game.getShape().getCentr();
  EXPECT_NO_THROW(game.userInput(UserAction::Left, false));
  for (int i = 0; i < 6; i++) game.updateGame();
  auto pos_new = game.getShape().getCentr();
  EXPECT_EQ(pos_new.first + 1, pos.first);
  EXPECT_NO_THROW(game.userInput(UserAction::Right, false));
  for (int i = 0; i < 6; i++) game.updateGame();
  pos_new = game.getShape().getCentr();
  EXPECT_EQ(pos_new.first, pos.first);
  EXPECT_NO_THROW(game.userInput(UserAction::Action, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Shifting));
  game.updateGame();
}
TEST(TestModel, PauseState_) {
  TetrisModel game;
  game.setState(GameState::Moving);
  EXPECT_NO_THROW(game.userInput(UserAction::Pause, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Paused));
  EXPECT_NO_THROW(game.updateGame());
  EXPECT_NO_THROW(game.userInput(UserAction::Pause, false));
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Moving));
}
TEST(TestModel, GameOver_) {
  TetrisModel game;
  game.setState(GameState::Start);
  while (game.getState() != 10) game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::GameOver));
  EXPECT_NO_THROW(game.updateGame());
  EXPECT_NO_THROW(game.userInput(UserAction::Terminate, false));
  EXPECT_EQ(game.getExit(), true);
}

TEST(AttachingStateTest, ClearFullRow) {
  TetrisModel game;
  AttachingState attachingState(game);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j)
      game.getField().setCell(j, i, TETRIS_BLOCK_CHAR);
  int clearedRows = attachingState.clearFullRows();

  EXPECT_EQ(clearedRows, 4);
  EXPECT_EQ(game.getField().getCell(0, 0), TETRIS_EMPTY_CHAR);
}

TEST(GameOverStateTest, TransitionToStart) {
  TetrisModel game;
  GameOverState gameOverState(game);

  gameOverState.userInput(UserAction::Start, false);

  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Start));
}

TEST(TetrisModelTest, StateTransitions) {
  TetrisModel game;

  game.userInput(UserAction::Start, false);
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Start));

  game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::SpawnShape));

  game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Moving));

  game.userInput(UserAction::Terminate, false);
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::GameOver));
}

TEST(TetrisModelTest, SpawnShapeOnStart) {
  TetrisModel game;

  game.userInput(UserAction::Start, false);
  game.updateGame();

  game.updateGame();

  auto blocks = game.getShape().getBlocks();
  EXPECT_FALSE(blocks.empty());
}

TEST(IntegrationTest, FullGameCycle) {
  TetrisModel game;

  game.userInput(UserAction::Start, false);
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Start));

  game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::SpawnShape));

  game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::Moving));

  game.userInput(UserAction::Right, false);
  game.updateGame();
  game.getShape().setBlocks({std::make_pair(0, 0)});
  auto blocks = game.getShape().getBlocks();
  EXPECT_EQ(blocks[0].second, 0);
  while (game.getState() != static_cast<int>(GameState::Attaching)) {
    game.updateGame();
  }

  game.updateGame();
  EXPECT_EQ(game.getState(), static_cast<int>(GameState::SpawnShape));
}
}  // namespace s21::tetris