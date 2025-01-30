#include "../include/FileReader.h"

#include <iostream>

namespace s21 {
Scene FileReader::ReadScene(const std::string& path) {
  std::ifstream in(path);
  Scene scene;
  if (in.is_open()) {
    NotifyProgress(0);
    std::vector<Figure> figures;
    VertexRead(in, figures, scene.params);

    in.clear();
    in.seekg(0, std::ios_base::beg);

    if (!figures.empty()) {
      EdgesRead(in, figures);
      scene.SetFigures(figures);
    }
    in.close();
    NotifyProgress(100);
  }

  return scene;
}

std::vector<Edge> FileReader::MakeEdges(std::string& line, size_t size_v) {
  std::vector<std::string> line_pieces;
  char* piece = std::strtok(line.data(), " ");

  while (piece) {
    line_pieces.push_back(std::string(piece));
    piece = strtok(nullptr, " ");
  }
  long int index;
  std::vector<long int> numbers;
  for (auto line : line_pieces) {
    int res = sscanf(strtok(line.data(), "/"), "%ld", &index);
    if (res == 1) {
      if (index > 0) {
        index -= 1;
      } else if (index < 0) {
        index += size_v;
      }
      numbers.push_back(index);
    }
  }
  std::vector<Edge> edges;
  for (std::vector<long int>::iterator it = numbers.begin(), it2 = it + 1;
       it != numbers.end(); ++it, ++it2) {
    if (it2 == numbers.end()) it2 = numbers.begin();
    edges.push_back(Edge(*it, *it2));
  }

  return edges;
}

void FileReader::VertexRead(std::ifstream& in, std::vector<Figure>& figures,
                            MinMax& params) {
  std::string line;
  Figure figure;
  bool flag = false;

  size_t file_size = 0, bytes_read = 0;
  int last_progress = -1;

  in.seekg(0, std::ios::end);
  file_size = in.tellg();
  in.seekg(0, std::ios::beg);

  while (std::getline(in, line)) {
    if (!figure.Empty() &&
        (line.substr(0, 2) == "g " || line.substr(0, 2) == "o ")) {
      figures.push_back(figure);
      figure.Clear();

    } else if (line.substr(0, 2) == "v ") {
      figure.AddVertex(MakeVertex(line, params, flag));
    }

    bytes_read += line.size() + 1;  // Учитываем символ перевода строки
    int current_progress = static_cast<int>(bytes_read * 100 / file_size);
    if (current_progress != last_progress) {
      NotifyProgress(current_progress / 2);
      last_progress = current_progress;
    }
  }
  if (!figure.Empty()) {
    figures.push_back(figure);
    figure.Clear();
  }
}

Vertex FileReader::MakeVertex(std::string& line, MinMax& params, bool& flag) {
  std::string coord = line.substr(2, line.size());
  std::stringstream stream;
  stream << coord;
  float x = 0, y = 0, z = 0;
  stream >> x >> y >> z;
  Vertex new_vertex = Vertex(x, y, z);
  if (!flag) {
    params.min_x = new_vertex.X;
    params.max_x = new_vertex.X;
    params.min_y = new_vertex.Y;
    params.max_y = new_vertex.Y;
    params.min_z = new_vertex.Z;
    params.max_z = new_vertex.Z;
    flag = true;
  }
  params.min_x = std::min(params.min_x, new_vertex.X);
  params.max_x = std::max(params.max_x, new_vertex.X);
  params.min_y = std::min(params.min_y, new_vertex.Y);
  params.max_y = std::max(params.max_y, new_vertex.Y);
  params.min_z = std::min(params.min_z, new_vertex.Z);
  params.max_z = std::max(params.max_z, new_vertex.Z);

  return new_vertex;
}

void FileReader::EdgesRead(std::ifstream& in, std::vector<Figure>& figures) {
  std::string line;
  std::vector<Figure>::iterator it = figures.begin();
  size_t size_v = it->GetVertices().size();
  long int offset = 0;

  size_t file_size = 0, bytes_read = 0;
  int last_progress = -1;

  in.seekg(0, std::ios::end);
  file_size = in.tellg();
  in.seekg(0, std::ios::beg);

  while (std::getline(in, line) && it != figures.end()) {
    if (line.substr(0, 2) == "f ") {
      std::string coord = line.substr(2, line.size());
      std::vector<Edge> edges_from_file = MakeEdges(coord, size_v);
      for (auto edge : edges_from_file) {
        it->AddEdge(edge);
      }
    } else if (line.substr(0, 2) == "g " || line.substr(0, 2) == "o ") {
      if (it == figures.begin() && it->GetEdges().empty()) continue;
      if (OutOfRange(size_v, it->GetEdges())) {
        offset += (it - 1)->GetVertices().size();
        it->EdgesOffset(offset * (-1L));
      }

      if (++it == figures.end()) --it;
      size_v = it->GetVertices().size();
    }
    bytes_read += line.size() + 1;  // Учитываем символ перевода строки
    int current_progress = static_cast<int>(bytes_read * 100 / file_size);
    if (current_progress != last_progress) {
      NotifyProgress(current_progress / 2 + 50);
      last_progress = current_progress;
    }
  }
  if (OutOfRange(size_v, it->GetEdges())) {
    offset += (it - 1)->GetVertices().size();
    it->EdgesOffset(offset * (-1L));
  }
}

bool FileReader::OutOfRange(size_t size_v, const std::vector<Edge>& edges) {
  for (Edge edge : edges) {
    if (std::fabs(edge.GetIndexBegin()) >= size_v ||
        std::fabs(edge.GetIndexBegin()) >= size_v) {
      { return true; }
    }
  }
  return false;
}

}  // namespace s21
