#ifndef VIEWSETTINGS_H
#define VIEWSETTINGS_H

#include <QColor>
#include <QObject>
#include <QSettings>
#include <QString>

namespace s21 {

enum class ProjectionType { PARALLEL, CENTRAL };
enum class EdgeType { SOLID, DOTTED };
enum class VertexType { NONE, CIRCLE, SQUARE };

class ViewSettings : public QObject {
  Q_OBJECT

 public:
  explicit ViewSettings(const QString& settingsfileName);

  // Геттеры
  QColor GetBackgroundColor() const;
  QColor GetEdgeColor() const;
  QColor GetVertexColor() const;
  int GetEdgeThickness() const;
  int GetVertexSize() const;
  ProjectionType GetProjectionType() const;
  EdgeType GetLineType() const;
  VertexType GetVertexType() const;

  // Сеттеры
  void SetBackgroundColor(const QColor& background_color);
  void SetEdgeColor(const QColor& edge_color);
  void SetVertexColor(const QColor& vertex_color);
  void SetEdgeThickness(int edge_thickness);
  void SetVertexSize(int vertex_size);
  void SetProjectionType(ProjectionType projection_type);
  void SetLineType(EdgeType line_type);
  void SetVertexType(VertexType vertex_type);

  // Управление настройками
  void SaveSettings(const QString& settingsFileName);
  bool LoadSettings(const QString& settingsFileName);
  void FactoryReset();
  void BackgroundReset();
  void EdgeLineReset();
  void VertexPointReset();

 signals:
  void SettingsChanged();

 private:
  QColor background_color_;
  QColor edge_color_;
  QColor vertex_color_;
  int edge_thickness_ = 1;
  int vertex_size_ = 5;
  ProjectionType projection_type_ = ProjectionType::PARALLEL;
  EdgeType line_type_ = EdgeType::SOLID;
  VertexType vertex_type_ = VertexType::CIRCLE;

  QSettings qsettings_;
};

}  // namespace s21

#endif  // VIEWSETTINGS_H