#ifndef VIEWER_H
#define VIEWER_H

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QtWidgets/QWidget>

class viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit viewer(QWidget *parent = nullptr);
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();

 signals:
};

#endif  // VIEWER_H
