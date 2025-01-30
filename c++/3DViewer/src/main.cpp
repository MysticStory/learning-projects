#include <locale.h>

#include <QApplication>

#include "Controller/include/Controller.h"
#include "Model/include/ModelViewer3D.h"
#include "View/include/mainwindow.h"
using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");

  ModelViewer3D model;
  MainWindow view;
  Controller controller(&view, &model, view.sceneDrawer_);
  view.show();

  return a.exec();
}
