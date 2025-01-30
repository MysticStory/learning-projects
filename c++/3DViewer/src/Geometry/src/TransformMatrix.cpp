#include "../include/TransformMatrix.h"

#include <cmath>  // для функций cos и sin

#include "../include/Vertex.h"
namespace s21 {

TransformMatrix::TransformMatrix() {
  // Инициализация матрицы как единичной матрицы
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      _matr[i][j] = (i == j) ? 1.0f : 0.0f;
    }
  }
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix& other) {
  TransformMatrix result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result._matr[i][j] = 0;
      for (int k = 0; k < 4; ++k) {
        result._matr[i][j] += _matr[i][k] * other._matr[k][j];
      }
    }
  }
  return result;
}

Vertex TransformMatrix::TransformVertex(const Vertex& point) const {
  float x_new = _matr[0][0] * point.X + _matr[0][1] * point.Y +
                _matr[0][2] * point.Z + _matr[0][3];
  float y_new = _matr[1][0] * point.X + _matr[1][1] * point.Y +
                _matr[1][2] * point.Z + _matr[1][3];
  float z_new = _matr[2][0] * point.X + _matr[2][1] * point.Y +
                _matr[2][2] * point.Z + _matr[2][3];
  return Vertex(x_new, y_new, z_new);
}

// Метод для создания матрицы смещения
TransformMatrix TransformMatrix::CreateTranslationMatrix(float tx, float ty,
                                                         float tz) {
  TransformMatrix matrix;
  matrix._matr[0][3] = tx;
  matrix._matr[1][3] = ty;
  matrix._matr[2][3] = tz;
  return matrix;
}

// Метод для создания матрицы масштабирования
TransformMatrix TransformMatrix::CreateScaleMatrix(float sx, float sy,
                                                   float sz) {
  TransformMatrix matrix;
  matrix._matr[0][0] = sx;
  matrix._matr[1][1] = sy;
  matrix._matr[2][2] = sz;
  return matrix;
}

// Метод для создания матрицы поворота вокруг оси X
TransformMatrix TransformMatrix::CreateRotationXMatrix(float theta) {
  TransformMatrix matrix;
  float cos_theta = cos(theta);
  float sin_theta = sin(theta);

  matrix._matr[1][1] = cos_theta;
  matrix._matr[1][2] = -sin_theta;
  matrix._matr[2][1] = sin_theta;
  matrix._matr[2][2] = cos_theta;

  return matrix;
}

// Метод для создания матрицы поворота вокруг оси Y
TransformMatrix TransformMatrix::CreateRotationYMatrix(float theta) {
  TransformMatrix matrix;
  float cos_theta = cos(theta);
  float sin_theta = sin(theta);

  matrix._matr[0][0] = cos_theta;
  matrix._matr[0][2] = sin_theta;
  matrix._matr[2][0] = -sin_theta;
  matrix._matr[2][2] = cos_theta;

  return matrix;
}

// Метод для создания матрицы поворота вокруг оси Z
TransformMatrix TransformMatrix::CreateRotationZMatrix(float theta) {
  TransformMatrix matrix;
  float cos_theta = cos(theta);
  float sin_theta = sin(theta);

  matrix._matr[0][0] = cos_theta;
  matrix._matr[0][1] = -sin_theta;
  matrix._matr[1][0] = sin_theta;
  matrix._matr[1][1] = cos_theta;

  return matrix;
}

TransformMatrix& TransformMatrix::Move(float tx, float ty, float tz) {
  TransformMatrix move = CreateTranslationMatrix(tx, ty, tz);
  (*this) = (*this) * move;
  return (*this);
}
TransformMatrix& TransformMatrix::Rotate(float tx, float ty, float tz) {
  TransformMatrix rotateX = CreateRotationXMatrix(tx * M_PI / 180);
  TransformMatrix rotateY =
      TransformMatrix::CreateRotationYMatrix(ty * M_PI / 180);
  TransformMatrix rotateZ =
      TransformMatrix::CreateRotationZMatrix(tz * M_PI / 180);
  (*this) = (*this) * rotateX * rotateY * rotateZ;
  return (*this);
}

TransformMatrix& TransformMatrix::Scale(float tx, float ty, float tz) {
  TransformMatrix scale = CreateScaleMatrix(tx, ty, tz);
  (*this) = (*this) * scale;
  return (*this);
}
}  // namespace s21