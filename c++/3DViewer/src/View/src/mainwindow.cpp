
#include "../include/mainwindow.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow()) {
  ui->setupUi(this);
  setInterfaceStyle();
  ui->groupBox_progressBar->hide();
  ui->groupBox_openFile->show();
  gifRecorder = new s21::GifRecorder(this);
  sceneDrawer_ = ui->openGLContainer;
  viewSettings_ = sceneDrawer_->GetSettings();

  zoomInTimer_ = new QTimer(this);
  zoomOutTimer_ = new QTimer(this);
  zoomInTimer_->setInterval(100);
  zoomOutTimer_->setInterval(100);

  setupConnections();
  ApplySettings();
}

MainWindow::~MainWindow() {
  delete gifRecorder;
  delete ui;
}

void MainWindow::UpdateModelInfo(int vertexCount, int edgeCount) {
  ui->VerticesNumber_textBrowser->setText(QString::number(vertexCount));
  ui->EdgesNumber_textBrowser->setText(QString::number(edgeCount));
}

void MainWindow::setZoomValue(float value) {
  ui->Zoom_lineEdit->setText(QString::number(value));
}

void MainWindow::setRotationValues(float x, float y, float z) {
  ui->XRotate_lineEdit->setText(QString::number(x));
  ui->YRotate_lineEdit->setText(QString::number(y));
  ui->ZRotate_lineEdit->setText(QString::number(z));
}

void MainWindow::setPositionValues(float x, float y, float z) {
  ui->XMoving_lineEdit->setText(QString::number(x));
  ui->YMoving_lineEdit->setText(QString::number(y));
  ui->ZMoving_lineEdit->setText(QString::number(z));
}

void MainWindow::closeEvent(QCloseEvent* event) { event->accept(); }

void MainWindow::resizeEvent(QResizeEvent* event) {
  QMainWindow::resizeEvent(event);  // Вызов базовой реализации resizeEvent

  // Рассчет пропорций для сохранения соотношения сторон
  int newWidth = event->size().width();
  int newHeight = event->size().height();

  int widgetWidth =
      static_cast<int>(newHeight * 4.0 / 3.0);  // Пропорция 4:3 для ширины
  int widgetHeight =
      static_cast<int>(newHeight);  // Пропорция сохранения высоты

  if (widgetWidth > newWidth) {
    widgetWidth = newWidth;
    widgetHeight =
        static_cast<int>(newWidth * 3.0 / 4.0);  // Пропорция 4:3 для высоты
  }

  if (widgetHeight > newHeight) {
    widgetHeight = newHeight;
    widgetWidth =
        static_cast<int>(newHeight * 4.0 / 3.0);  // Пропорция 4:3 для ширины
  }

  qDebug() << "New size: " << newWidth << "x" << newHeight;
  qDebug() << "OpenGLWidget size: " << widgetWidth << "x" << widgetHeight;

  ui->openGLContainer->setMaximumWidth(widgetWidth);
  ui->openGLContainer->setMaximumHeight(widgetHeight);

  // Установка пропорционального размера виджета OpenGLWidget
  ui->openGLContainer->setGeometry(0, 0, widgetWidth, widgetHeight);
}

void MainWindow::onOpenFileButtonClicked() {
  QDir startingDir = GetAplicationPath();
  QString fileName = QFileDialog::getOpenFileName(
      this, "Open File", startingDir.path(), "OBJ Files (*.obj *.OBJ)");
  if (fileName.isEmpty()) {
    QMessageBox::critical(this, "Error", "The obj file could not be opened");
    return;
  }

  emit fileOpenRequested(fileName.toStdString(), [this](int progress) {
    QMetaObject::invokeMethod(
        this, [this, progress]() { TestCallback(progress); },
        Qt::QueuedConnection);  // Передаем функцию через лямбду(точнее вызов
                                // функции)
  });

  on_Centering_pushButton_clicked();
  QByteArray arr = fileName.toUtf8();
  QFileInfo fileInfo(fileName);
  QString modelName = fileInfo.baseName();
  ui->ModelName_textBrowser->setText(modelName);
  ui->PathFile_textBrowser->setText(fileName);
}

void MainWindow::TestCallback(int val) {
  QMetaObject::invokeMethod(
      this,
      [this, val]() {
        qDebug() << "progress val " << val;
        ui->groupBox_openFile->hide();
        ui->groupBox_progressBar->show();
        ui->OpenFile_pushButton->setEnabled(false);
        ui->progressBar->setValue(val);
        if (val == 100) {
          ui->OpenFile_pushButton->setEnabled(true);
          ui->groupBox_progressBar->hide();
          ui->groupBox_openFile->show();
          qDebug() << "кнопка разблокирована" << val;
        }
      },
      Qt::QueuedConnection);
}
void MainWindow::onBackgroundColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    QString colorName = color.name(QColor::HexRgb);
    ui->BackgroundColor_lineEdit->setText(colorName);
  }
}

void MainWindow::onEdgeLineColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    QString colorName = color.name(QColor::HexRgb);
    ui->EdgeLineColor_lineEdit->setText(colorName);
  }
}

void MainWindow::onVertexPointColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    QString colorName = color.name(QColor::HexRgb);
    ui->VertexPointColor_lineEdit->setText(colorName);
  }
}

void MainWindow::on_BackgroundColor_lineEdit_textChanged(const QString& arg1) {
  viewSettings_->SetBackgroundColor(QColor(arg1));
  ui->BackgroundColor_lineEdit->setStyleSheet("background-color: " + arg1 +
                                              ";");
  applyContrastTextToLineEdit(ui->BackgroundColor_lineEdit, arg1);
}

void MainWindow::on_EdgeLineColor_lineEdit_textChanged(const QString& arg1) {
  viewSettings_->SetEdgeColor(QColor(arg1));
  ui->EdgeLineColor_lineEdit->setStyleSheet("background-color: " + arg1 + ";");
  applyContrastTextToLineEdit(ui->EdgeLineColor_lineEdit, arg1);
}

void MainWindow::on_VertexPointColor_lineEdit_textChanged(const QString& arg1) {
  viewSettings_->SetVertexColor(QColor(arg1));
  ui->VertexPointColor_lineEdit->setStyleSheet("background-color: " + arg1 +
                                               ";");
  applyContrastTextToLineEdit(ui->VertexPointColor_lineEdit, arg1);
}

void MainWindow::on_EdgeLineThickness_lineEdit_textChanged(
    const QString& arg1) {
  viewSettings_->SetEdgeThickness(arg1.toInt());
}

void MainWindow::on_VertexPointSize_lineEdit_textChanged(const QString& arg1) {
  viewSettings_->SetVertexSize(arg1.toInt());
}

void MainWindow::DottedEdgeLineTypeSelected(bool checked) {
  if (checked) {
    viewSettings_->SetLineType(EdgeType::DOTTED);
  }
}

void MainWindow::SolidEdgeLineTypeSelected(bool checked) {
  if (checked) {
    viewSettings_->SetLineType(EdgeType::SOLID);
  }
}

void MainWindow::VertexDisplayAsCircleSelected(bool checked) {
  if (checked) {
    viewSettings_->SetVertexType(VertexType::CIRCLE);
  }
}

void MainWindow::VertexDisplayAsSquareSelected(bool checked) {
  if (checked) {
    viewSettings_->SetVertexType(VertexType::SQUARE);
  }
}

void MainWindow::VertexNotDisplayedSelected(bool checked) {
  if (checked) {
    viewSettings_->SetVertexType(VertexType::NONE);
  }
}

void MainWindow::ParallelProjectionTypeSelected(bool checked) {
  if (checked) {
    viewSettings_->SetProjectionType(ProjectionType::PARALLEL);
  }
}

void MainWindow::CentralProjectionTypeSelected(bool checked) {
  if (checked) {
    viewSettings_->SetProjectionType(ProjectionType::CENTRAL);
  }
}

void MainWindow::onPushButtonSaveImageClicked() {
  QString saveDirectory = GetAplicationPath().path() + "/images_gifs/";
  QString imageFileType = ui->ImageFileType_comboBox->currentText();
  QDir dir(saveDirectory);
  if (!dir.exists()) {
    if (!dir.mkpath(saveDirectory)) {
      QMessageBox::critical(this, "Error", "Failed to create directory.");
      return;
    }
  }

  QString fileName = saveDirectory;

  QDateTime currentDateTime = QDateTime::currentDateTime();
  QString formattedDateTime = currentDateTime.toString("hh_mm_ss_dd_MM_yyyy_");
  fileName.append(formattedDateTime);

  QString modelName = ui->ModelName_textBrowser->toPlainText();
  fileName.append(modelName);
  fileName.append(imageFileType);

  fileName = QDir::toNativeSeparators(fileName);

  QImage img = sceneDrawer_->grabFramebuffer();
  if (img.isNull()) {
    QMessageBox::critical(this, "Error",
                          "Failed to capture image from OpenGL widget.");
    return;
  }

  if (!img.save(fileName)) {
    QMessageBox::critical(this, "Error", "Failed to save image.");
    return;
  }

  QMessageBox::information(this, "Success", "Image saved successfully.");
}

void MainWindow::onBackgroundResetButtonClicked() {
  ui->BackgroundColor_lineEdit->setText("#FFFFFF");
}

void MainWindow::onEdgeLineResetButtonClicked() {
  ui->EdgeLineColor_lineEdit->setText("#000000");
  ui->EdgeLineThickness_lineEdit->setText("1");
  ui->SolidEdgeLineType_radioButton->setChecked(true);
  viewSettings_->SetLineType(EdgeType::SOLID);
}

void MainWindow::onVertexPointResetButtonClicked() {
  ui->VertexPointColor_lineEdit->setText("#FF0000");
  ui->VertexPointSize_lineEdit->setText("5");
  ui->VertexDisplayAsCircle_radioButton->setChecked(true);
  viewSettings_->SetVertexType(VertexType::CIRCLE);
}

void MainWindow::onFactoryResetButtonClicked() {
  onBackgroundResetButtonClicked();
  onEdgeLineResetButtonClicked();
  onVertexPointResetButtonClicked();
  onEdgeLineResetButtonClicked();
  ui->Centering_pushButton->click();
  ui->ParallelProjectionType_radioButton->click();
}

void MainWindow::GetRotateSlider() {
  float valueX = ui->Xrotate_horizontalScrollBar->value();
  float valueY = ui->Yrotate_verticalScrollBar->value();
  float valueZ = ui->Zrotate_horizontalScrollBar->value();
  ui->XRotate_lineEdit->setText(QString::number(valueX));
  ui->YRotate_lineEdit->setText(QString::number(valueY));
  ui->ZRotate_lineEdit->setText(QString::number(valueZ));
  rotateModelRequested(valueX, valueY, valueZ);
}

void MainWindow::GetRotateEdit() {
  float valueX = ui->XRotate_lineEdit->text().toFloat();
  float valueY = ui->YRotate_lineEdit->text().toFloat();
  float valueZ = ui->ZRotate_lineEdit->text().toFloat();
  ui->Xrotate_horizontalScrollBar->setValue(int(valueX));
  ui->Yrotate_verticalScrollBar->setValue(int(valueY));
  ui->Zrotate_horizontalScrollBar->setValue(int(valueZ));
  rotateModelRequested(valueX, valueY, valueZ);
}

void MainWindow::GetTranslate() {
  float valueX = ui->XMoving_lineEdit->text().toFloat();
  float valueY = ui->YMoving_lineEdit->text().toFloat();
  float valueZ = ui->ZMoving_lineEdit->text().toFloat();
  translateModelRequested(valueX, valueY, valueZ);
}

void MainWindow::on_ZoomIn_pushButton_clicked() {
  float newZoom = ui->Zoom_lineEdit->text().toFloat() + 0.1;
  ui->Zoom_lineEdit->setText(QString::number(newZoom));
  zoomModelRequested(newZoom);
}

void MainWindow::on_ZoomOut_pushButton_clicked() {
  float newZoom = ui->Zoom_lineEdit->text().toFloat() - 0.1;
  if (newZoom < 0.001) newZoom = 0;
  ui->Zoom_lineEdit->setText(QString::number(newZoom));
  zoomModelRequested(newZoom);
}

void MainWindow::on_Zoom_lineEdit_editingFinished() {
  float newZoom = ui->Zoom_lineEdit->text().toFloat();
  if (newZoom < 0.001) {
    newZoom = 0;
    ui->Zoom_lineEdit->setText(QString::number(newZoom));
  }
  zoomModelRequested(newZoom);
}

void MainWindow::on_Centering_pushButton_clicked() {
  centeringModelRequested();
  ui->XRotate_lineEdit->setText(QString::number(0));
  ui->YRotate_lineEdit->setText(QString::number(0));
  ui->ZRotate_lineEdit->setText(QString::number(0));
  ui->XMoving_lineEdit->setText(QString::number(0));
  ui->YMoving_lineEdit->setText(QString::number(0));
  ui->ZMoving_lineEdit->setText(QString::number(0));
  ui->Xrotate_horizontalScrollBar->setValue(int(0));
  ui->Yrotate_verticalScrollBar->setValue(int(0));
  ui->Zrotate_horizontalScrollBar->setValue(int(0));
  ui->Zoom_lineEdit->setText(QString::number(1));
  rotateModelRequested(0, 0, 0);
  translateModelRequested(0, 0, 0);
  zoomModelRequested(1);
}

void MainWindow::captureScreenshot() {
  QImage screenshot = sceneDrawer_->grab().toImage();
  gifRecorder->addScreenshot(screenshot);
}

void MainWindow::toggleRecording() {
  QString modelName = ui->ModelName_textBrowser->toPlainText();
  if (gifRecorder->isRecording()) {
    gifRecorder->stopRecording(modelName);
    ui->RecordScreencast_pushButton->setText("Start Recording");
  } else {
    gifRecorder->startRecording(640, 480, 100);
    ui->RecordScreencast_pushButton->setText("Stop Recording");
  }
}

QDir MainWindow::GetAplicationPath() const {
  QDir startingDir(QCoreApplication::applicationDirPath());
#ifdef Q_OS_MAC
  startingDir.cdUp();
  startingDir.cdUp();
  startingDir.cdUp();
#endif
  return startingDir;
}

void MainWindow::ApplySettings() {
  ui->BackgroundColor_lineEdit->setText(
      viewSettings_->GetBackgroundColor().name());
  ui->EdgeLineColor_lineEdit->setText(viewSettings_->GetEdgeColor().name());
  ui->VertexPointColor_lineEdit->setText(
      viewSettings_->GetVertexColor().name());
  ui->EdgeLineThickness_lineEdit->setText(
      QString::number(viewSettings_->GetEdgeThickness()));
  ui->VertexPointSize_lineEdit->setText(
      QString::number(viewSettings_->GetVertexSize()));
  ui->XRotate_lineEdit->setText(QString::number(0));
  ui->YRotate_lineEdit->setText(QString::number(0));
  ui->ZRotate_lineEdit->setText(QString::number(0));
  ui->XMoving_lineEdit->setText(QString::number(0));
  ui->YMoving_lineEdit->setText(QString::number(0));
  ui->ZMoving_lineEdit->setText(QString::number(0));
  ui->Zoom_lineEdit->setText(QString::number(1));

  if (viewSettings_->GetLineType() == EdgeType::DOTTED) {
    ui->DottedEdgeLineType_radioButton->setChecked(true);
  } else {
    ui->SolidEdgeLineType_radioButton->setChecked(true);
  }

  if (viewSettings_->GetVertexType() == VertexType::CIRCLE) {
    ui->VertexDisplayAsCircle_radioButton->setChecked(true);
  } else {
    if (viewSettings_->GetVertexType() == VertexType::SQUARE) {
      ui->VertexDisplayAsSquare_radioButton->setChecked(true);
    } else {
      ui->VertexNotDisplayed_radioButton->setChecked(true);
    }
  }

  if (viewSettings_->GetProjectionType() == ProjectionType::PARALLEL) {
    ui->ParallelProjectionType_radioButton->setChecked(true);
  } else {
    ui->CentralProjectionType_radioButton->setChecked(true);
  }
}

void MainWindow::setInterfaceStyle() {
  this->setStyleSheet(StyleHelper::getMainWidgetStyle());
  ui->BackgroundColor_pushButton->setStyleSheet(
      StyleHelper::getActionButtonsStyle());
  ui->EdgeLineColor_pushButton->setStyleSheet(
      StyleHelper::getActionButtonsStyle());
  ui->VertexPointColor_pushButton->setStyleSheet(
      StyleHelper::getActionButtonsStyle());
  ui->OpenFile_pushButton->setStyleSheet(StyleHelper::getActionButtonsStyle());
  ui->ZoomIn_pushButton->setStyleSheet(StyleHelper::getActionButtonsStyle());
  ui->ZoomOut_pushButton->setStyleSheet(StyleHelper::getActionButtonsStyle());
  ui->BackgroundReset_pushButton->setStyleSheet(
      StyleHelper::getResetButtonsStyle());
  ui->EdgeLineReset_pushButton->setStyleSheet(
      StyleHelper::getResetButtonsStyle());
  ui->FactoryReset_pushButton->setStyleSheet(
      StyleHelper::getResetButtonsStyle());
  ui->VertexPointReset_pushButton->setStyleSheet(
      StyleHelper::getResetButtonsStyle());
  ui->CentralProjectionType_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->DottedEdgeLineType_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->ParallelProjectionType_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->SolidEdgeLineType_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->VertexDisplayAsCircle_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->VertexDisplayAsSquare_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->VertexNotDisplayed_radioButton->setStyleSheet(
      StyleHelper::getRadioButtonsStyle());
  ui->ModelName_textBrowser->setStyleSheet(StyleHelper::getTextBrowserStyle());
  ui->VerticesNumber_textBrowser->setStyleSheet(
      StyleHelper::getTextBrowserStyle());
  ui->EdgesNumber_textBrowser->setStyleSheet(
      StyleHelper::getTextBrowserStyle());
  ui->PathFile_textBrowser->setStyleSheet(StyleHelper::getTextBrowserStyle());
  ui->BackgroundColor_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->EdgeLineColor_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->VertexPointColor_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->EdgeLineThickness_lineEdit->setStyleSheet(
      StyleHelper::getLineEditStyle());
  ui->VertexPointSize_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->Zoom_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->XMoving_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->YMoving_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->ZMoving_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->XRotate_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->YRotate_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());
  ui->ZRotate_lineEdit->setStyleSheet(StyleHelper::getLineEditStyle());

  // повороты маштаб смещение
  connect(ui->Xrotate_horizontalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->Yrotate_verticalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->Zrotate_horizontalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->XRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);
  connect(ui->YRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);
  connect(ui->ZRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);

  connect(ui->XMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);
  connect(ui->YMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);
  connect(ui->ZMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);
}

void MainWindow::setupConnections() {
  connect(gifRecorder, &s21::GifRecorder::requestScreenshot, this,
          &MainWindow::captureScreenshot);
  connect(ui->RecordScreencast_pushButton, &QPushButton::clicked, this,
          &MainWindow::toggleRecording);

  connect(zoomInTimer_, &QTimer::timeout, this,
          &MainWindow::on_ZoomIn_pushButton_clicked);
  connect(zoomOutTimer_, &QTimer::timeout, this,
          &MainWindow::on_ZoomOut_pushButton_clicked);

  connect(ui->ZoomIn_pushButton, &QPushButton::pressed, this,
          [=]() { zoomInTimer_->start(); });
  connect(ui->ZoomIn_pushButton, &QPushButton::released, this,
          [=]() { zoomInTimer_->stop(); });

  connect(ui->ZoomOut_pushButton, &QPushButton::pressed, this,
          [=]() { zoomOutTimer_->start(); });
  connect(ui->ZoomOut_pushButton, &QPushButton::released, this,
          [=]() { zoomOutTimer_->stop(); });

  connect(ui->OpenFile_pushButton, &QPushButton::clicked, this,
          &MainWindow::onOpenFileButtonClicked);

  connect(ui->BackgroundColor_pushButton, &QPushButton::clicked, this,
          &MainWindow::onBackgroundColorButtonClicked);
  connect(ui->EdgeLineColor_pushButton, &QPushButton::clicked, this,
          &MainWindow::onEdgeLineColorButtonClicked);
  connect(ui->VertexPointColor_pushButton, &QPushButton::clicked, this,
          &MainWindow::onVertexPointColorButtonClicked);

  connect(ui->BackgroundColor_lineEdit, &QLineEdit::editingFinished,
          ui->openGLContainer, [=] {
            viewSettings_->SetBackgroundColor(
                QColor(ui->BackgroundColor_lineEdit->text()));
          });
  connect(
      ui->EdgeLineColor_lineEdit, &QLineEdit::editingFinished,
      ui->openGLContainer, [=] {
        viewSettings_->SetEdgeColor(QColor(ui->EdgeLineColor_lineEdit->text()));
      });
  connect(ui->VertexPointColor_lineEdit, &QLineEdit::editingFinished,
          ui->openGLContainer, [=] {
            viewSettings_->SetVertexColor(
                QColor(ui->VertexPointColor_lineEdit->text()));
          });

  connect(ui->DottedEdgeLineType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::DottedEdgeLineTypeSelected);
  connect(ui->SolidEdgeLineType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::SolidEdgeLineTypeSelected);
  connect(ui->VertexDisplayAsCircle_radioButton, &QRadioButton::clicked, this,
          &MainWindow::VertexDisplayAsCircleSelected);
  connect(ui->VertexDisplayAsSquare_radioButton, &QRadioButton::clicked, this,
          &MainWindow::VertexDisplayAsSquareSelected);
  connect(ui->VertexNotDisplayed_radioButton, &QRadioButton::clicked, this,
          &MainWindow::VertexNotDisplayedSelected);
  connect(ui->ParallelProjectionType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::ParallelProjectionTypeSelected);
  connect(ui->CentralProjectionType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::CentralProjectionTypeSelected);
  connect(ui->SaveImage_pushButton, &QPushButton::clicked, this,
          &MainWindow::onPushButtonSaveImageClicked);
  connect(ui->Xrotate_horizontalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->Yrotate_verticalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->Zrotate_horizontalScrollBar, &QSlider::valueChanged, this,
          &MainWindow::GetRotateSlider);
  connect(ui->XRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);
  connect(ui->YRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);
  connect(ui->ZRotate_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetRotateEdit);
  connect(ui->XMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);
  connect(ui->YMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);
  connect(ui->ZMoving_lineEdit, &QLineEdit::editingFinished, this,
          &MainWindow::GetTranslate);

  connect(ui->VertexPointSize_lineEdit, &QLineEdit::editingFinished,
          ui->openGLContainer, [=] {
            viewSettings_->SetVertexSize(
                ui->VertexPointSize_lineEdit->text().toFloat());
          });
  connect(ui->EdgeLineThickness_lineEdit, &QLineEdit::editingFinished,
          ui->openGLContainer, [=] {
            viewSettings_->SetEdgeThickness(
                ui->EdgeLineThickness_lineEdit->text().toFloat());
          });

  connect(ui->DottedEdgeLineType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::DottedEdgeLineTypeSelected);

  connect(ui->SolidEdgeLineType_radioButton, &QRadioButton::clicked, this,
          &MainWindow::SolidEdgeLineTypeSelected);

  connect(ui->BackgroundReset_pushButton, &QPushButton::clicked, this,
          &MainWindow::onBackgroundResetButtonClicked);
  connect(ui->EdgeLineReset_pushButton, &QPushButton::clicked, this,
          &MainWindow::onEdgeLineResetButtonClicked);
  connect(ui->VertexPointReset_pushButton, &QPushButton::clicked, this,
          &MainWindow::onVertexPointResetButtonClicked);
  connect(ui->FactoryReset_pushButton, &QPushButton::clicked, this,
          &MainWindow::onFactoryResetButtonClicked);

  connect(ui->Centering_pushButton, &QPushButton::clicked, this,
          &MainWindow::on_Centering_pushButton_clicked);
}

QColor MainWindow::getContrastColor(const QColor& backgroundColor) {
  int lightness = backgroundColor.lightness();
  return (lightness < 128) ? Qt::white : Qt::black;
}

void MainWindow::applyContrastTextToLineEdit(QLineEdit* lineEdit,
                                             const QString& nameColor) {
  QColor backgroundColor = QColor(nameColor);
  QColor contrastColor = getContrastColor(backgroundColor);
  QString currentStyleSheet = lineEdit->styleSheet();
  QString newStyleSheet =
      currentStyleSheet + "color: " + contrastColor.name() + ";";
  lineEdit->setStyleSheet(newStyleSheet);
}

}  // namespace s21