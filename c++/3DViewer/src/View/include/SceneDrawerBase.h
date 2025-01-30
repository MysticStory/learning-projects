#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H

#include "../../Geometry/include/Scene.h"
#include "ViewSettings.h"

namespace s21 {

class SceneDrawerBase {
 public:
  SceneDrawerBase() = default;
  virtual ~SceneDrawerBase() = default;

  virtual void DrawScene() = 0;
};

}  // namespace s21

#endif  // SCENEDRAWERBASE_H