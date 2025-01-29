#include "statesTetris.h"

#include "tetrisModel.h"

namespace s21::tetris {

// MainMenu ------------------------------------------------------------
MainMenuState::MainMenuState(TetrisModel& game) : game_(game) {}

void MainMenuState::userInput(UserAction action, bool hol [[maybe_unused]]) {
  if (action == UserAction::Start) {
    game_.setState(GameState::Start);
  } else if (action == UserAction::Terminate) {
    game_.setExit();
  }
}

void MainMenuState::updateGame() {}
// StartState ------------------------------------------------------------
StartState::StartState(TetrisModel& game) : game_(game) {}

void StartState::userInput(UserAction action [[maybe_unused]],
                           bool hold [[maybe_unused]]) {}

void StartState::updateGame() {
  game_.resetGame();
  game_.setState(GameState::SpawnShape);
}

// SpawnShapeState ------------------------------------------------------------
SpawnShapeState::SpawnShapeState(TetrisModel& game) : game_(game) {}

void SpawnShapeState::userInput(UserAction action [[maybe_unused]],
                                bool hold [[maybe_unused]]) {}

void SpawnShapeState::updateGame() {
  game_.spawnShape();
  bool collision = false;
  for (const auto& segment : game_.getShape().getBlocks()) {
    int x = segment.first;
    int y = segment.second;
    if (game_.getField().getCell(x, y) != TETRIS_EMPTY_CHAR) {
      collision = true;
      break;
    }
  }
  if (collision) {
    game_.setState(GameState::GameOver);
  }

  else {
    for (const auto& segment : game_.getShape().getBlocks()) {
      int x = segment.first;
      int y = segment.second;
      game_.getField().setCell(x, y, TETRIS_BLOCK_CHAR);
    }
    game_.setState(GameState::Moving);
  }
}

// MovingState ------------------------------------------------------------
MovingState::MovingState(TetrisModel& game) : game_(game), forceSpeed(false) {}

void MovingState::userInput(UserAction action, bool hold [[maybe_unused]]) {
  forceSpeed = hold;
  switch (action) {
    case UserAction::Left:
      game_.getShape().setMoved(Shape::Moved::Left);
      break;
    case UserAction::Right:
      game_.getShape().setMoved(Shape::Moved::Rigth);
      break;
    case UserAction::Down:
      game_.getShape().setMoved(Shape::Moved::Down);
      break;
    case UserAction::Pause:
      game_.getGameInfo().pause = true;
      game_.setState(GameState::Paused);
      break;
    case UserAction::Terminate:
      game_.setState(GameState::GameOver);
      break;
    case UserAction::Action:
      game_.setState(GameState::Shifting);
      break;
    default:
      break;
  }
}
bool MovingState::canMove(int dir) {
  bool collision = false;
  auto old_pos = game_.getShape().getBlocks();
  auto old_centr = game_.getShape().getCentr();
  for (const auto& segment : old_pos) {
    int x = segment.first;
    int y = segment.second;
    game_.getField().setCell(x, y, TETRIS_EMPTY_CHAR);
  }
  game_.getShape().move(dir);
  for (const auto& segment : game_.getShape().getBlocks()) {
    int x = segment.first;
    int y = segment.second;
    if (game_.getField().getCell(x, y) != TETRIS_EMPTY_CHAR) {
      collision = true;
      break;
    }
  }
  if (collision) {
    game_.getShape().setBlocks(old_pos);
    game_.getShape().setCentr(old_centr);
  }
  for (const auto& segment : game_.getShape().getBlocks()) {
    int x = segment.first;
    int y = segment.second;
    game_.getField().setCell(x, y, TETRIS_BLOCK_CHAR);
  }
  return collision;
}
void MovingState::updateGame() {
  static int count = 0;

  if (count % 5 == 0) {
    if (game_.getShape().getMoved() != Shape::Moved::NO) {
      int dir = static_cast<int>(game_.getShape().getMoved());
      if (dir != 2) game_.getShape().setMoved(Shape::Moved::NO);
      bool collision = canMove(dir);
      if (collision && dir == 2) game_.setState(GameState::Attaching);
    }
  }

  int speed = game_.getGameInfo().speed;
  if (count >= TETRIS_BASE_SPEED / speed) {
    bool collision = canMove(2);
    if (collision) game_.setState(GameState::Attaching);
    count = 0;
  } else {
    count++;
  }
}
// AttachingState ------------------------------------------------------------
AttachingState::AttachingState(TetrisModel& game) : game_(game) {}

void AttachingState::userInput(UserAction action [[maybe_unused]],
                               bool hold [[maybe_unused]]) {}
int AttachingState::clearFullRows() {
  int rowsCleared = 0;
  int height_ = game_.getField().getHeight();
  int width_ = game_.getField().getWidth();
  // Проходим по всем строкам поля
  for (int y = 0; y < height_; ++y) {
    bool fullRow = true;

    // Проверяем, заполнена ли строка
    for (int x = 0; x < width_; ++x) {
      if (game_.getField().getCell(x, y) == TETRIS_EMPTY_CHAR) {
        fullRow = false;
        break;
      }
    }

    if (fullRow) {
      // Удаляем строку и смещаем строки выше вниз
      for (int row = y; row > 0; --row) {
        for (int x = 0; x < width_; ++x) {
          game_.getField().setCell(x, row,
                                   game_.getField().getCell(x, row - 1));
        }
      }

      // Очищаем верхнюю строку
      for (int x = 0; x < width_; ++x) {
        game_.getField().setCell(x, 0, TETRIS_EMPTY_CHAR);
      }

      // Увеличиваем счетчик удаленных строк
      ++rowsCleared;

      // После удаления строки нужно проверить текущую строку снова
      --y;
    }
  }

  return rowsCleared;
}
void AttachingState::updateGame() {
  game_.getShape().setMoved(Shape::Moved::NO);
  int add_score = static_cast<int>(pow(2, clearFullRows()) - 1);
  game_.getGameInfo().score += add_score * TETRIS_SCORE_INCREMENT;

  if (game_.getGameInfo().score > 600) {
    game_.getGameInfo().level = 1 + game_.getGameInfo().score / 600;
    game_.getGameInfo().speed =
        TETRIS_SPEED_INCREMENT * (game_.getGameInfo().level - 1) +
        TETRIS_INITIAL_SPEED;
  }
  if (game_.getGameInfo().score > game_.getGameInfo().high_score)
    game_.getGameInfo().high_score = game_.getGameInfo().score;

  game_.setState(GameState::SpawnShape);
}
// ShiftingState ------------------------------------------------------------
ShiftingState::ShiftingState(TetrisModel& game) : game_(game) {}

void ShiftingState::userInput(UserAction action [[maybe_unused]],
                              bool hold [[maybe_unused]]) {}

void ShiftingState::updateGame() {
  bool collision = false;
  auto old_pos = game_.getShape().getBlocks();
  auto old_centr = game_.getShape().getCentr();
  for (const auto& segment : old_pos) {
    int x = segment.first;
    int y = segment.second;
    game_.getField().setCell(x, y, TETRIS_EMPTY_CHAR);
  }
  game_.getShape().Rotate();
  for (const auto& segment : game_.getShape().getBlocks()) {
    int x = segment.first;
    int y = segment.second;
    if (game_.getField().getCell(x, y) != TETRIS_EMPTY_CHAR) {
      collision = true;
      break;
    }
  }
  if (collision) {
    game_.getShape().setBlocks(old_pos);
    game_.getShape().setCentr(old_centr);
  }
  for (const auto& segment : game_.getShape().getBlocks()) {
    int x = segment.first;
    int y = segment.second;
    game_.getField().setCell(x, y, TETRIS_BLOCK_CHAR);
  }
  game_.setState(GameState::Moving);
}
// PausedState ------------------------------------------------------------
PausedState::PausedState(TetrisModel& game) : game_(game) {}

void PausedState::userInput(UserAction action [[maybe_unused]],
                            bool hold [[maybe_unused]]) {
  if (UserAction::Pause == action || UserAction::Start == action) {
    game_.getGameInfo().pause = false;
    game_.setState(GameState::Moving);
  }
}

void PausedState::updateGame() {}

// GameOverState ------------------------------------------------------------
GameOverState::GameOverState(TetrisModel& game) : game_(game) {}

void GameOverState::userInput(UserAction action [[maybe_unused]],
                              bool hold [[maybe_unused]]) {
  game_.saveGame(PATH_TETRIS);
  if (action == UserAction::Start) {
    game_.setState(GameState::Start);
  } else if (action == UserAction::Terminate) {
    game_.setExit();
  }
}

void GameOverState::updateGame() {}

}  // namespace s21