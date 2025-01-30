#ifndef FILEREADER_H
#define FILEREADER_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include "../../Geometry/include/Scene.h"
#include "BaseFileReader.h"
namespace s21 {

class FileReader : public BaseFileReader {
 public:
  Scene ReadScene(const std::string& path) override;
  bool OutOfRange(size_t size_v, const std::vector<Edge>& edges);
  Vertex MakeVertex(std::string& line, MinMax& params, bool& flag);
  std::vector<Edge> MakeEdges(std::string& line, size_t size_v);
  void VertexRead(std::ifstream& in, std::vector<Figure>& figures,
                  MinMax& params);
  void EdgesRead(std::ifstream& in, std::vector<Figure>& figures);
};

}  // namespace s21
#endif  // FILEREADER_H
