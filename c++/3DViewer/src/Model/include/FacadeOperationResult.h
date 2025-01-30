#ifndef FACADE_OPERATION_RESULT_H
#define FACADE_OPERATION_RESULT_H

#include <string>

namespace s21 {
class FacadeOperationResult {
 private:
  bool _success = false;      // Статус успеха операции
  std::string _errorMessage;  // Сообщение об ошибке

 public:
  // Конструкторы
  FacadeOperationResult(bool success, const std::string& errorMessage = "");

  // Методы доступа
  std::string GetErrorMessage() const;
  bool IsSuccess() const;

  // Методы установки
  void SetErrorMessage(const std::string& errorMessage);
  void SetSuccess(bool success);

  // Деструктор
  ~FacadeOperationResult();
};
}  // namespace s21

#endif  // FACADE_OPERATION_RESULT_H