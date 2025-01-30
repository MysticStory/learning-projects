#include "../include/FacadeOperationResult.h"

namespace s21 {

// Конструктор с параметром для указания успеха и сообщения об ошибке
FacadeOperationResult::FacadeOperationResult(bool success,
                                             const std::string& errorMessage)
    : _success(success), _errorMessage(errorMessage) {}

// Метод получения сообщения об ошибке
std::string FacadeOperationResult::GetErrorMessage() const {
  return _errorMessage;
}

// Метод проверки успешности операции
bool FacadeOperationResult::IsSuccess() const { return _success; }

// Метод установки сообщения об ошибке
void FacadeOperationResult::SetErrorMessage(const std::string& errorMessage) {
  _errorMessage = errorMessage;
}

// Метод установки статуса успеха
void FacadeOperationResult::SetSuccess(bool success) { _success = success; }

// Деструктор
FacadeOperationResult::~FacadeOperationResult() {}

}  // namespace s21