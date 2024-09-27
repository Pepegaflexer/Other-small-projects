#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  config = new QSettings("baggmela", "3D_viewer", this);

  get_config();
  prepare_UI();
}

MainWindow::~MainWindow() {
  set_config();
  freeData(&ui->viewer_widget->srcData);
  delete ui;
}

void MainWindow::resizeEvent(QResizeEvent*) {
  QSize size = this->size();
  int height = size.height();
  int width = size.width();
  ui->groupBox->setGeometry(width / 2 - 315, 20, 630, 70);
  ui->file_info->setGeometry(width / 2 - 315, 54, 630, 61);
  ui->color_bar->setGeometry(width / 2 - 200, 140, 401, 211);
  ui->scale_bar->setGeometry(width / 2 - 258, 140, 211, 111);
  ui->rotate_bar->setGeometry(width / 2 - 258, 140, 211, 191);
  ui->move_bar->setGeometry(width / 2 - 258, 140, 211, 191);
  ui->viewer_widget->setGeometry(0, 0, width, height);
}

void MainWindow::prepare_UI() {
  connect(ui->line_width_spin, SIGNAL(valueChanged(int)), ui->line_width_slider,
          SLOT(setValue(int)));
  connect(ui->line_width_slider, SIGNAL(valueChanged(int)), ui->line_width_spin,
          SLOT(setValue(int)));
  connect(ui->vertex_size_spin, SIGNAL(valueChanged(int)),
          ui->vertex_size_slider, SLOT(setValue(int)));
  connect(ui->vertex_size_slider, SIGNAL(valueChanged(int)),
          ui->vertex_size_spin, SLOT(setValue(int)));

  connect(ui->rotate_slider_x, SIGNAL(valueChanged(int)), ui->rotate_spin_x,
          SLOT(setValue(int)));
  connect(ui->rotate_spin_x, SIGNAL(valueChanged(int)), ui->rotate_slider_x,
          SLOT(setValue(int)));
  connect(ui->rotate_slider_y, SIGNAL(valueChanged(int)), ui->rotate_spin_y,
          SLOT(setValue(int)));
  connect(ui->rotate_spin_y, SIGNAL(valueChanged(int)), ui->rotate_slider_y,
          SLOT(setValue(int)));
  connect(ui->rotate_slider_z, SIGNAL(valueChanged(int)), ui->rotate_spin_z,
          SLOT(setValue(int)));
  connect(ui->rotate_spin_z, SIGNAL(valueChanged(int)), ui->rotate_slider_z,
          SLOT(setValue(int)));

  ui->vertex_size_slider->setValue(ui->viewer_widget->vertex_size);
  ui->line_width_slider->setValue(ui->viewer_widget->line_width);

  ui->fileButton->setIcon(QIcon(":/images/images/File.png"));
  ui->central_mode->setIcon(QIcon(":/images/images/Central.png"));
  ui->parallel_mode->setIcon(QIcon(":/images/images/Parallel.png"));
  ui->background_color->setIcon(QIcon(":/images/images/Screen_tamplate.png"));

  this->setStyleSheet("QMainWindow{" + color_background + "}");
  ui->vertexes_color->setStyleSheet(color_vertexes);
  ui->lines_color->setStyleSheet(color_lines);
  ui->cube_background_3->setStyleSheet(color_background);

  ui->file_info->setVisible(false);
  ui->move_bar->setVisible(false);
  ui->rotate_bar->setVisible(false);
  ui->scale_bar->setVisible(false);
  ui->color_bar->setVisible(false);

  change_cube_color();
  dot_mode(mode_dot);
  line_mode(mode_line);
}
// === open file === //
void MainWindow::on_fileButton_clicked() {
  ui->fileButton->setIcon(QIcon(":/images/images/File_pressed.png"));
  QString title, directory = "\0";
  QString file_filter = tr("OBJ (*.obj)");
  QString vertex_count, line_count = "\0";
  QString absolute_path = QFileDialog::getOpenFileName(
      this, title, directory, file_filter, &file_filter);
  QFile file(absolute_path);

  if (file.open(QIODevice::ReadOnly)) {
    QByteArray file_path = absolute_path.toLocal8Bit();
    char* filepath = file_path.data();
    while (absolute_path.contains('/') || absolute_path.contains('\''))
      absolute_path.remove(0, 1);
    //            qDebug() << filepath;
    reader(&ui->viewer_widget->srcData, filepath);
    ui->viewer_widget->scaleStart(&ui->viewer_widget->srcData);
    findMinMaxX(&ui->viewer_widget->srcData);
    findMinMaxY(&ui->viewer_widget->srcData);
    findMinMaxZ(&ui->viewer_widget->srcData);
    ui->viewer_widget->moveCenter(&ui->viewer_widget->srcData);

    vertex_count =
        QString::number(ui->viewer_widget->srcData.count_of_vertexes);
    line_count = QString::number(ui->viewer_widget->srcData.count_of_facets);
    ui->viewer_widget->update();
    ui->file_name->setText(absolute_path);
    ui->file_info->setVisible(true);
    ui->file_vertexes->setText("Vertexes: " + vertex_count);
    ui->file_lines->setText("Lines: " + line_count);
    file.close();
  }
  ui->fileButton->setIcon(QIcon(":/images/images/File.png"));
}

void MainWindow::on_edit_off_clicked() { edit_mode(0); }

void MainWindow::on_move_mode_clicked() { edit_mode(1); }

void MainWindow::on_rotate_mode_clicked() { edit_mode(2); }

void MainWindow::on_scale_mode_clicked() { edit_mode(3); }

void MainWindow::edit_mode(short mode_edit) {
  if (ui->color_bar->isVisible()) on_cubic_mask_clicked();
  if (mode_edit == 0) {
    ui->move_mode->setIcon(QIcon(":/images/images/Move.png"));
    ui->rotate_mode->setIcon(QIcon(":/images/images/Rotate.png"));
    ui->scale_mode->setIcon(QIcon(":/images/images/Scale.png"));
    ui->move_bar->setVisible(false);
    ui->rotate_bar->setVisible(false);
    ui->scale_bar->setVisible(false);
  } else if (mode_edit == 1) {
    ui->move_mode->setIcon(QIcon(":/images/images/Move_pressed.png"));
    ui->rotate_mode->setIcon(QIcon(":/images/images/Rotate.png"));
    ui->scale_mode->setIcon(QIcon(":/images/images/Scale.png"));
    ui->move_bar->setVisible(true);
    ui->rotate_bar->setVisible(false);
    ui->scale_bar->setVisible(false);
  } else if (mode_edit == 2) {
    ui->move_mode->setIcon(QIcon(":/images/images/Move.png"));
    ui->rotate_mode->setIcon(QIcon(":/images/images/Rotate_pressed.png"));
    ui->scale_mode->setIcon(QIcon(":/images/images/Scale.png"));
    ui->move_bar->setVisible(false);
    ui->rotate_bar->setVisible(true);
    ui->scale_bar->setVisible(false);
  } else if (mode_edit == 3) {
    ui->move_mode->setIcon(QIcon(":/images/images/Move.png"));
    ui->rotate_mode->setIcon(QIcon(":/images/images/Rotate.png"));
    ui->scale_mode->setIcon(QIcon(":/images/images/Scale_pressed.png"));
    ui->move_bar->setVisible(false);
    ui->rotate_bar->setVisible(false);
    ui->scale_bar->setVisible(true);
  }
}

// === move === //
void MainWindow::on_move_slider_x_sliderMoved() {
  ui->viewer_widget->x_move = 0;
  ui->viewer_widget->x_move += (double)ui->move_slider_x->value() / 10;
  ui->viewer_widget->update();
}

void MainWindow::on_move_slider_y_sliderMoved() {
  ui->viewer_widget->y_move = 0;
  ui->viewer_widget->y_move += (double)ui->move_slider_y->value() / 10;
  ui->viewer_widget->update();
}

void MainWindow::on_move_slider_z_sliderMoved() {
  ui->viewer_widget->z_move = 0;
  ui->viewer_widget->z_move += (double)ui->move_slider_z->value() / 10;
  ui->viewer_widget->update();
}

// === rotate === //
void MainWindow::on_rotate_slider_x_sliderMoved() {
  ui->viewer_widget->x_rotate = 0;
  ui->viewer_widget->x_rotate = (double)ui->rotate_slider_x->value();
  ui->viewer_widget->update();
}

void MainWindow::on_rotate_slider_y_sliderMoved() {
  ui->viewer_widget->y_rotate = 0;
  ui->viewer_widget->y_rotate = (double)ui->rotate_slider_y->value();
  ui->viewer_widget->update();
}

void MainWindow::on_rotate_slider_z_sliderMoved() {
  ui->viewer_widget->z_rotate = 0;
  ui->viewer_widget->z_rotate = (double)ui->rotate_slider_z->value();
  ui->viewer_widget->update();
}

// === scale === //
void MainWindow::on_scale_slider_sliderMoved() {
  ui->viewer_widget->x_scale = 0;
  ui->viewer_widget->y_scale = 0;
  ui->viewer_widget->z_scale = 0;
  ui->viewer_widget->x_scale = ((double)ui->scale_slider->value() * 0.1) + 1;
  ui->viewer_widget->y_scale = ((double)ui->scale_slider->value() * 0.1) + 1;
  ui->viewer_widget->z_scale = ((double)ui->scale_slider->value() * 0.1) + 1;
  ui->scale_spin->setValue(ui->scale_slider->value());
  ui->viewer_widget->update();
}

void MainWindow::on_scale_spin_valueChanged() {
  ui->viewer_widget->x_scale = 0;
  ui->viewer_widget->y_scale = 0;
  ui->viewer_widget->z_scale = 0;
  ui->viewer_widget->x_scale = ((double)ui->scale_spin->value() * 0.1) + 1;
  ui->viewer_widget->y_scale = ((double)ui->scale_spin->value() * 0.1) + 1;
  ui->viewer_widget->z_scale = ((double)ui->scale_spin->value() * 0.1) + 1;
  ui->scale_slider->setValue(ui->scale_spin->value());
  ui->viewer_widget->update();
}

void MainWindow::on_cubic_mask_clicked() {
  if (ui->color_bar->isVisible())
    ui->color_bar->setVisible(false);
  else {
    ui->color_bar->setVisible(true);
    if (ui->move_bar->isVisible() || ui->rotate_bar->isVisible() ||
        ui->scale_bar->isVisible())
      on_edit_off_clicked();
  }
}

void MainWindow::change_cube_color() {
  QColor color;
  color.setRed(rgba_lines.r);
  color.setGreen(rgba_lines.g);
  color.setBlue(rgba_lines.b);
  QPixmap cube(":/images/images/Cube.png");
  cube.scaled(35, 35, Qt::IgnoreAspectRatio, Qt::FastTransformation);
  QPixmap mask(cube.size());
  mask.scaled(35, 35, Qt::IgnoreAspectRatio, Qt::FastTransformation);
  mask.fill(color);
  mask.setMask(cube.createMaskFromColor(Qt::transparent));
  ui->cubic->setPixmap(mask);
}

// === center === //
void MainWindow::on_central_mode_pressed() {
  ui->central_mode->setIcon(QIcon(":/images/images/Central_pressed.png"));
}

void MainWindow::on_central_mode_released() {
  ui->central_mode->setIcon(QIcon(":/images/images/Central.png"));
  ui->viewer_widget->proection_type = 1;
  ui->viewer_widget->update();
}

// === parallel === //
void MainWindow::on_parallel_mode_pressed() {
  ui->parallel_mode->setIcon(QIcon(":/images/images/Parallel_pressed.png"));
}

void MainWindow::on_parallel_mode_released() {
  ui->parallel_mode->setIcon(QIcon(":/images/images/Parallel.png"));
  ui->viewer_widget->proection_type = 0;
  ui->viewer_widget->update();
}

// === color === //
void MainWindow::on_vertexes_color_clicked() {
  QColor qcolor_vertexes =
      QColorDialog::getColor(Qt::lightGray, this, tr("Выберите цвет точек"));
  qcolor_vertexes.getRgb(&rgba.r, &rgba.g, &rgba.b);
  ui->viewer_widget->vertex_rgb.r = (float)rgba.r / 255;
  ui->viewer_widget->vertex_rgb.g = (float)rgba.g / 255;
  ui->viewer_widget->vertex_rgb.b = (float)rgba.b / 255;
  color_vertexes = color_toString(rgba);
  ui->vertexes_color->setStyleSheet(color_vertexes);
  ui->viewer_widget->update();
}

void MainWindow::on_lines_color_clicked() {
  QColor qcolor_lines =
      QColorDialog::getColor(Qt::lightGray, this, tr("Выберите цвет линий"));
  qcolor_lines.getRgb(&rgba.r, &rgba.g, &rgba.b);
  ui->viewer_widget->line_rgb.r = (float)rgba.r / 255;
  ui->viewer_widget->line_rgb.g = (float)rgba.g / 255;
  ui->viewer_widget->line_rgb.b = (float)rgba.b / 255;
  rgba_lines = rgba;
  color_lines = color_toString(rgba_lines);
  ui->lines_color->setStyleSheet(color_lines);
  ui->viewer_widget->update();
  change_cube_color();
}

void MainWindow::on_line_width_slider_sliderMoved() {
  ui->viewer_widget->line_width = ui->line_width_slider->value();
  ui->viewer_widget->update();
}

void MainWindow::on_line_width_spin_valueChanged() {
  ui->viewer_widget->line_width = ui->line_width_spin->value();
  ui->viewer_widget->update();
}

void MainWindow::on_vertex_size_slider_sliderMoved() {
  ui->viewer_widget->vertex_size = ui->vertex_size_slider->value();
  ui->viewer_widget->update();
}

void MainWindow::on_vertex_size_spin_valueChanged() {
  ui->viewer_widget->vertex_size = ui->vertex_size_spin->value();
  ui->viewer_widget->update();
}

void MainWindow::on_background_color_pressed() {
  QColor qcolor_background =
      QColorDialog::getColor(Qt::gray, this, tr("Выберите цвет фона"));
  qcolor_background.getRgb(&rgba.r, &rgba.g, &rgba.b);
  ui->viewer_widget->bg_rgb.r = (float)rgba.r / 255;
  ui->viewer_widget->bg_rgb.g = (float)rgba.g / 255;
  ui->viewer_widget->bg_rgb.b = (float)rgba.b / 255;
  color_background = color_toString(rgba);
  ui->cube_background_3->setStyleSheet(color_background);
  QMainWindow::setStyleSheet("QMainWindow{" + color_background + "}");
}

void MainWindow::on_background_color_released() {
  ui->background_color->setIcon(QIcon(":/images/images/Screen_tamplate.png"));
}

// === screenshot === //
void MainWindow::on_screenshot_pressed() {
  ui->screenshot->setIcon(QIcon(":/images/images/Screenshot_pressed.png"));
}

void MainWindow::on_screenshot_released() {
  ui->screenshot->setIcon(QIcon(":/images/images/Screenshot.png"));
  QString file_name = QFileDialog::getSaveFileName(
      0, "Сохранить скриншот как...", "", tr("PNG (*.png);;BMP (*.bmp)"));
  ui->viewer_widget->grabFramebuffer().save(file_name);
}

// === gif === //
void MainWindow::on_screencast_clicked() {
  ui->screencast->setIcon(QIcon(":/images/images/Screencast_pressed.png"));
  QString file_name = QFileDialog::getSaveFileName(
      this, "Сохранить GIF", QDir::homePath(), "GIF (*.gif)");

  gif_file = new QFile(file_name);
  if (!gif_file->open(QIODevice::WriteOnly))
    QMessageBox::critical(this, "Warning", "Не удалось записать файл");
  else
    start_gif();
  ui->screencast->setIcon(QIcon(":/images/images/Screencast.png"));
}

void MainWindow::start_gif() {
  gif = new QGifImage(QSize(640, 480));
  gif_timer = new QTimer(this);
  connect(gif_timer, &QTimer::timeout, this, &MainWindow::write_gif);
  gif_timer->start(100);
  frames = 0;
}

void MainWindow::write_gif() {
  QRect rect(0, 0, 640, 480);  // this->size().height(), this->size().width()
  QPixmap pixmap = ui->viewer_widget->grab(rect);

  QImage img = pixmap.toImage();
  frames++;
  gif->addFrame(img, 100);  // цифра это задержка
  if (frames == 50) {
    gif_timer->stop();
    gif->save(gif_file);
    gif_file->close();
    delete gif_file;
    gif_file = nullptr;
    delete gif;
    gif = nullptr;
  }
}

// === режим отображения точек === //
void MainWindow::on_circle_mode_clicked() {
  mode_dot = 1;
  dot_mode(mode_dot);
}

void MainWindow::on_square_mode_clicked() {
  mode_dot = 2;
  dot_mode(mode_dot);
}

void MainWindow::on_none_mode_clicked() {
  mode_dot = 0;
  dot_mode(mode_dot);
}

void MainWindow::dot_mode(short mode_dot) {
  if (mode_dot == 1) {
    ui->circle_mode->setIcon(QIcon(":/images/images/Dot_circle_pressed.png"));
    ui->square_mode->setIcon(QIcon(":/images/images/Dot_square.png"));
    ui->none_mode->setIcon(QIcon(":/images/images/Dot_none.png"));
    ui->viewer_widget->vertex_type = 1;
    ui->viewer_widget->update();
  } else if (mode_dot == 2) {
    ui->circle_mode->setIcon(QIcon(":/images/images/Dot_circle.png"));
    ui->square_mode->setIcon(QIcon(":/images/images/Dot_square_pressed.png"));
    ui->none_mode->setIcon(QIcon(":/images/images/Dot_none.png"));
    ui->viewer_widget->vertex_type = 2;
    ui->viewer_widget->update();
  } else if (mode_dot == 0) {
    ui->circle_mode->setIcon(QIcon(":/images/images/Dot_circle.png"));
    ui->square_mode->setIcon(QIcon(":/images/images/Dot_square.png"));
    ui->none_mode->setIcon(QIcon(":/images/images/Dot_none_pressed.png"));
    ui->viewer_widget->vertex_type = 0;
    ui->viewer_widget->update();
  }
}

void MainWindow::on_line_mode_solid_clicked() {
  mode_line = false;
  line_mode(mode_line);
}

void MainWindow::on_line_mode_dotted_clicked() {
  mode_line = true;
  line_mode(mode_line);
}

void MainWindow::line_mode(bool mode_line) {
  if (!mode_line) {
    ui->line_mode_solid->setIcon(
        QIcon(":/images/images/Dot_square_pressed.png"));
    ui->line_mode_dotted->setIcon(QIcon(":/images/images/Square_dotted.png"));
    ui->viewer_widget->line_type = 1;
    ui->viewer_widget->update();
  } else {
    ui->line_mode_solid->setIcon(QIcon(":/images/images/Dot_square.png"));
    ui->line_mode_dotted->setIcon(
        QIcon(":/images/images/Square_dotted_pressed.png"));
    ui->viewer_widget->line_type = 2;
    ui->viewer_widget->update();
  }
}

QString MainWindow::color_toString(color_t color) {
  QString rt = QString::number(color.r);
  QString gt = QString::number(color.g);
  QString bt = QString::number(color.b);
  QString color_string =
      "background-color:rgba( " + rt + ", " + gt + ", " + bt + ", 100% );";
  return color_string;
}

void MainWindow::set_config() {  // save
  config->setValue("mode_dot", mode_dot);
  config->setValue("mode_line", mode_line);
  config->setValue("vertex_size", ui->viewer_widget->vertex_size);
  config->setValue("line_width", ui->viewer_widget->line_width);
  config->setValue("color_vertexes", color_vertexes);
  config->setValue("color_lines", color_lines);
  config->setValue("color_facets", color_facets);
  config->setValue("color_background", color_background);
  config->setValue("r", rgba_lines.r);
  config->setValue("g", rgba_lines.g);
  config->setValue("b", rgba_lines.b);

  config->setValue("vertex_rgb.r", ui->viewer_widget->vertex_rgb.r);
  config->setValue("vertex_rgb.g", ui->viewer_widget->vertex_rgb.g);
  config->setValue("vertex_rgb.b", ui->viewer_widget->vertex_rgb.b);
  config->setValue("vertex_type", ui->viewer_widget->vertex_type);
  config->setValue("vertex_size", ui->viewer_widget->vertex_size);

  config->setValue("line_rgb.r", ui->viewer_widget->line_rgb.r);
  config->setValue("line_rgb.g", ui->viewer_widget->line_rgb.g);
  config->setValue("line_rgb.b", ui->viewer_widget->line_rgb.b);
  config->setValue("line_type", ui->viewer_widget->line_type);
  config->setValue("line_width", ui->viewer_widget->line_width);

  config->setValue("bg_rgb.r", ui->viewer_widget->bg_rgb.r);
  config->setValue("bg_rgb.g", ui->viewer_widget->bg_rgb.g);
  config->setValue("bg_rgb.b", ui->viewer_widget->bg_rgb.b);
}

void MainWindow::get_config() {  // load
  mode_dot = config->value("mode_dot").toInt();
  mode_line = config->value("mode_line").toBool();
  ui->viewer_widget->vertex_size = config->value("vertex_size").toInt();
  ui->viewer_widget->line_width = config->value("line_width").toInt();
  color_vertexes = config->value("color_vertexes").toString();
  color_lines = config->value("color_lines").toString();
  color_facets = config->value("color_facets").toString();
  color_background = config->value("color_background").toString();
  rgba_lines.r = config->value("r").toInt();
  rgba_lines.g = config->value("g").toInt();
  rgba_lines.b = config->value("b").toInt();

  ui->viewer_widget->vertex_rgb.r = config->value("vertex_rgb.r").toFloat();
  ui->viewer_widget->vertex_rgb.g = config->value("vertex_rgb.g").toFloat();
  ui->viewer_widget->vertex_rgb.b = config->value("vertex_rgb.b").toFloat();
  ui->viewer_widget->vertex_type = config->value("vertex_type").toInt();
  ui->viewer_widget->vertex_size = config->value("vertex_size").toInt();

  ui->viewer_widget->line_rgb.r = config->value("line_rgb.r").toFloat();
  ui->viewer_widget->line_rgb.g = config->value("line_rgb.g").toFloat();
  ui->viewer_widget->line_rgb.b = config->value("line_rgb.b").toFloat();
  ui->viewer_widget->line_type = config->value("line_type").toInt();
  ui->viewer_widget->line_width = config->value("line_width").toInt();

  ui->viewer_widget->bg_rgb.r = config->value("bg_rgb.r").toFloat();
  ui->viewer_widget->bg_rgb.g = config->value("bg_rgb.g").toFloat();
  ui->viewer_widget->bg_rgb.b = config->value("bg_rgb.b").toFloat();
}
