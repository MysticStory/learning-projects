#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <iostream>

#include "../../Model/include/ModelViewer3D.h"
#include "../../View/include/QtSceneDrawer.h"
#include "../../View/include/ViewSettings.h"
#include "../../View/include/mainwindow.h"

namespace s21 {
class MainWindow;

class Controller : public QObject {
  Q_OBJECT

 public:
  explicit Controller(MainWindow* view, ModelViewer3D* model,
                      QtSceneDrawer* drawer);
  ~Controller();
  using ProgressCallback = std::function<void(int)>;

 public slots:

  void OnOpenFile(const std::string& filePath,
                  ProgressCallback callback = nullptr);

  void OnMove(float dx, float dy, float dz);
  void OnRotate(float dx, float dy, float dz);
  void OnScale(float scale);

 private:
  ModelViewer3D* model_;   // Указатель на модель
  QtSceneDrawer* drawer_;  // Указатель на отрисовщик
  MainWindow* view_;       // Указатель на представление
  ViewSettings* settings_;  // Указатель на настройки визуализации
  void FinishedLoadFile();
  void setupConnections();

 private slots:
};

}  // namespace s21

#endif  // CONTROLLER_H
