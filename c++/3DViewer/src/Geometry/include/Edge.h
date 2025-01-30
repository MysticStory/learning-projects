#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"
namespace s21 {
class Edge {
 private:
  long int _index_begin;
  long int _index_end;

 public:
  Edge(){};
  Edge(long int index_begin, long int index_end);
  long int GetIndexBegin() const;
  long int GetIndexEnd() const;
  void SetIndexBegin(long int index);
  void SetIndexEnd(long int index);
  Edge& operator+=(long int index);

  bool operator==(const Edge& other) const;
};
}  // namespace s21
#endif  // EDGE_H_