#ifndef TRANSFORMTEST_H_
#define TRANSFORMTEST_H_

#include <gtest/gtest.h>

#include "../src/Model/include/FileReader.h"

class TransformTest : public testing::Test {
 public:
  std::vector<s21::Figure> *test;

  void SetUp() {
    test = new std::vector<s21::Figure>();
    std::vector<s21::Vertex> cube_vert = {
        s21::Vertex(0.8, 0.8, 0),    s21::Vertex(0.3, 0.8, 0),
        s21::Vertex(0.3, 0.3, 0),    s21::Vertex(0.8, 0.3, 0),
        s21::Vertex(0.3, 0.8, -0.5), s21::Vertex(0.8, 0.8, -0.5),
        s21::Vertex(0.8, 0.3, -0.5), s21::Vertex(0.3, 0.3, -0.5)};
    std::vector<s21::Edge> cube_edges = {
        s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(2, 3),
        s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4), s21::Edge(4, 5),
        s21::Edge(6, 7), s21::Edge(7, 4), s21::Edge(3, 6), s21::Edge(6, 0),
        s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3), s21::Edge(1, 4),
        s21::Edge(4, 2), s21::Edge(5, 1)};

    std::vector<s21::Vertex> p_vert = {
        s21::Vertex(-0.55, 0.25, 0.55), s21::Vertex(-0.8, 0.0, 0.3),
        s21::Vertex(-0.3, 0.0, -0.3), s21::Vertex(-0.3, 0.0, 0.8),
        s21::Vertex(-0.8, 0.0, 0.8)};
    std::vector<s21::Edge> p_edges = {
        s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
        s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(3, 4), s21::Edge(4, 0),
        s21::Edge(4, 1), s21::Edge(1, 3)};

    s21::Figure cube{cube_vert, cube_edges};
    s21::Figure pyramid{p_vert, p_edges};
    test->push_back(cube);
    test->push_back(pyramid);
  }
  void TearDown() { delete test; }
};

#endif  // TRANSFORMTEST_H_