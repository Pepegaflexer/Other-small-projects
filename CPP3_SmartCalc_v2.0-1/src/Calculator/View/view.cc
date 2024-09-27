#include "view.h"

#include "ui_view.h"

using namespace s21;

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
  this->controller_ = controller;
  ui->setupUi(this);
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  ui->widget->setBackground(plotGradient);
  init_slots();
}

View::~View() { delete ui; }

void View::init_slots() {
  // циферки
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(number_clicked()));
  // скобочка скобочка
  connect(ui->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(number_clicked()));
  connect(ui->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(number_clicked()));

  // синусы и косинусы
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_natlog, SIGNAL(clicked()), this,
          SLOT(number_clicked()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(number_clicked()));
  connect(ui->pushButton_koren, SIGNAL(clicked()), this,
          SLOT(number_clicked()));

  // операторы
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(op_clicked()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(op_clicked()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(op_clicked()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(op_clicked()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(op_clicked()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(op_clicked()));
  // equal
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(calculation()));
  // graph
  connect(ui->pushButton_GR, SIGNAL(clicked()), this, SLOT(graphic()));
  // dot
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(d_clicked()));
  //Очистить строку для ввода выражения
  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(ac_clicked()));
  //удалить один символ
  connect(ui->pushButton_backSpace, SIGNAL(clicked()), this,
          SLOT(bs_clicked()));
  // проверка и редактирвоание ввода
  connect(ui->vvodnaya_stroka, SIGNAL(textChanged(QString)), this,
          SLOT(validate()));

  // кредит
  connect(ui->pushButtonCR, SIGNAL(clicked()), this, SLOT(credit_clicked()));
}

void View::number_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString str;
  if (ui->vvodnaya_stroka->text() == "0") {
    ui->vvodnaya_stroka->setText("");
  }
  str = ui->vvodnaya_stroka->text() + button->text();
  ui->vvodnaya_stroka->setText(str);
}

void View::op_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString str = ui->vvodnaya_stroka->text();
  if (str.endsWith('+') || str.endsWith('-') || str.endsWith('*') ||
      str.endsWith('/') || str.endsWith('%') || str.endsWith('^')) {
    str.chop(1);
  }
  ui->vvodnaya_stroka->setText(str + button->text());
}

void View::d_clicked() {
  ui->vvodnaya_stroka->setText(ui->vvodnaya_stroka->text() + ".");
}

void View::ac_clicked() { ui->vvodnaya_stroka->setText("0"); }

void View::bs_clicked() {
  QString str = ui->vvodnaya_stroka->text();
  str.chop(1);
  static QRegularExpression re1(
      "(sin$|cos$|tan$|acos$|asin$|atan$|ln$|log$|sqrt$)");
  str.replace(re1, "");
  if (str.isEmpty()) {
    str.append('0');
  }
  ui->vvodnaya_stroka->setText(str);
}

void View::validate() {
  QString str = ui->vvodnaya_stroka->text();
  str.replace("..", ".");
  static QRegularExpression re("(\\d*\\.\\d+)\\.");
  str.replace(re, "\\1");
  static QRegularExpression re1("(\\D)\\.");
  str.replace(re1, "\\10.");
  static QRegularExpression re2("(\\d)\\.(\\D)");
  str.replace(re2, "\\1\\2");
  static QRegularExpression re3("si$|co$|ta$|aco$|asi$|ata$|l$|lo$|sqr$");
  str.replace(re3, "");
  static QRegularExpression re4(
      "(\\d|x|\\))(sin$|cos$|tan$|acos$|asin$|atan$|ln$|log$|sqrt$|x$|\\()");
  str.replace(re4, "\\1*\\2");
  static QRegularExpression re5(
      "(sin$|cos$|tan$|acos$|asin$|atan$|ln$|log$|sqrt$)");
  str.replace(re5, "\\1(");
  static QRegularExpression re6("(x|\\))(\\d)");
  str.replace(re6, "\\1*\\2");
  static QRegularExpression re7("\\(\\)");
  str.replace(re7, "(0)");
  static QRegularExpression re8("\\(\\*|\\(\\/|\\(\\+|\\(\\%|\\(\\^");
  str.replace(re8, "(");
  ui->vvodnaya_stroka->setText(str);
}

void View::calculation() {
  QString qstr = ui->vvodnaya_stroka->text();
  double num = ui->doubleSpinBox_X->value();
  std::string str = qstr.toStdString();
  double result = 0;
  if (controller_->check_brackets(str)) {
    ui->result->setText("error ( != ) or close bracket first");
  } else {
    result = controller_->start_calculate(str, num);
    ui->result->setText(QString::number(result));
  }
}

void View::graphic() {
  ui->widget->clearGraphs();
  double xMin = 0, xMax = 0, yMin = 0, yMax = 0, h = 0, X = 0, tmp = 0;
  QVector<double> x, y;
  xMin = ui->doubleSpinBox_X1->value();
  xMax = ui->doubleSpinBox_X2->value();
  yMin = ui->doubleSpinBox_Y1->value();
  yMax = ui->doubleSpinBox_Y2->value();
  QString qstr = ui->vvodnaya_stroka->text();
  std::string str = qstr.toStdString();
  if (controller_->check_brackets(str)) {
    ui->result->setText("error ( != ) or close bracket first");
  } else {
    if (xMin > xMax) {
      tmp = xMin;
      xMin = xMax;
      xMax = tmp;
    }
    if (yMin > yMax) {
      tmp = yMin;
      yMin = yMax;
      yMax = tmp;
    }
    h = (xMax - xMin) / 1000;
    ui->widget->xAxis->setRange(xMin, xMax);
    ui->widget->yAxis->setRange(yMin, yMax);
    X = xMin;
    for (int i = 0; i < 1000; X += h, i++) {
      x.push_back(X);
      double Y = controller_->start_calculate(str, X);
      y.push_back(Y);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  }
}

void View::credit_clicked() {
  ui->listWidget->clear();
  std::vector<double> data(4);
  data.at(0) = ui->doubleSpinBox_cs->value();
  if (ui->comboBoxYM->currentText() == "Лет") {
    data.at(1) = ui->spinBox_ct->value() * 12;
  } else {
    data.at(1) = ui->spinBox_ct->value();
  }
  if (ui->comboBoxType->currentText() == "Аннуитетный") {
    data.at(2) = 1;
  } else {
    data.at(2) = 2;
  }
  data.at(3) = ui->doubleSpinBox_r->value();
  data = controller_->start_calc_credit(data);
  if (ui->comboBoxType->currentText() == "Аннуитетный") {
    ui->lineEditItog->setText(QString::number(data.at(0), 'g', 12));
    ui->lineEditPereplata->setText(QString::number(data.at(1), 'g', 12));
    ui->listWidget->addItem(QString::number(data.at(2), 'g', 12));
  } else {
    ui->lineEditItog->setText(QString::number(data.at(0), 'g', 12));
    ui->lineEditPereplata->setText(QString::number(data.at(1), 'g', 12));
    for (unsigned int i = 2; i < data.size() - 1; i++) {
      ui->listWidget->addItem(QString::number(data.at(i), 'g', 12));
    }
  }
}
