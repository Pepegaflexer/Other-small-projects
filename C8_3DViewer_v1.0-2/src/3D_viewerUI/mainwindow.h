#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QColor>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QPainter>
#include <QPalette>
#include <QProcess>
#include <QSettings>
#include <QTimer>

#include "QtGifImage-master/src/3rdParty/giflib/gif_lib.h"
#include "QtGifImage-master/src/gifimage/qgifimage.h"

typedef struct {
  int r, g, b;
} color_t;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  QFile* gif_file;
  QGifImage* gif;
  QTimer* gif_timer;
  int frames;

 private slots:
  void on_fileButton_clicked();

  void edit_mode(short mode_edit);
  void on_move_mode_clicked();
  void on_rotate_mode_clicked();
  void on_scale_mode_clicked();
  void on_edit_off_clicked();

  void on_move_slider_x_sliderMoved();
  void on_move_slider_y_sliderMoved();
  void on_move_slider_z_sliderMoved();

  void on_rotate_slider_x_sliderMoved();
  void on_rotate_slider_y_sliderMoved();
  void on_rotate_slider_z_sliderMoved();

  void on_scale_slider_sliderMoved();
  void on_scale_spin_valueChanged();

  void on_cubic_mask_clicked();
  void change_cube_color();

  void on_vertexes_color_clicked();
  void on_vertex_size_slider_sliderMoved();
  void on_vertex_size_spin_valueChanged();
  void on_lines_color_clicked();
  void line_mode(bool mode_line);
  void on_line_width_slider_sliderMoved();
  void on_line_width_spin_valueChanged();
  void on_line_mode_solid_clicked();
  void on_line_mode_dotted_clicked();
  void dot_mode(short mode_dot);
  void on_circle_mode_clicked();
  void on_square_mode_clicked();
  void on_none_mode_clicked();

  void on_background_color_pressed();
  void on_background_color_released();

  void on_central_mode_pressed();
  void on_central_mode_released();
  void on_parallel_mode_released();
  void on_parallel_mode_pressed();

  void on_screenshot_pressed();
  void on_screenshot_released();

  void on_screencast_clicked();
  void start_gif();
  void write_gif();

  void prepare_UI();
  void get_config();
  void set_config();
  QString color_toString(color_t color);

 private:
  Ui::MainWindow* ui;
  void resizeEvent(QResizeEvent*);
  short mode_edit = 0;
  short mode_dot = 0;
  bool mode_line = false;

  color_t rgba;
  color_t rgba_lines;
  QString color_lines;
  QString color_vertexes;
  QString color_facets;
  QString color_background;
  QSettings* config;
};
#endif  // MAINWINDOW_H
