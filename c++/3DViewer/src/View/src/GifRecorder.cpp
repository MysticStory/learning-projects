#include "../include/GifRecorder.h"

#include <qgifimage.h>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QImageWriter>
#include <QMessageBox>

namespace s21 {

GifRecorder::GifRecorder(QObject* parent)
    : QObject(parent),
      recording_(false),
      width_(640),
      height_(480),
      delay_(100) {
  connect(&timer_, &QTimer::timeout, this, &GifRecorder::captureFrame);
}

GifRecorder::~GifRecorder() {
  if (recording_) stopRecording("");  // Остановим запись, если она ещё активна
}

void GifRecorder::startRecording(int width, int height, int delay) {
  if (recording_) return;

  width_ = width;
  height_ = height;
  delay_ = delay;
  frames_.clear();
  recording_ = true;

  timer_.start(delay);  // Запуск таймера с заданной задержкой
}

QDir GifRecorder::GetAplicationPath() const {
  QDir startingDir(QCoreApplication::applicationDirPath());
#ifdef Q_OS_MAC
  startingDir.cdUp();
  startingDir.cdUp();
  startingDir.cdUp();
#endif
  return startingDir;
}

void GifRecorder::stopRecording(const QString& filename) {
  if (!recording_) return;

  timer_.stop();
  recording_ = false;

  if (frames_.isEmpty()) {
    qWarning() << "No frames captured for GIF.";
    return;
  }

  // Создаем директорию для сохранения, если ее нет
  QString saveDirectory = GetAplicationPath().path() + "/images_gifs/";
  QDir dir(saveDirectory);
  if (!dir.exists() && !dir.mkpath(saveDirectory)) {
    qWarning() << "Failed to create directory:" << saveDirectory;
    return;
  }

  QString fileName =
      filename.isEmpty()
          ? saveDirectory +
                QDateTime::currentDateTime().toString("hh_mm_ss_dd_MM_yyyy.gif")
          : saveDirectory + filename +
                QDateTime::currentDateTime().toString(
                    "_hh_mm_ss_dd_MM_yyyy.gif");

  // Проверяем наличие расширения .gif
  if (!fileName.endsWith(".gif")) {
    fileName += ".gif";
  }

  // Создание GIF с использованием QGifImage
  QGifImage gif;
  gif.setDefaultDelay(delay_);

  for (const QImage& frame : frames_) {
    gif.addFrame(frame.scaled(width_, height_));
  }

  if (!gif.save(fileName)) {
    qWarning() << "Failed to save GIF to" << fileName;
    return;
  }

  qDebug() << "GIF saved successfully to" << fileName;
  frames_.clear();
}

void GifRecorder::addScreenshot(const QImage& frame) {
  if (recording_) {
    frames_.append(
        frame.scaled(width_, height_,
                     Qt::KeepAspectRatioByExpanding));  // Добавляем кадр с
                                                        // указанными размерами
  }
}

void GifRecorder::captureFrame() {
  if (!recording_) return;

  emit requestScreenshot();
}

}  // namespace s21