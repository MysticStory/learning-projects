#include "../include/Figure.h"

namespace s21 {

Figure::Figure(const std::vector<Vertex>& vertices,
               const std::vector<Edge>& edges)
    : _vertices(vertices), _edges(edges) {}
Figure::Figure() {}

std::vector<Vertex>& Figure::GetVertices() { return _vertices; }
std::vector<Edge>& Figure::GetEdges() { return _edges; }

const std::vector<Vertex> Figure::GetTransformedVertices() const {
  std::vector<Vertex> transformedVertices;
  transformedVertices.reserve(
      _vertices.size());  // Резервируем место для вершин
  for (const auto& vertex : _vertices) {
    transformedVertices.push_back(vertex.Transform(transformationMatrix));
  }
  return transformedVertices;
}

void Figure::AddVertex(const Vertex vertex) { _vertices.push_back(vertex); }

void Figure::AddEdge(const Edge edge) { _edges.push_back(edge); }

void Figure::Clear() {
  _vertices.clear();
  _edges.clear();
}

bool Figure::Empty() const { return _vertices.empty() && _edges.empty(); }

void Figure::EdgesOffset(long int offset) {
  for (Edge& edge : _edges) {
    edge += offset;
  }
}

int Figure::GetVertexCount() const { return _vertices.size(); }
int Figure::GetEdgeCount() const { return _edges.size(); }

}  // namespace s21