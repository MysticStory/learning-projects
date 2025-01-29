#include "qtview.h"
#include <QMessageBox>
#include <QMap>
namespace s21 {

QtView::QtView(QWidget *parent) : QWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
  setFixedSize(330, 400);  // Размер окна
  initColorMap();
}

void QtView::initialize(int rows, int cols) {
  rows_ = cols;
  cols_ = rows;
}
void QtView::initColorMap() {
    colorMap['#'] = Qt::green;  // Тело змейки
    colorMap['*'] = Qt::red;    // Еда змейки
    colorMap['.'] = Qt::blue;  // Пустое место

  }
void QtView::render(const GameInfo &gameInfo, int currentState) {
  gameInfo_ = gameInfo;
  currentState_ = currentState;
  update();  // Перерисовка виджета
}

std::pair<UserAction, bool> QtView::getUserInput() {
  static int count = 0;
  auto userAction = lastKey_;
  if (userAction == UserAction::NO_ACT) {
    count = 0;
  } else {
    ++count;
  }
  lastKey_ = UserAction::NO_ACT;
  return std::make_pair(userAction, count > 5);
}

void QtView::displayGameOver(int score) {
  QMessageBox::information(this, "Game Over", "Your score: " + QString::number(score));
}

void QtView::cleanUp() {}

void QtView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  drawField(painter);
  drawInfoPanel(painter);
}

void QtView::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      lastKey_ = UserAction::Left;
      break;
    case Qt::Key_Right:
      lastKey_ = UserAction::Right;
      break;
    case Qt::Key_Up:
      lastKey_ = UserAction::Up;
      break;
    case Qt::Key_Down:
      lastKey_ = UserAction::Down;
      break;
    case Qt::Key_Space:
      lastKey_ = UserAction::Action;
      break;
    case Qt::Key_P:
      lastKey_ = UserAction::Pause;
      break;
    case Qt::Key_Q:
      lastKey_ = UserAction::Terminate;
      break;
    case Qt::Key_S:
      lastKey_ = UserAction::Start;
      break;
    default:
      lastKey_ = UserAction::NO_ACT;
      break;
  }
}

void QtView::drawField(QPainter &painter) {
    const auto &field = gameInfo_.field;
    int blockSize = 20;  // Размер одного блока

    for (int x = 0; x < cols_; ++x) {
      for (int y = 0; y < rows_; ++y) {
        QRect rect(x * blockSize, y * blockSize, blockSize, blockSize);

        // Определите цвет в зависимости от символа
        QColor fillColor = colorMap.value(field[x][y], Qt::black); // Цвет по умолчанию - черный
        painter.fillRect(rect, fillColor);
        painter.drawRect(rect); // Рисуем границу блока
      }
    }
  }

void QtView::drawInfoPanel(QPainter &painter) {
  int startX = cols_ * 20 + 20;  // Начало панели информации после поля

  painter.setPen(Qt::black);
  painter.drawText(startX, 20, "Score: " + QString::number(gameInfo_.score));
  painter.drawText(startX, 40, "Level: " + QString::number(gameInfo_.level));
  painter.drawText(startX, 60, "Speed: " + QString::number(gameInfo_.speed));
  painter.drawText(startX, 80, "High Score: " + QString::number(gameInfo_.high_score));
  painter.drawText(startX, 100, currentState_ != 10
                                  ? (gameInfo_.pause ? "Pause" : "Play")
                                  : "Game Over");
  painter.drawText(startX, 120, "Controls:");
  painter.drawText(startX, 140, "Arrows: Move");
  painter.drawText(startX, 160, "'S': Start");
  painter.drawText(startX, 180, currentState_ < 10 ? "'P': Pause" : "'Q': Quit");
}

void QtView::drawBorder(QPainter &painter) {
  painter.setPen(Qt::white);

  // Верхняя граница
  for (int x = 0; x <= cols_; ++x) {
    painter.drawRect(x * 20 + 10, 10, 20, 20);
  }

  // Боковые границы
  for (int y = 0; y < rows_; ++y) {
    painter.drawRect(10, y * 20 + 10, 20, 20);
    painter.drawRect(cols_ * 20 + 10, y * 20 + 10, 20, 20);
  }

  // Нижняя граница
  for (int x = 0; x <= cols_; ++x) {
    painter.drawRect(x * 20 + 10, rows_ * 20 + 10, 20, 20);
  }
}

}  // namespace s21
