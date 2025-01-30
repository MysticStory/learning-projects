#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>

class StyleHelper {
 public:
  static QString getMainWidgetStyle();
  static QString getActionButtonsStyle();
  static QString getResetButtonsStyle();
  static QString getRadioButtonsStyle();
  static QString getTextBrowserStyle();
  static QString getLineEditStyle();
};

#endif  // STYLEHELPER_H