#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets/QWidget>

extern "C" {
#include "../c_sources/3d_viewer.h"
}

typedef struct {
  float r, g, b;
} rgb_gl;

QT_BEGIN_NAMESPACE
namespace Ui {
class ModelViewer;
}
QT_END_NAMESPACE

class ModelViewer : public QOpenGLWidget {
  Q_OBJECT

 private:
 public:
  ModelViewer(QWidget *parent = nullptr);
  ~ModelViewer();
  bool model_loaded;
  dataStruct srcData;

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void draw();

  short line_width = 5, line_type = 1;  // 0 - нет, 1 - обычная, 2 - пунктир
  rgb_gl line_rgb = {0, 0.255, 0.255};
  void draw_line();

  short vertex_size = 20, vertex_type = 1;
  rgb_gl vertex_rgb = {0.255, 0.255, 0};
  void draw_vertex();

  rgb_gl bg_rgb = {0.2, 0.2, 0.2};
  QPoint mouse_pos;
  bool move_or_rotate;
  short proection_type = 1;
  double x_move = 0, y_move = 0, z_move = 0;
  double x_scale = 1, y_scale = 1, z_scale = 1;
  double x_rotate = 0, y_rotate = 0, z_rotate = 0;

  // L - вращение, R - перемещение
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);

  void moveCenter(data_struct *srcData);
  void scaleStart(data_struct *srcData);
  double findMax(double x, double y, double z);

 private slots:

 private:
  Ui::ModelViewer *ui;
};

#endif  // MODELVIEWER_H
