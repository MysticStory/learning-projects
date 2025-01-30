#include "../include/Vertex.h"
namespace s21 {
Vertex::Vertex(float x_, float y_, float z_) : X(x_), Y(y_), Z(z_) {}
Vertex::Vertex() {}

bool Vertex::operator==(const Vertex& other) const {
  return fabsf(this->X - other.X) < 1e-6 && fabsf(this->Y - other.Y) < 1e-6 &&
         fabsf(this->Z - other.Z) < 1e-6;
}

Vertex Vertex::Transform(const TransformMatrix& tranformMatrix) const {
  return tranformMatrix.TransformVertex(*this);
}
}  // namespace s21