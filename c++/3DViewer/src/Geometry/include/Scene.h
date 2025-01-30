#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Figure.h"
#include "TransformMatrix.h"
namespace s21 {
class MinMax {
 public:
  float min_x = -1, max_x = 1, min_y = -1, max_y = 1, min_z = -1, max_z = 1;
};
class Scene {
 public:
  Scene(const std::vector<Figure>& figures);
  Scene();
  ~Scene() = default;
  std::vector<Figure>& GetFigures();
  void SetFigures(const std::vector<Figure>& figures);
  void AddFigure(const Figure& figure);
  void TransformFigures(const TransformMatrix& matrix);
  bool Empty();
  int GetVertexCount() const;
  int GetEdgeCount() const;
  MinMax params;

 private:
  std::vector<Figure> _figures;
};
}  // namespace s21
#endif  // SCENE_H_