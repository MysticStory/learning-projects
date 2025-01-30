#include "../include/ModelViewer3D.h"

#include <iostream>

namespace s21 {

FacadeOperationResult ModelViewer3D::LoadScene(std::string path) {
  _scene = _fileReader.ReadScene(path);

  bool testEmpty = _scene.Empty();
  if (testEmpty) return FacadeOperationResult(false, "File not read or empty");

  return FacadeOperationResult(true);
}

void ModelViewer3D::ReadSceneAsync(const std::string& path,
                                   std::function<void()> callback) {
  // Запускаем асинхронный поток
  std::thread([this, path, callback]() {
    Scene result = _fileReader.ReadScene(path);
    {
      std::lock_guard<std::mutex> lock(scene_mutex);
      _scene = result;
    }
    // Вызываем callback-функцию
    if (callback) {
      callback();
    }
  }).detach();
}

void ModelViewer3D::SetScene(Scene& scene) { _scene = scene; }

void ModelViewer3D::SetProgressCallback(ProgressCallback callback) {
  _fileReader.SetProgressCallback(std::move(callback));
}

FacadeOperationResult ModelViewer3D::MoveScene(float x, float y, float z) {
  for (auto& figure : _scene.GetFigures()) {
    figure.state[0][0] = x;
    figure.state[0][1] = y;
    figure.state[0][2] = z;
  }

  return UpdateTransformMatrix();
}

FacadeOperationResult ModelViewer3D::RotateScene(float rx, float ry, float rz) {
  for (auto& figure : _scene.GetFigures()) {
    figure.state[1][0] = rx;
    figure.state[1][1] = ry;
    figure.state[1][2] = rz;
  }

  return UpdateTransformMatrix();
}

FacadeOperationResult ModelViewer3D::ScaleScene(float scale) {
  for (auto& figure : _scene.GetFigures()) {
    figure.state[2][0] = scale;
    figure.state[2][1] = scale;
    figure.state[2][2] = scale;
  }
  return UpdateTransformMatrix();
}

FacadeOperationResult ModelViewer3D::UpdateTransformMatrix() {
  for (auto& figure : _scene.GetFigures()) {
    figure.transformationMatrix = TransformMatrix();
    figure.transformationMatrix
        .Move(figure.state[0][0], figure.state[0][1], figure.state[0][2])
        .Rotate(figure.state[1][0], figure.state[1][1], figure.state[1][2])
        .Scale(figure.state[2][0], figure.state[2][1], figure.state[2][2]);
  }
  return FacadeOperationResult(true);
}

Scene& ModelViewer3D::GetCurrentScene() { return _scene; }

int ModelViewer3D::GetVertexCount() const { return _scene.GetVertexCount(); }
int ModelViewer3D::GetEdgeCount() const { return _scene.GetEdgeCount(); }

ModelViewer3D::ModelViewer3D() {}

ModelViewer3D::~ModelViewer3D() {}
}  // namespace s21
