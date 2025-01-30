#include "../include/Edge.h"
namespace s21 {

Edge::Edge(long int begin, long int end)
    : _index_begin(begin), _index_end(end) {}

long int Edge::GetIndexBegin() const { return _index_begin; }
long int Edge::GetIndexEnd() const { return _index_end; }

void Edge::SetIndexBegin(long int index) { _index_begin = index; }
void Edge::SetIndexEnd(long int index) { _index_end = index; }

Edge& Edge::operator+=(long int index) {
  _index_begin += index;
  _index_end += index;

  return (*this);
}

bool Edge::operator==(const Edge& other) const {
  return (_index_begin == other._index_begin &&
          _index_end == other._index_end) ||
         (_index_begin == other._index_end && _index_end == other._index_begin);
}

}  // namespace s21