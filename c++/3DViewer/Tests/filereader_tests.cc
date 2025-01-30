#include "ReaderTest.h"

TEST(Reader, test_1) {
  std::string path = "ABCD";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_TRUE(my_scene.Empty());
}

TEST(Reader, test_2) {
  std::string path;
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_TRUE(my_scene.Empty());
}

TEST(Reader, test_3) {
  std::string path = "./Test_files/empty.obj";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);
  EXPECT_TRUE(my_scene.Empty());
}

TEST_F(ReaderTest, reader_1) {
  std::string path = "./Tests/Test_files/cube.obj";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_EQ(my_scene.GetFigures().size(), 1);
  EXPECT_TRUE(my_scene.GetFigures()[0].GetVertices() ==
              check->at(0).GetVertices());
  EXPECT_TRUE(my_scene.GetFigures()[0].GetEdges() == check->at(0).GetEdges());
}

TEST_F(ReaderTest, reader_2) {
  std::string path = "./Tests/Test_files/pyramid.obj";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_EQ(my_scene.GetFigures().size(), 1);
  EXPECT_TRUE(my_scene.GetFigures()[0].GetVertices() ==
              check->at(1).GetVertices());
  EXPECT_TRUE(my_scene.GetFigures()[0].GetEdges() == check->at(1).GetEdges());
}

TEST_F(ReaderTest, reader_3) {
  std::string path = "./Tests/Test_files/cube_no_facets.obj";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_EQ(my_scene.GetFigures().size(), 1);
  EXPECT_TRUE(my_scene.GetFigures()[0].GetVertices() ==
              check->at(0).GetVertices());
  EXPECT_TRUE(my_scene.GetFigures()[0].GetEdges().empty());
}

TEST_F(ReaderTest, reader_4) {
  std::string path = "./Tests/Test_files/pyramid_neg.obj";
  s21::FileReader reader;
  s21::Scene my_scene = reader.ReadScene(path);

  EXPECT_EQ(my_scene.GetFigures().size(), 1);
  EXPECT_TRUE(my_scene.GetFigures()[0].GetVertices() ==
              check->back().GetVertices());
  EXPECT_TRUE(my_scene.GetFigures()[0].GetEdges() == check->back().GetEdges());
}
