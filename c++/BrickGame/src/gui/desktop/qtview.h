#ifndef QT_VIEW_H_
#define QT_VIEW_H_

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "../IView.h"

namespace s21 {

class QtView : public QWidget, public IView {
  Q_OBJECT

 public:
  explicit QtView(QWidget *parent = nullptr);

  void initialize(int rows, int cols) override;
  void render(const GameInfo &gameInfo, int currentState) override;
  std::pair<UserAction, bool> getUserInput() override;
  void displayGameOver(int score) override;
  void cleanUp() override;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  UserAction lastKey_;
  int rows_;
  int cols_;
  GameInfo gameInfo_;
  int currentState_;
  QMap<char, QColor> colorMap;

  void initColorMap();
  void drawField(QPainter &painter);
  void drawInfoPanel(QPainter &painter);
  void drawBorder(QPainter &painter);
};

}  // namespace s21

#endif  // QT_VIEW_H_

