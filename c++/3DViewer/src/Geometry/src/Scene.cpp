#include "../include/Scene.h"

namespace s21 {

Scene::Scene(const std::vector<Figure>& figures) : _figures(figures) {}
Scene::Scene() {}
std::vector<Figure>& Scene::GetFigures() { return _figures; }

void Scene::TransformFigures(const TransformMatrix& matrix) {
  for (auto& figure : _figures) {
    figure.transformationMatrix = matrix;
  }
}

void Scene::AddFigure(const Figure& figure) { _figures.push_back(figure); }
bool Scene::Empty() { return _figures.size() == 0; }
void Scene::SetFigures(const std::vector<Figure>& figures) {
  _figures = figures;
}

int Scene::GetVertexCount() const {
  int count = 0;
  for (const Figure& figure : _figures) {
    count +=
        figure.GetVertexCount();  // Получаем количество вершин у каждой фигуры
  }
  return count;
}

int Scene::GetEdgeCount() const {
  int count = 0;
  for (const Figure& figure : _figures) {
    count +=
        figure.GetEdgeCount();  // Получаем количество рёбер у каждой фигуры
  }
  return count;
}

}  // namespace s21