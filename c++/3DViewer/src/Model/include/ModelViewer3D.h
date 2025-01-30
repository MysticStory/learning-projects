#ifndef MODEL_VIWER_3D_H
#define MODEL_VIWER_3D_H

#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include "../../Geometry/include/Scene.h"
#include "FacadeOperationResult.h"
#include "FileReader.h"

namespace s21 {

class ModelViewer3D {
 public:
  using ProgressCallback = std::function<void(int)>;
  ModelViewer3D(/* args */);
  ~ModelViewer3D();
  FacadeOperationResult DrawScene();
  FacadeOperationResult LoadScene(
      std::string path);  // загружает сцену с нормализацией

  void ReadSceneAsync(const std::string& path, std::function<void()> callback);
  FacadeOperationResult MoveScene(float x, float y,
                                  float z);  // перемещает сцену по осям x, y, z
  FacadeOperationResult RotateScene(float x, float y,
                                    float z);  // вращает сцену по осям x, y, z

  FacadeOperationResult ScaleScene(float scale);  // масштабирует сцену по осям

  void SetScene(Scene& scene);
  Scene& GetCurrentScene();

  int GetVertexCount() const;
  int GetEdgeCount() const;

  void SetProgressCallback(ProgressCallback callback);

 private:
  FileReader _fileReader;
  Scene _scene;
  FacadeOperationResult UpdateTransformMatrix();
  std::mutex scene_mutex;
};

}  // namespace s21

#endif  // MODEL_VIWER_3D_H