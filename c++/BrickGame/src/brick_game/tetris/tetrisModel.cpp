#include "tetrisModel.h"

namespace s21::tetris {

TetrisModel::TetrisModel() : currentState_(nullptr), exit(false) {
  currentField_ =
      new FieldBase(TETRIS_FIELD_WIDTH, TETRIS_FIELD_HEIGHT, TETRIS_EMPTY_CHAR);
  nextField_ =
      new FieldBase(TETRIS_FIELD_WIDTH, TETRIS_FIELD_HEIGHT, TETRIS_EMPTY_CHAR);
  initializeStates();
  resetGame();
}
TetrisModel::~TetrisModel() {
  delete currentField_;
  delete nextField_;
}

Shape& TetrisModel::getShape() { return shape_; }
FieldBase& TetrisModel::getField() const { return *nextField_; }
GameInfo& TetrisModel::getGameInfo() { return game_info_; }
bool TetrisModel::getExit() { return exit; }
void TetrisModel::setExit() { exit = true; }

void TetrisModel::initializeStates() {
  mainMenuState_ = std::make_unique<MainMenuState>(*this);
  startState_ = std::make_unique<StartState>(*this);
  pausedState_ = std::make_unique<PausedState>(*this);
  spawnShapeState_ = std::make_unique<SpawnShapeState>(*this);
  movingState_ = std::make_unique<MovingState>(*this);
  shiftingState_ = std::make_unique<ShiftingState>(*this);
  movingState_ = std::make_unique<MovingState>(*this);
  attachingState_ = std::make_unique<AttachingState>(*this);
  gameOverState_ = std::make_unique<GameOverState>(*this);
  currentState_ = mainMenuState_.get();  // Изначально активное состояние
}

void TetrisModel::setState(GameState state) {
  currentGameState_ = state;
  switch (state) {
    case GameState::MainMenu:
      currentState_ = mainMenuState_.get();
      break;
    case GameState::Start:
      currentState_ = startState_.get();
      break;
    case GameState::Paused:
      currentState_ = pausedState_.get();
      break;
    case GameState::SpawnShape:
      currentState_ = spawnShapeState_.get();
      break;
    case GameState::Moving:
      currentState_ = movingState_.get();
      break;
    case GameState::Shifting:
      currentState_ = shiftingState_.get();
      break;
    case GameState::Attaching:
      currentState_ = attachingState_.get();
      break;
    case GameState::GameOver:
      currentState_ = gameOverState_.get();
      break;

    default:
      throw std::invalid_argument("Неизвестное состояние");
  }
}

std::pair<int, int> TetrisModel::getSizeField() {
  return std::make_pair(currentField_->getWidth(), currentField_->getHeight());
}

void TetrisModel::setState(int state) {
  setState(static_cast<GameState>(state));
}

void TetrisModel::userInput(UserAction action, bool hold) {
  currentState_->userInput(action, hold);
}

void TetrisModel::updateGame() {
  if (getState() < 10) currentField_->copyFrom(*nextField_);
  currentState_->updateGame();
}

const GameInfo& TetrisModel::getGameInfo() const { return game_info_; }

void TetrisModel::resetGame() {
  game_info_ = GameInfo();
  currentField_->clearField();
  nextField_->clearField();
  game_info_.field = currentField_->getField();
  game_info_.next = nextField_->getField();
  game_info_.speed = TETRIS_INITIAL_SPEED;
  loadGame(PATH_TETRIS);
}

void TetrisModel::spawnShape() { shape_ = Shape(); }

void TetrisModel::saveGame(const std::string& filepath) const {
  std::filesystem::path DIRECTORY = "build";
  std::filesystem::path path_ = DIRECTORY / filepath;
  std::ofstream file(path_);
  if (!file.is_open()) {
    throw std::runtime_error("Невозможно открыть файл для записи");
  }
  file << game_info_.high_score;
}

void TetrisModel::loadGame(const std::string& filepath) {
  std::filesystem::path DIRECTORY = "build";
  std::filesystem::path path_ = DIRECTORY / filepath;

  std::ifstream file(path_);

  if (!file.is_open()) {
    // Файл не открылся, значит, возможно, он не существует
    std::ofstream newFile(path_);  // Попытка создать новый файл
    if (!newFile) {
      throw std::runtime_error("Не удалось создать файл для записи");
    }
    // Записываем начальное значение
    game_info_.high_score = 0;
    newFile << game_info_.high_score;
    newFile.close();
    return;
  }

  // Если файл успешно открыт, читаем значение
  file >> game_info_.high_score;
}

int TetrisModel::getState() const {
  return static_cast<int>(currentGameState_);
}

}  // namespace s21
