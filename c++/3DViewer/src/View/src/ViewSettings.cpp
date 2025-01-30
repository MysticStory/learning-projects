#include "../include/ViewSettings.h"

#include <QDebug>
#include <QFile>
namespace s21 {

ViewSettings::ViewSettings(const QString& settingsfileName)
    : qsettings_(settingsfileName, QSettings::NativeFormat) {
  LoadSettings(settingsfileName);
}

// Геттеры
QColor ViewSettings::GetBackgroundColor() const { return background_color_; }
QColor ViewSettings::GetEdgeColor() const { return edge_color_; }
QColor ViewSettings::GetVertexColor() const { return vertex_color_; }
int ViewSettings::GetEdgeThickness() const { return edge_thickness_; }
int ViewSettings::GetVertexSize() const { return vertex_size_; }
ProjectionType ViewSettings::GetProjectionType() const {
  return projection_type_;
}
EdgeType ViewSettings::GetLineType() const { return line_type_; }
VertexType ViewSettings::GetVertexType() const { return vertex_type_; }

// Сеттеры
void ViewSettings::SetBackgroundColor(const QColor& background_color) {
  background_color_ = background_color;
  emit SettingsChanged();
}
void ViewSettings::SetEdgeColor(const QColor& edge_color) {
  edge_color_ = edge_color;
  emit SettingsChanged();
}
void ViewSettings::SetVertexColor(const QColor& vertex_color) {
  vertex_color_ = vertex_color;
  emit SettingsChanged();
}
void ViewSettings::SetEdgeThickness(int edge_thickness) {
  if (edge_thickness > 0) edge_thickness_ = edge_thickness;
  emit SettingsChanged();
}
void ViewSettings::SetVertexSize(int vertex_size) {
  if (vertex_size > 0) vertex_size_ = vertex_size;
  emit SettingsChanged();
}
void ViewSettings::SetProjectionType(ProjectionType projection_type) {
  projection_type_ = projection_type;
  emit SettingsChanged();
}
void ViewSettings::SetLineType(EdgeType line_type) {
  line_type_ = line_type;
  emit SettingsChanged();
}
void ViewSettings::SetVertexType(VertexType vertex_type) {
  vertex_type_ = vertex_type;
  emit SettingsChanged();
}

// Управление настройками

void ViewSettings::SaveSettings(const QString& settingsFileName) {
  qDebug() << "Сохранение началась";
  QSettings settings(settingsFileName, QSettings::NativeFormat);
  settings.setValue("background_color", background_color_);
  settings.setValue("edge_color", edge_color_);
  settings.setValue("vertex_color", vertex_color_);
  settings.setValue("edge_thickness", edge_thickness_);
  settings.setValue("vertex_size", vertex_size_);
  settings.setValue("projection_type", static_cast<int>(projection_type_));
  settings.setValue("line_type", static_cast<int>(line_type_));
  settings.setValue("vertex_type", static_cast<int>(vertex_type_));
}

bool ViewSettings::LoadSettings(const QString& settingsFileName) {
  qDebug() << "загрузка началась";
  if (!QFile::exists(settingsFileName)) {
    qDebug() << "по умолчанию";
    background_color_ = QColor(Qt::white);
    edge_color_ = QColor(Qt::black);
    vertex_color_ = QColor(Qt::black);
    edge_thickness_ = 1;
    vertex_size_ = 5;
    projection_type_ = ProjectionType::PARALLEL;
    line_type_ = EdgeType::SOLID;
    vertex_type_ = VertexType::CIRCLE;
  } else {
    qDebug() << "из файла";
    QSettings settings(settingsFileName, QSettings::NativeFormat);
    //  Чтение и применение значений из файла
    background_color_ =
        settings.value("background_color", QColor(Qt::white)).value<QColor>();
    edge_color_ =
        settings.value("edge_color", QColor(Qt::black)).value<QColor>();
    vertex_color_ =
        settings.value("vertex_color", QColor(Qt::black)).value<QColor>();
    edge_thickness_ = settings.value("edge_thickness", 1).toInt();
    vertex_size_ = settings.value("vertex_size", 5).toInt();
    projection_type_ = static_cast<ProjectionType>(
        settings.value("projection_type", 0).toInt());
    line_type_ = static_cast<EdgeType>(settings.value("line_type", 0).toInt());
    vertex_type_ =
        static_cast<VertexType>(settings.value("vertex_type", 0).toInt());
  }
  return true;
}

void ViewSettings::FactoryReset() {
  background_color_ = QColor(Qt::white);
  edge_color_ = QColor(Qt::black);
  vertex_color_ = QColor(Qt::black);
  edge_thickness_ = 1;
  vertex_size_ = 5;
  projection_type_ = ProjectionType::PARALLEL;
  line_type_ = EdgeType::SOLID;
  vertex_type_ = VertexType::NONE;
}

void ViewSettings::BackgroundReset() { qsettings_.remove("background_color"); }

void ViewSettings::EdgeLineReset() {
  qsettings_.remove("edge_color");
  qsettings_.remove("edge_thickness");
  qsettings_.remove("line_type");
}

void ViewSettings::VertexPointReset() {
  qsettings_.remove("vertex_color");
  qsettings_.remove("vertex_size");
  qsettings_.remove("vertex_type");
}

}  // namespace s21