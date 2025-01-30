#include "../include/StyleHelper.h"

QString StyleHelper::getMainWidgetStyle() {
  return "QWidget{"
         "    background-color: rgb(98, 98, 98);"
         "}";
}

QString StyleHelper::getActionButtonsStyle() {
  return "QPushButton{"
         "    color:#fff;"
         "    background:none;"
         "    border:none;"
         "    border-radius:6px;"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.529101 rgba(0, 32, 27, 255), stop:1 rgba(255, 255, 255, "
         "255));"
         "}"
         "QPushButton::hover{"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.768421 rgba(102, 44, 44, 255), stop:1 rgba(255, 255, "
         "255, 255));"
         "}"
         "QPushButton::pressed{"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.216931 rgba(102, 44, 44, 255), stop:1 rgba(255, 255, "
         "255, 255));"
         "}";
}

QString StyleHelper::getResetButtonsStyle() {
  return "QPushButton{"
         "    color:#fff;"
         "    background:none;"
         "    border:none;"
         "    border-radius:6px;"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.47619 rgba(141, 0, 0, 255), stop:1 rgba(255, 255, 255, "
         "255));"
         "}"
         "QPushButton::hover{"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.740741 rgba(185, 0, 0, 255), stop:1 rgba(255, 255, 255, "
         "255));"
         "}"
         "QPushButton::pressed{"
         "    background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, "
         "y2:0, stop:0.132275 rgba(185, 0, 0, 255), stop:1 rgba(255, 255, 255, "
         "255));"
         "}";
}

QString StyleHelper::getRadioButtonsStyle() {
  return "QRadioButton{"
         "    color:#000;"
         "    background:none;"
         "    border:none;"
         "    border-radius:6px;"
         "    background-color: rgb(110, 110, 110);"
         "    border-color: rgb(0, 0, 0);"
         "}"
         "QRadioButton::checked{"
         "    color:#fff;"
         "    background-color: rgb(95, 95, 95);"
         "}";
}

QString StyleHelper::getTextBrowserStyle() {
  return "QTextBrowser{"
         "    color:#fff;"
         "    background:none;"
         "    border-radius:6px;"
         "    background-color: rgb(115, 115, 115);"
         "}";
}

QString StyleHelper::getLineEditStyle() {
  return "QLineEdit{"
         "    color:#fff;"
         "    background:none;"
         "    border-radius:6px;"
         "    background-color: rgb(115, 115, 115);"
         "}";
}