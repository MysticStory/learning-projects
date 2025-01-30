#ifndef GIFRECORDER_H
#define GIFRECORDER_H

#include <QDir>
#include <QImage>
#include <QString>
#include <QTimer>
#include <QVector>
namespace s21 {

class GifRecorder : public QObject {
  Q_OBJECT

 signals:
  void requestScreenshot();

 public slots:
  void emitRequestScreenshot() { emit requestScreenshot(); }

 public:
  explicit GifRecorder(QObject* parent = nullptr);
  ~GifRecorder();

  void startRecording(int width, int height, int delay = 100);
  void stopRecording(const QString& filename);
  void addScreenshot(const QImage& frame);

  bool isRecording() const { return recording_; }

 private slots:
  void captureFrame();
  QDir GetAplicationPath() const;

 private:
  bool recording_ = false;
  int width_;
  int height_;
  int delay_;  // Задержка между кадрами
  QVector<QImage> frames_;
  QTimer timer_;
};

}  // namespace s21

#endif  // GIFRECORDER_H