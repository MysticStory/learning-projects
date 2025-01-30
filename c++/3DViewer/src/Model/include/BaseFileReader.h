#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H
#include <functional>
#include <string>

#include "../../Geometry/include/Scene.h"
namespace s21 {

class BaseFileReader {
 public:
  using ProgressCallback = std::function<void(int)>;
  virtual Scene ReadScene(const std::string& path) = 0;

  // установить функцию вызовы
  void SetProgressCallback(ProgressCallback callback) {
    progress_callback_ = std::move(callback);
  }

 private:
  ProgressCallback progress_callback_;
  // для оповещения
 protected:
  void NotifyProgress(int progress) {
    if (progress_callback_) {
      progress_callback_(progress);
    }
  }
};
}  // namespace s21
#endif  // BASEFILEREADER_H