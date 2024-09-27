#include "modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent) : QOpenGLWidget(parent) {
  srcData.count_of_facets = 0;
  srcData.count_of_vertexes = 0;
  srcData.matrix_3d.columns = 0;
  srcData.matrix_3d.rows = 0;
  srcData.matrix_3d.matrix = {0};
  srcData.polygons = {0};
}

ModelViewer::~ModelViewer() {}

void ModelViewer::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT, GL_FILL);
}

void ModelViewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void ModelViewer::paintGL() {
  glClearColor(bg_rgb.r, bg_rgb.g, bg_rgb.b, 0);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);

  if (proection_type == 1) {
    glFrustum(-1, 1, -1, 1, 1, 800);
    glTranslated(0, 0, -2);
    glTranslated(x_move, y_move,
                 z_move - (srcData.minMaxZ[1] - srcData.minMaxZ[0]));
  } else {
    glOrtho(srcData.minMaxX[0], srcData.minMaxX[1], srcData.minMaxY[0],
            srcData.minMaxY[1], srcData.minMaxZ[0], srcData.minMaxZ[1]);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslated(x_move, y_move, z_move);

  glRotated(x_rotate, 1, 0, 0);
  glRotated(y_rotate, 0, 1, 0);
  glRotated(z_rotate, 0, 0, 1);
  glScaled(x_scale, y_scale, z_scale);

  draw_line();
  draw();
  draw_vertex();
}

void ModelViewer::draw() {
  double x = 0, y = 0, z = 0;

  for (int i = 0; i < srcData.count_of_facets; i++) {
    for (int j = 0; j < srcData.polygons[i].num_of_ver_in_facets; j++) {
      x = srcData.matrix_3d.matrix[srcData.polygons[i].vertexes[j] - 1][0];
      y = srcData.matrix_3d.matrix[srcData.polygons[i].vertexes[j] - 1][1];
      z = srcData.matrix_3d.matrix[srcData.polygons[i].vertexes[j] - 1][2];
      glColor3d(line_rgb.r, line_rgb.g, line_rgb.b);
      glPointSize(vertex_size);
      glEnable(GL_POINT_SMOOTH);
      glBegin(GL_LINE_LOOP | GL_POINTS);
      glVertex3d(x, y, z);
    }
    glEnd();
  }
}

void ModelViewer::draw_line() {  // линии
  if (line_type != 0) glLineWidth(line_width);
  if (line_type != 2)
    glDisable(GL_LINE_STIPPLE);
  else if (line_type == 2) {
    glLineStipple(3, 0x00F0);
    glEnable(GL_LINE_STIPPLE);
  }
}

void ModelViewer::draw_vertex() {  // вершины
  double x = 0, y = 0, z = 0;

  glPointSize(vertex_size);
  if (vertex_type == 1)
    glEnable(GL_POINT_SMOOTH);
  else if (vertex_type == 2)
    glDisable(GL_POINT_SMOOTH);
  for (int i = 0; i < srcData.count_of_vertexes; i++) {
    x = srcData.matrix_3d.matrix[i][0];
    y = srcData.matrix_3d.matrix[i][1];
    z = srcData.matrix_3d.matrix[i][2];
    if (vertex_type != 0) glBegin(GL_POINTS);
    glColor3d(vertex_rgb.r, vertex_rgb.g, vertex_rgb.b);
    glVertex3d(x, y, z);
    glEnd();
  }
}

void ModelViewer::moveCenter(data_struct *srcData) {  // отцентровка фигура
  double centerX = 0, centerY = 0, centerZ = 0;
  centerX =
      srcData->minMaxX[0] + (srcData->minMaxX[1] - srcData->minMaxX[0]) / 2;
  centerY =
      srcData->minMaxY[0] + (srcData->minMaxY[1] - srcData->minMaxY[0]) / 2;
  centerZ =
      srcData->minMaxZ[0] + (srcData->minMaxZ[1] - srcData->minMaxZ[0]) / 2;
  if (centerX != 0) {
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      srcData->matrix_3d.matrix[i][0] =
          srcData->matrix_3d.matrix[i][0] - centerX;
    }
  }
  if (centerY != 0) {
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      srcData->matrix_3d.matrix[i][1] =
          srcData->matrix_3d.matrix[i][1] - centerY;
    }
  }
  if (centerZ != 0) {
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      srcData->matrix_3d.matrix[i][2] =
          srcData->matrix_3d.matrix[i][2] - centerY;
    }
  }
}

void ModelViewer::scaleStart(
    data_struct *srcData) {  // сколируется при старте что бы
  double x = 0, y = 0, z = 0;  // фигура занимала 80% поля
  matrix_t tmpMatrix;
  s21_create_matrix(srcData->count_of_vertexes, 3, &tmpMatrix);
  x = srcData->minMaxX[1] - srcData->minMaxX[0];
  y = srcData->minMaxY[1] - srcData->minMaxY[0];
  z = srcData->minMaxZ[1] - srcData->minMaxZ[0];
  double max = findMax(x, y, z);
  double scale = (0.8 - (0.8 * (-1))) / max;
  s21_mult_number(&(srcData->matrix_3d), scale, &tmpMatrix);
  srcData->matrix_3d = tmpMatrix;
}

double ModelViewer::findMax(double x, double y,
                            double z) {  // ф-ия для помощи в просчете  скейла
  double max = 0;
  if (x > y && x > z) {
    max = x;
  } else if (y > x && y > z) {
    max = y;
  } else {
    max = z;
  }
  return max;
}

void ModelViewer::mousePressEvent(QMouseEvent *event) {
  mouse_pos = event->pos();
  if (event->button() == Qt::LeftButton)
    move_or_rotate = true;
  else if (event->button() == Qt::RightButton)
    move_or_rotate = false;
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event) {
  if (move_or_rotate) {
    x_rotate = 1 / M_PI * (event->pos().y() - mouse_pos.y());
    y_rotate = 1 / M_PI * (event->pos().x() - mouse_pos.x());
    update();
  } else if (!move_or_rotate) {
    x_move = 0.01 / M_PI * (event->pos().x() - mouse_pos.x());
    y_move = (-0.01) / M_PI * (event->pos().y() - mouse_pos.y());
    update();
  }
}

void ModelViewer::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    x_scale *= 0.9;
    y_scale *= 0.9;
    z_scale *= 0.9;
  } else {
    x_scale *= 1.1;
    y_scale *= 1.1;
    z_scale *= 1.1;
  }
  update();
}
