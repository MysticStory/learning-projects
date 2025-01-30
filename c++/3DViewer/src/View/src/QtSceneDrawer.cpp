#include "../include/QtSceneDrawer.h"

namespace s21 {

ViewSettings* QtSceneDrawer::GetSettings() { return settings_; }

QtSceneDrawer::QtSceneDrawer(QWidget* parent)
    : QOpenGLWidget(parent), scene_(nullptr) {
  settings_ = new ViewSettings("settings.ini");
  qDebug() << "QtSceneDrawer создан. Scene:" << scene_
           << "Settings:" << settings_;
  ClearBuffers();
}

QtSceneDrawer::~QtSceneDrawer() {
  ClearBuffers();
  settings_->SaveSettings("settings.ini");
  delete settings_;
}

void QtSceneDrawer::DrawScene() {
  for (auto& [figure, buffer] : mapBuffers) {
    Draw(buffer);
  }
}

void QtSceneDrawer::UpdateViewFrame(FacadeOperationResult result,
                                    Scene& scene) {
  makeCurrent();
  if (result.IsSuccess()) {
    scene_ = &scene;
    if (!scene_) {
      qWarning() << "Ошибка: указатель на сцену не инициализирован!";
      return;
    }
    qDebug() << "Обновляем буферы фигур рендера " << this;
    for (auto& figure : scene_->GetFigures()) {
      if (mapBuffers.find(&figure) != mapBuffers.end()) {
        UpdateVertexBuffer(mapBuffers.at(&figure),
                           figure.GetTransformedVertices());

        // for (auto vertex : figure.GetVertices()) {
        //   qDebug() << "Вершинв " << vertex.X << " " << vertex.Y << " "
        //            << vertex.Z << " |";
        // }
      }
    }
    repaint();
  }
}
void QtSceneDrawer::UpdateView(FacadeOperationResult result, Scene& scene) {
  qDebug() << "Вызывается UpdateView. Scene адрес:" << &scene
           << "Результат операции:" << result.IsSuccess();
  qDebug() << "Перед вызовом makeCurrent(). Объект QtSceneDrawer: " << this;

  makeCurrent();

  if (result.IsSuccess()) {
    scene_ = &scene;
    if (!scene_) {
      qWarning() << "Ошибка: указатель на сцену не инициализирован!";
      return;
    }
    qDebug() << "Создаем фигуры рендера " << this;
    ClearBuffers();
    for (auto& figure : scene_->GetFigures()) {
      if (mapBuffers.find(&figure) == mapBuffers.end()) {
        qDebug() << "ссылка на буффер фигуры " << &figure;
        mapBuffers.emplace(&figure, CreateBuffers(figure));

      } else {
        qDebug() << "ссылка на существующий буффер АХТУНГ " << &figure;
      }
    }
    setViewType(false);
    qDebug() << "фигуры рендера созданы" << this;
    repaint();
  } else {
    ClearBuffers();
    repaint();
    QMessageBox::about(this, "Message",
                       QString::fromStdString(result.GetErrorMessage()));
  }
}

void QtSceneDrawer::OnSettingsChanged() {
  qDebug() << "смена настроек отрисовщика";
  makeCurrent();
  QColor colorbg = settings_->GetBackgroundColor();
  glClearColor(colorbg.redF(), colorbg.greenF(), colorbg.blueF(),
               colorbg.alphaF());
  setViewType(settings_->GetProjectionType() != ProjectionType::PARALLEL);
}

void QtSceneDrawer::initializeGL() {
  qDebug() << "Инициализация OpenGL начата.";

  initializeOpenGLFunctions();
  QColor colorbg = settings_->GetBackgroundColor();
  glClearColor(colorbg.redF(), colorbg.greenF(), colorbg.blueF(),
               colorbg.alphaF());

  qDebug() << "Инициализация OpenGL завершена.";
}

void QtSceneDrawer::paintGL() {
  qDebug() << "отрисовка кадров";
  glClear(GL_COLOR_BUFFER_BIT);  // Очищаем экран
  if (settings_ && scene_) {
    DrawScene();
  }
}

void QtSceneDrawer::resizeGL(int width, int height) {
  qDebug() << "resizeGL старт";
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1,
          1);  // Переустанавливаем проекцию, чтобы учитывать новый размер
  qDebug() << "resizeGL завершен";
}

void QtSceneDrawer::setViewType(bool type) {
  //  Инициализация матрицы проекций  OpenGL
  if (scene_) {
    makeCurrent();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // Сброс матрицы проекции
    // Вычисляем границы окна просмотра
    qDebug() << "пределы x" << scene_->params.min_x << " "
             << scene_->params.max_x;
    qDebug() << "пределы y" << scene_->params.min_y << " "
             << scene_->params.max_y;
    qDebug() << "пределы z" << scene_->params.min_z << " "
             << scene_->params.max_z;
    float freespace = 1.3;
    float width = scene_->params.max_x - scene_->params.min_x;
    float height = scene_->params.max_y - scene_->params.min_y;
    float depth = scene_->params.max_z - scene_->params.min_z;
    float centerX = (scene_->params.max_x + scene_->params.min_x) / 2.0;
    float centerY = (scene_->params.max_y + scene_->params.min_y) / 2.0;
    float centerZ = (scene_->params.max_z + scene_->params.min_z) / 2.0;
    float size = std::max({width, height, depth});
    float min_size = std::min({width, height, depth});
    GLdouble aspectRatio = 1.0 * this->width() / this->height();

    if (type) {              // Перспективная проекция
      GLdouble fovY = 30.0;  // Угол обзора по вертикали
      float nearVal = min_size * 0.1;
      float farVal = size * 10.0;
      GLdouble fH = tan(fovY / 360.0 * M_PI) * nearVal;
      GLdouble fW = fH * aspectRatio;

      glFrustum(-fW, fW, -fH, fH, nearVal, farVal);
      glTranslatef(-centerX, -centerY, -3 * size);
    } else {  // Ортографическая проекция
      glOrtho(centerX - size * freespace / 2.0,
              centerX + size * freespace / 2.0,
              centerY - size * freespace / 2.0 / aspectRatio,
              centerY + size * freespace / 2.0 / aspectRatio,
              centerZ - size * freespace * 2, centerZ + size * freespace * 2);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    update();
  }
}

buffersGL QtSceneDrawer::CreateBuffers(Figure& figure) {
  makeCurrent();
  GLuint vbo = 0;  // Vertex Buffer Object
  GLuint ebo = 0;  // Element Buffer Object
  std::vector<GLuint> indices;
  auto& figureVertices = figure.GetTransformedVertices();
  auto& figureEdges = figure.GetEdges();

  qDebug() << "_vbo " << this;
  // Создание VBO для вершин
  glGenBuffers(1, &vbo);
  qDebug() << "create vbo_ " << this;
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  qDebug() << "вершин  " << figureVertices.size() << this;
  glBufferData(GL_ARRAY_BUFFER, figureVertices.size() * sizeof(Vertex),
               figureVertices.data(), GL_DYNAMIC_DRAW);

  // Создание EBO для рёбер
  qDebug() << "_ebo " << this;
  glGenBuffers(1, &ebo);
  for (const auto& edge : figureEdges) {
    auto test = edge.GetIndexBegin();
    indices.push_back(test);
    auto test1 = edge.GetIndexEnd();
    indices.push_back(test1);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return buffersGL(vbo, ebo, figureVertices.size(), figure.GetEdges().size());
}

void QtSceneDrawer::UpdateVertexBuffer(buffersGL buffer,
                                       const std::vector<Vertex>& bufferGl) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, bufferGl.size() * sizeof(Vertex),
                  bufferGl.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void QtSceneDrawer::Draw(buffersGL buffer) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);

  // Установка атрибута вершин (позиция)
  glEnableClientState(GL_VERTEX_ARRAY);

  glPointSize(settings_->GetVertexSize());
  if (settings_->GetVertexType() == VertexType::CIRCLE)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);

  glVertexPointer(3, GL_FLOAT, 0, (void*)0);
  // Отрисовка вершин
  if (settings_->GetVertexType() != VertexType::NONE) {
    QColor colorV = settings_->GetVertexColor();
    glColor3f(colorV.redF(), colorV.greenF(), colorV.blueF());  // Цвет вершин
    glDrawArrays(GL_POINTS, 0, buffer.countVertics);
    CheckGLError("Vertex ");
  }
  // Рисуем рёбра
  if (buffer.countEdges > 0) {
    QColor colorE = settings_->GetEdgeColor();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.ebo);
    glColor3f(colorE.redF(), colorE.greenF(), colorE.blueF());  // Цвет рёбер
    glLineWidth(settings_->GetEdgeThickness());
    if (settings_->GetLineType() == EdgeType::DOTTED) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(2, 0x00F0);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }
    glDrawElements(GL_LINES, buffer.countEdges * 2, GL_UNSIGNED_INT,
                   nullptr);  // Отрисовка рёбер
    CheckGLError("Edge ");
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void QtSceneDrawer::ClearBuffers() {
  for (auto& [figure, buffer] : mapBuffers) {
    if (buffer.vbo) {
      glDeleteBuffers(1, &buffer.vbo);
      buffer.vbo = 0;
    }
    if (buffer.ebo) {
      glDeleteBuffers(1, &buffer.ebo);
      buffer.ebo = 0;
    }
  }
  mapBuffers.clear();
}
void QtSceneDrawer::CheckGLError(QString location) {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    qDebug() << "OpenGL Error: " << err << " at " << location;
  }
}
}  // namespace s21
