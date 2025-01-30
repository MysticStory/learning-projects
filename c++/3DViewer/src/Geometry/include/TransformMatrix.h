#ifndef TRANSFORMMATRIX_H_
#define TRANSFORMMATRIX_H_

namespace s21 {
class Vertex;
class TransformMatrix {
 private:
  float _matr[4][4];  // 4x4 матрица для 3D трансформаций

 public:
  TransformMatrix();  // Конструктор по умолчанию

  // Операция умножения матриц
  TransformMatrix operator*(const TransformMatrix& other);

  // Применение матрицы к точке
  Vertex TransformVertex(const Vertex& point) const;

  // Методы для создания различных матриц трансформаций
  static TransformMatrix CreateTranslationMatrix(float tx, float ty,
                                                 float tz);  // Смещение
  TransformMatrix& Move(float tx, float ty, float tz);
  TransformMatrix& Rotate(float tx, float ty, float tz);
  TransformMatrix& Scale(float tx, float ty, float tz);
  static TransformMatrix CreateScaleMatrix(float sx, float sy,
                                           float sz);  // Масштабирование
  static TransformMatrix CreateRotationXMatrix(
      float theta);  // Поворот вокруг X
  static TransformMatrix CreateRotationYMatrix(
      float theta);  // Поворот вокруг Y
  static TransformMatrix CreateRotationZMatrix(
      float theta);  // Поворот вокруг Z
  static TransformMatrix CreatePerspectiveProjectionMatrix(
      float fov, float aspect, float near,
      float far);  // Перспективная проекция
  static TransformMatrix CreateParallelProjectionMatrix(float left, float right,
                                                        float bottom, float top,
                                                        float near, float far);
};
}  // namespace s21

#endif  // TRANSFORMMATRIX_H_