#ifndef VERTEX_H_
#define VERTEX_H_

#include <cmath>

#include "TransformMatrix.h"

namespace s21 {
class Vertex {
 public:
  Vertex();
  float X;
  float Y;
  float Z;
  Vertex(float x, float y, float z);
  Vertex Transform(const TransformMatrix& tranformMatrix) const;
  bool operator==(const Vertex& other) const;
};
}  // namespace s21
#endif  // VERTEX_H_