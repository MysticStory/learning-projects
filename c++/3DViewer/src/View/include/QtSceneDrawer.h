#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QInputDialog>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QShowEvent>
#include <QVector3D>
#include <iostream>
#include <map>

#include "../../Model/include/FacadeOperationResult.h"
#include "SceneDrawerBase.h"
namespace s21 {

struct buffersGL {
  buffersGL(GLuint vbo_, GLuint ebo_, long int countVertics_,
            long int countEdges_)
      : vbo(vbo_),
        ebo(ebo_),
        countVertics(countVertics_),
        countEdges(countEdges_) {}

  GLuint vbo = 0;  // Vertex Buffer Object
  GLuint ebo = 0;  // Element Buffer Object
  long int countVertics = 0;
  long int countEdges = 0;
};

class QtSceneDrawer : public QOpenGLWidget,
                      public SceneDrawerBase,
                      protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit QtSceneDrawer(QWidget* parent = nullptr);
  ~QtSceneDrawer() override;

  void DrawScene() override;

 public slots:
  void OnSettingsChanged();
  void UpdateView(FacadeOperationResult result, Scene& scene);
  void UpdateViewFrame(FacadeOperationResult result, Scene& scene);

 public:
  ViewSettings* GetSettings();

 signals:
  void OpenFileSignal(std::string path);
  void ModelInfoUpdated(
      const QString& filePath, const QString& modelName, int verticesNumber,
      int edgesNumber);  // Сигнал для обновления информации о модели
  void zoomChanged(float zoom);  // Сигнал об изменении масштаба

 protected:
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void initializeGL() override;

 private:
  ViewSettings* settings_;
  Scene* scene_;
  void setViewType(bool type);
  // отрисовка
  std::map<Figure*, buffersGL> mapBuffers;

  void ClearBuffers();
  buffersGL CreateBuffers(Figure& figure);
  void Draw(buffersGL buffer);
  void UpdateVertexBuffer(buffersGL buffer,
                          const std::vector<Vertex>& bufferGl);
  void CheckGLError(QString location);
};
}  // namespace s21

#endif  // QTSCENEDRAWER_H
