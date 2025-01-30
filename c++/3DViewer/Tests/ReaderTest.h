#ifndef READERTEST_H_
#define READERTEST_H_

#include <gtest/gtest.h>

#include "../src/Model/include/FileReader.h"

class ReaderTest : public testing::Test {
 public:
  std::vector<s21::Figure>* check;
  void SetUp() {
    check = new std::vector<s21::Figure>();
    std::vector<s21::Vertex> cube_vert = {
        s21::Vertex(1.0, 1.0, 1.0),   s21::Vertex(-1.0, 1.0, 1.0),
        s21::Vertex(-1.0, -1.0, 1.0), s21::Vertex(1.0, -1.0, 1.0),
        s21::Vertex(-1.0, 1.0, -1.0), s21::Vertex(1.0, 1.0, -1.0),
        s21::Vertex(1.0, -1.0, -1.0), s21::Vertex(-1.0, -1.0, -1.0)};
    std::vector<s21::Edge> cube_edges = {
        s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 1), s21::Edge(0, 2),
        s21::Edge(2, 3), s21::Edge(3, 0), s21::Edge(5, 6), s21::Edge(6, 4),
        s21::Edge(4, 5), s21::Edge(4, 6), s21::Edge(6, 7), s21::Edge(7, 4),
        s21::Edge(3, 6), s21::Edge(6, 0), s21::Edge(0, 3), s21::Edge(0, 6),
        s21::Edge(6, 5), s21::Edge(5, 0), s21::Edge(2, 7), s21::Edge(7, 3),
        s21::Edge(3, 2), s21::Edge(3, 7), s21::Edge(7, 6), s21::Edge(6, 3),
        s21::Edge(1, 4), s21::Edge(4, 2), s21::Edge(2, 1), s21::Edge(2, 4),
        s21::Edge(4, 7), s21::Edge(7, 2), s21::Edge(0, 5), s21::Edge(5, 1),
        s21::Edge(1, 0), s21::Edge(1, 5), s21::Edge(5, 4), s21::Edge(4, 1)};

    std::vector<s21::Vertex> p_vert = {
        s21::Vertex(0.0, 1.0, 0.0), s21::Vertex(-1.0, 0.0, -1.0),
        s21::Vertex(1.0, 0.0, -1.0), s21::Vertex(1.0, 0.0, 1.0),
        s21::Vertex(-1.0, 0.0, 1.0)};
    std::vector<s21::Edge> p_edges = {
        s21::Edge(0, 1), s21::Edge(1, 2), s21::Edge(2, 0), s21::Edge(0, 0),
        s21::Edge(0, 0), s21::Edge(0, 2), s21::Edge(2, 3), s21::Edge(3, 0),
        s21::Edge(0, 3), s21::Edge(3, 4), s21::Edge(4, 0), s21::Edge(0, 4),
        s21::Edge(4, 1), s21::Edge(1, 0), s21::Edge(2, 1), s21::Edge(1, 3),
        s21::Edge(3, 2), s21::Edge(1, 4), s21::Edge(4, 3), s21::Edge(3, 1)};

    s21::Figure cube{cube_vert, cube_edges};
    s21::Figure pyramid{p_vert, p_edges};
    check->push_back(cube);
    check->push_back(pyramid);
  }
  void TearDown() { delete check; }
};

#endif  // READERTEST_H_