#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QColorDialog>
#include <QDir>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "GifRecorder.h"
#include "QtSceneDrawer.h"
#include "StyleHelper.h"
#include "ViewSettings.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  using ProgressCallback = std::function<void(int)>;
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QtSceneDrawer* sceneDrawer_ = nullptr;
  void UpdateModelInfo(int vertexCount, int edgeCount);

  void setZoomValue(float value);  // Обновление Zoom_lineEdit
  void setRotationValues(float x, float y,
                         float z);  // Обновление Rotation_lineEdit
  void setPositionValues(float x, float y,
                         float z);  // Обновление Position_lineEdit

 signals:
  void fileOpenRequested(std::string fileName,
                         ProgressCallback callback = nullptr);
  void rotateModelRequested(float x, float y, float z);
  void translateModelRequested(float x, float y, float z);
  void zoomModelRequested(float zoom);
  void centeringModelRequested();

 protected:
  void closeEvent(QCloseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private slots:
  void onOpenFileButtonClicked();
  void onBackgroundColorButtonClicked();
  void on_BackgroundColor_lineEdit_textChanged(const QString& arg1);
  void onEdgeLineColorButtonClicked();
  void onVertexPointColorButtonClicked();
  void on_EdgeLineColor_lineEdit_textChanged(const QString& arg1);
  void on_VertexPointColor_lineEdit_textChanged(const QString& arg1);
  void on_EdgeLineThickness_lineEdit_textChanged(const QString& arg1);
  void on_VertexPointSize_lineEdit_textChanged(const QString& arg1);

  void DottedEdgeLineTypeSelected(bool checked);
  void SolidEdgeLineTypeSelected(bool checked);
  void VertexDisplayAsCircleSelected(bool checked);
  void VertexDisplayAsSquareSelected(bool checked);
  void VertexNotDisplayedSelected(bool checked);
  void ParallelProjectionTypeSelected(bool checked);
  void CentralProjectionTypeSelected(bool checked);
  void onPushButtonSaveImageClicked();

  void onBackgroundResetButtonClicked();
  void onEdgeLineResetButtonClicked();
  void onVertexPointResetButtonClicked();
  void onFactoryResetButtonClicked();

  void GetRotateSlider();
  void GetRotateEdit();
  void GetTranslate();

  void on_ZoomIn_pushButton_clicked();
  void on_ZoomOut_pushButton_clicked();
  void on_Zoom_lineEdit_editingFinished();

  void on_Centering_pushButton_clicked();

 private:
  Ui::MainWindow* ui = nullptr;
  ViewSettings* viewSettings_ = nullptr;

  QTimer* zoomInTimer_ = nullptr;
  QTimer* zoomOutTimer_ = nullptr;

  GifRecorder* gifRecorder;
  void captureScreenshot();
  void toggleRecording();

  QDir GetAplicationPath() const;
  void ApplySettings();
  void setInterfaceStyle();
  void setupConnections();
  QColor getContrastColor(const QColor& backgroundColor);
  void applyContrastTextToLineEdit(QLineEdit* lineEdit,
                                   const QString& backgroundColor);

  void TestCallback(int val);
};

}  // namespace s21

#endif  // MAINWINDOW_H
