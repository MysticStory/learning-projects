#include "snakeModel.h"

namespace s21 {
namespace snake {
SnakeModel::SnakeModel() : currentState_(nullptr), exit(false) {
  currentField_ =
      new FieldBase(SNAKE_FIELD_WIDTH, SNAKE_FIELD_HEIGHT, SNAKE_EMPTY_CHAR);
  nextField_ =
      new FieldBase(SNAKE_FIELD_WIDTH, SNAKE_FIELD_HEIGHT, SNAKE_EMPTY_CHAR);
  initializeStates();
  resetGame();
}
SnakeModel::~SnakeModel() {
  delete currentField_;
  delete nextField_;
}

Snake& SnakeModel::getSnake() { return snake_; }
FieldBase& SnakeModel::getField() const { return *nextField_; }
GameInfo& SnakeModel::getGameInfo() { return game_info_; }
bool SnakeModel::getExit() { return exit; }
void SnakeModel::setExit() { exit = true; }

void SnakeModel::initializeStates() {
  mainMenuState_ = std::make_unique<MainMenuState>(*this);
  startState_ = std::make_unique<StartState>(*this);
  pausedState_ = std::make_unique<PausedState>(*this);
  spawnFruitState_ = std::make_unique<SpawnFruitState>(*this);
  turnMoveState_ = std::make_unique<TurnMoveState>(*this);
  eatFruitState_ = std::make_unique<EatFruitState>(*this);
  gameOverState_ = std::make_unique<GameOverState>(*this);
  winState_ = std::make_unique<GameOverState>(*this);
  currentState_ = mainMenuState_.get();  // Изначально активное состояние
}

void SnakeModel::setState(GameState state) {
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
    case GameState::SpawnFruit:
      currentState_ = spawnFruitState_.get();
      break;
    case GameState::TurnMove:
      currentState_ = turnMoveState_.get();
      break;
    case GameState::EatFruit:
      currentState_ = eatFruitState_.get();
      break;
    case GameState::GameOver:
      currentState_ = gameOverState_.get();
      break;
    case GameState::Win:
      currentState_ = winState_.get();
      break;
    default:
      throw std::invalid_argument("Неизвестное состояние");
  }
}

std::pair<int, int> SnakeModel::getSizeField() {
  return std::make_pair(currentField_->getWidth(), currentField_->getHeight());
}

void SnakeModel::setState(int state) {
  setState(static_cast<GameState>(state));
}

void SnakeModel::userInput(UserAction action, bool hold) {
  currentState_->userInput(action, hold);
}

void SnakeModel::updateGame() {
  if (getState() < 10) currentField_->copyFrom(*nextField_);
  currentState_->updateGame();
}

const GameInfo& SnakeModel::getGameInfo() const { return game_info_; }

void SnakeModel::resetGame() {
  game_info_ = GameInfo();
  currentField_->clearField();
  nextField_->clearField();
  game_info_.field = currentField_->getField();
  game_info_.next = nextField_->getField();
  game_info_.speed = SNAKE_INITIAL_SPEED;
  loadGame(PATH_SNAKE);
}

void SnakeModel::spawnSnake() {
  snake_ = Snake();
  for (const auto& segment : snake_.getBody()) {
    int x = segment.first;
    int y = segment.second;
    nextField_->setCell(x, y, SNAKE_BODY_CHAR);
  }
}

void SnakeModel::saveGame(const std::string& filepath) const {
  std::filesystem::path DIRECTORY = "build";
  std::filesystem::path path_ = DIRECTORY / filepath;
  std::ofstream file(path_);
  if (!file.is_open()) {
    throw std::runtime_error("Невозможно открыть файл для записи");
  }
  file << game_info_.high_score;
}

void SnakeModel::loadGame(const std::string& filepath) {
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

int SnakeModel::getState() const { return static_cast<int>(currentGameState_); }
}  // namespace snake
}  // namespace s21
