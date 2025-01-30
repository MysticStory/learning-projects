#include "TransformTest.h"

TEST_F(TransformTest, move_1) {
  s21::Scene scene(*test);
  std::vector<s21::Figure> check;
  std::vector<s21::Vertex> c_vert = {
      s21::Vertex(1.0, 0.9, -0.1), s21::Vertex(0.5, 0.9, -0.1),
      s21::Vertex(0.5, 0.4, -0.1), s21::Vertex(1, 0.4, -0.1),
      s21::Vertex(0.5, 0.9, -0.6), s21::Vertex(1, 0.9, -0.6),
      s21::Vertex(1.0, 0.4, -0.6), s21::Vertex(0.5, 0.4, -0.6)};
  std::vector<s21::Edge> c_edges = {
      s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
      s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
      s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
      s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
      s21::Edge(4, 2), s21::Edge(5, 1)};

  std::vector<s21::Vertex> pyr_vert = {
      s21::Vertex(-0.35, 0.35, 0.45), s21::Vertex(-0.6, 0.1, 0.2),
      s21::Vertex(-0.1, 0.1, -0.4), s21::Vertex(-0.1, 0.1, 0.7),
      s21::Vertex(-0.6, 0.1, 0.7)};
  std::vector<s21::Edge> pyr_edges = {
      s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
      s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
      s21::Edge(4, 1), s21::Edge(1, 3)};

  s21::Figure c{c_vert, c_edges};
  s21::Figure p{pyr_vert, pyr_edges};
  check.push_back(c);
  check.push_back(p);

  s21::TransformMatrix transform;
  transform.Move(0.2, 0.1, -0.1);

  scene.TransformFigures(transform);

  EXPECT_TRUE(scene.GetFigures().front().GetTransformedVertices() ==
              check.front().GetVertices());
  EXPECT_TRUE(scene.GetFigures().back().GetTransformedVertices() ==
              check.back().GetVertices());
}

TEST_F(TransformTest, scale_1) {
  s21::Scene scene(*test);
  std::vector<s21::Figure> check;
  std::vector<s21::Vertex> c_vert = {
      s21::Vertex(1.6, 1.6, 0),  s21::Vertex(0.6, 1.6, 0),
      s21::Vertex(0.6, 0.6, 0),  s21::Vertex(1.6, 0.6, 0),
      s21::Vertex(0.6, 1.6, -1), s21::Vertex(1.6, 1.6, -1),
      s21::Vertex(1.6, 0.6, -1), s21::Vertex(0.6, 0.6, -1)};
  std::vector<s21::Edge> c_edges = {
      s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
      s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
      s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
      s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
      s21::Edge(4, 2), s21::Edge(5, 1)};

  std::vector<s21::Vertex> p_vert = {
      s21::Vertex(-1.1, 0.5, 1.1), s21::Vertex(-1.6, 0.0, 0.6),
      s21::Vertex(-0.6, 0.0, -0.6), s21::Vertex(-0.6, 0.0, 1.6),
      s21::Vertex(-1.6, 0.0, 1.6)};
  std::vector<s21::Edge> p_edges = {
      s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
      s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
      s21::Edge(4, 1), s21::Edge(1, 3)};

  s21::Figure c{c_vert, c_edges};
  s21::Figure p{p_vert, p_edges};
  check.push_back(c);
  check.push_back(p);

  s21::TransformMatrix transform;
  transform.Scale(2, 2, 2);

  scene.TransformFigures(transform);

  EXPECT_TRUE(scene.GetFigures().front().GetTransformedVertices() ==
              check.front().GetVertices());
  EXPECT_TRUE(scene.GetFigures().back().GetTransformedVertices() ==
              check.back().GetVertices());
}

TEST_F(TransformTest, rotateX) {
  s21::Scene scene(*test);
  std::vector<s21::Figure> check;
  std::vector<s21::Vertex> c_vert = {
      s21::Vertex(0.8, 0.0, 0.8), s21::Vertex(0.3, 0.0, 0.8),
      s21::Vertex(0.3, 0.0, 0.3), s21::Vertex(0.8, 0.0, 0.3),
      s21::Vertex(0.3, 0.5, 0.8), s21::Vertex(0.8, 0.5, 0.8),
      s21::Vertex(0.8, 0.5, 0.3), s21::Vertex(0.3, 0.5, 0.3)};
  std::vector<s21::Edge> c_edges = {
      s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
      s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
      s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
      s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
      s21::Edge(4, 2), s21::Edge(5, 1)};

  std::vector<s21::Vertex> p_vert = {
      s21::Vertex(-0.55, -0.55, 0.25), s21::Vertex(-0.8, -0.3, 0.0),
      s21::Vertex(-0.3, 0.3, 0.0), s21::Vertex(-0.3, -0.8, 0.0),
      s21::Vertex(-0.8, -0.8, 0.0)};
  std::vector<s21::Edge> p_edges = {
      s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
      s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
      s21::Edge(4, 1), s21::Edge(1, 3)};

  s21::Figure c{c_vert, c_edges};
  s21::Figure p{p_vert, p_edges};
  check.push_back(c);
  check.push_back(p);

  s21::TransformMatrix transform;
  transform.Rotate(90, 0, 0);

  scene.TransformFigures(transform);

  EXPECT_TRUE(scene.GetFigures().front().GetTransformedVertices() ==
              check.front().GetVertices());
  EXPECT_TRUE(scene.GetFigures().back().GetTransformedVertices() ==
              check.back().GetVertices());
}

TEST_F(TransformTest, rotateY_1) {
  s21::Scene scene(*test);
  std::vector<s21::Figure> check;
  std::vector<s21::Vertex> c_vert = {
      s21::Vertex(0.0, 0.8, -0.8),  s21::Vertex(0.0, 0.8, -0.3),
      s21::Vertex(0.0, 0.3, -0.3),  s21::Vertex(0.0, 0.3, -0.8),
      s21::Vertex(-0.5, 0.8, -0.3), s21::Vertex(-0.5, 0.8, -0.8),
      s21::Vertex(-0.5, 0.3, -0.8), s21::Vertex(-0.5, 0.3, -0.3)};
  std::vector<s21::Edge> c_edges = {
      s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
      s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
      s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
      s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
      s21::Edge(4, 2), s21::Edge(5, 1)};

  std::vector<s21::Vertex> p_vert = {
      s21::Vertex(0.55, 0.25, 0.55), s21::Vertex(0.3, 0.0, 0.8),
      s21::Vertex(-0.3, 0.0, 0.3), s21::Vertex(0.8, 0.0, 0.3),
      s21::Vertex(0.8, 0.0, 0.8)};
  std::vector<s21::Edge> p_edges = {
      s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
      s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
      s21::Edge(4, 1), s21::Edge(1, 3)};

  s21::Figure c{c_vert, c_edges};
  s21::Figure p{p_vert, p_edges};
  check.push_back(c);
  check.push_back(p);

  s21::TransformMatrix rotateY;
  rotateY.Rotate(0, 90, 0);

  scene.TransformFigures(rotateY);

  EXPECT_TRUE(scene.GetFigures().front().GetTransformedVertices() ==
              check.front().GetVertices());
  EXPECT_TRUE(scene.GetFigures().back().GetTransformedVertices() ==
              check.back().GetVertices());
}

TEST_F(TransformTest, rotateZ_1) {
  s21::Scene scene(*test);
  std::vector<s21::Figure> check;
  std::vector<s21::Vertex> c_vert = {
      s21::Vertex(-0.8, 0.8, 0),    s21::Vertex(-0.8, 0.3, 0),
      s21::Vertex(-0.3, 0.3, 0),    s21::Vertex(-0.3, 0.8, 0),
      s21::Vertex(-0.8, 0.3, -0.5), s21::Vertex(-0.8, 0.8, -0.5),
      s21::Vertex(-0.3, 0.8, -0.5), s21::Vertex(-0.3, 0.3, -0.5)};
  std::vector<s21::Edge> c_edges = {
      s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
      s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
      s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
      s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
      s21::Edge(4, 2), s21::Edge(5, 1)};

  std::vector<s21::Vertex> p_vert = {
      s21::Vertex(-0.25, -0.55, 0.55), s21::Vertex(0.0, -0.8, 0.3),
      s21::Vertex(0.0, -0.3, -0.3), s21::Vertex(0.0, -0.3, 0.8),
      s21::Vertex(0.0, -0.8, 0.8)};
  std::vector<s21::Edge> p_edges = {
      s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
      s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
      s21::Edge(4, 1), s21::Edge(1, 3)};

  s21::Figure c{c_vert, c_edges};
  s21::Figure p{p_vert, p_edges};
  check.push_back(c);
  check.push_back(p);

  s21::TransformMatrix rotateZ;
  rotateZ.Rotate(0, 0, 90);

  scene.TransformFigures(rotateZ);

  EXPECT_TRUE(scene.GetFigures().front().GetTransformedVertices() ==
              check.front().GetVertices());
  EXPECT_TRUE(scene.GetFigures().back().GetTransformedVertices() ==
              check.back().GetVertices());
}