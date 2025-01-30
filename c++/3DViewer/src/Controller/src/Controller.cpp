#include "../include/Controller.h"

namespace s21 {

Controller::Controller(MainWindow* view, ModelViewer3D* model,
                       QtSceneDrawer* drawer)
    : model_(model), drawer_(drawer), view_(view) {
  settings_ = drawer->GetSettings();
  setupConnections();
}

Controller::~Controller() = default;

void Controller::OnOpenFile(const std::string& filePath,
                            ProgressCallback callback) {
  if (callback) {
    model_->SetProgressCallback(
        callback);  // Прокидываем функцию обратной связи если она есть
  }
  model_->ReadSceneAsync(filePath, [this]() {
    QMetaObject::invokeMethod(
        this, [this]() { FinishedLoadFile(); }, Qt::QueuedConnection);
  });
}

void Controller::FinishedLoadFile() {
  FacadeOperationResult result = FacadeOperationResult(true);
  if (model_->GetCurrentScene().Empty()) {
    result = FacadeOperationResult(false, "File not read or empty");
  }
  int vertexCount = model_->GetVertexCount();
  int edgeCount = model_->GetEdgeCount();
  view_->UpdateModelInfo(vertexCount, edgeCount);
  drawer_->setVisible(true);  // Делает виджет видимым
  if (!drawer_) {
    qWarning() << "Ошибка: объект drawer_ не инициализирован!";
  } else {
    drawer_->UpdateView(result, model_->GetCurrentScene());
  }
}
void Controller::OnMove(float dx, float dy, float dz) {
  FacadeOperationResult result = model_->MoveScene(dx, dy, dz);
  drawer_->UpdateViewFrame(result, model_->GetCurrentScene());
}

void Controller::OnRotate(float dx, float dy, float dz) {
  FacadeOperationResult result = model_->RotateScene(dx, dy, dz);
  drawer_->UpdateViewFrame(result, model_->GetCurrentScene());
}

void Controller::OnScale(float scale) {
  FacadeOperationResult result = model_->ScaleScene(scale);
  drawer_->UpdateViewFrame(result, model_->GetCurrentScene());
}

void Controller::setupConnections() {
  connect(view_, &MainWindow::fileOpenRequested, this, &Controller::OnOpenFile);
  connect(view_, &MainWindow::translateModelRequested, this,
          &Controller::OnMove);
  connect(view_, &MainWindow::rotateModelRequested, this,
          &Controller::OnRotate);
  connect(view_, &MainWindow::zoomModelRequested, this, &Controller::OnScale);
  connect(settings_, &ViewSettings::SettingsChanged, drawer_,
          &QtSceneDrawer::OnSettingsChanged);
}

}  // namespace s21