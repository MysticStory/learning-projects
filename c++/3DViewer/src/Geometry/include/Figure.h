#ifndef FIGURE_H_
#define FIGURE_H_

#include <vector>

#include "Edge.h"
#include "TransformMatrix.h"
#include "Vertex.h"

namespace s21 {
class Figure {
 public:
  TransformMatrix transformationMatrix = TransformMatrix();
  float state[3][3] = {{0, 0, 0}, {0, 0, 0}, {1, 1, 1}};
  Figure();
  Figure(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges);
  std::vector<Vertex>& GetVertices();
  std::vector<Edge>& GetEdges();

  void AddVertex(const Vertex vertices);
  void AddEdge(const Edge edges);
  const std::vector<Vertex> GetTransformedVertices() const;
  void Clear();
  bool Empty() const;

  void EdgesOffset(long int offset);
  int GetVertexCount() const;
  int GetEdgeCount() const;

 private:
  std::vector<Vertex> _vertices;
  std::vector<Edge> _edges;
};
}  // namespace s21
#endif  // FIGURE_H_