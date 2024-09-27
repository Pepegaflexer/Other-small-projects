#include "mainwindow.h"

#include <QRegularExpression>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  ui->widget->setBackground(plotGradient);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_natlog, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_koren, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_ac, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_backSpace, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->vvodnaya_stroka, SIGNAL(textChanged(QString)), this,
          SLOT(validate()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(calculation()));
  connect(ui->pushButton_GR, SIGNAL(clicked()), this, SLOT(graphic()));
  connect(ui->pushButtonCR, SIGNAL(clicked()), this, SLOT(calcCredit()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->vvodnaya_stroka->text() == "0" && button->text() != "." &&
      button->text() != "AC") {
    ui->vvodnaya_stroka->setText(button->text());
  } else if (button->text() == "AC") {
    ui->vvodnaya_stroka->setText("0");
  } else if (button->text() == "<-" && ui->vvodnaya_stroka->text() != "0") {
    QString label_temp = (ui->vvodnaya_stroka->text());
    label_temp.chop(1);
    ui->vvodnaya_stroka->setText(label_temp);
  } else {
    QString label_result = (ui->vvodnaya_stroka->text() + button->text());
    ui->vvodnaya_stroka->setText(label_result);
  }
}

void MainWindow::calculation() {
  int error = 0;
  QString x = ui->lineEditX->text();
  QString temp = ui->vvodnaya_stroka->text();
  QByteArray ba = temp.toLocal8Bit();
  const char *str = ba.data();
  double xValue = x.toDouble();
  double res = startCalculate(str, xValue, &error);
  if (error == 1) {
    ui->result->setText("error ( != )");
  } else if (error == 2) {
    ui->result->setText("error отриц. значение под корнем");
  } else {
    QString resStr = QString::number(res, 'g', 15);
    ui->result->setText(resStr);
  }
}

void MainWindow::validate() {
  QString temp_string = ui->vvodnaya_stroka->text();
  temp_string.replace("..", ".");
  static QRegularExpression re1("(\\D)\\.");
  temp_string.replace(re1, "\\10.");

  ui->vvodnaya_stroka->setText(temp_string);
}

void MainWindow::graphic() {
  int error = 0;
  ui->widget->clearGraphs();
  double xMin = 0, xMax = 0, yMin = 0, yMax = 0, h = 0, X = 0, tmp = 0;
  QVector<double> x, y;
  xMin = ui->lineEditX1->text().toDouble();
  xMax = ui->lineEditX2->text().toDouble();
  yMin = ui->lineEditY1->text().toDouble();
  yMax = ui->lineEditY2->text().toDouble();
  QString temp = ui->vvodnaya_stroka->text();
  QByteArray ba = temp.toLocal8Bit();
  const char *str = ba.data();
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
    double Y = startCalculate(str, X, &error);
    y.push_back(Y);
  }
  if (error == 1) {
    ui->result->setText("error ( != )");
  } else {
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  }
}

void MainWindow::calcCredit() {
  ui->listWidget->clear();
  double creditSum = 0., creditTerm = 0., interestRate = 0., res = 0.;
  creditSum = ui->lineEditCS->text().toDouble();
  creditTerm = ui->lineEditCT->text().toDouble();
  interestRate = ui->lineEditIR->text().toDouble();
  if (ui->comboBoxYM->currentText() == "Лет") {
    creditTerm *= 12;
  }
  if (ui->comboBoxType->currentText() == "Аннуитетный") {
    double mes = interestRate / 12 / 100;
    double kef =
        (mes * pow(1 + mes, creditTerm)) / (pow(1 + mes, creditTerm) - 1);
    res = round((creditSum * kef) * 100) / 100;
    ui->listWidget->addItem(QString::number(res, 'g', 12));
    res = round((res * creditTerm) * 100) / 100;
    QString temp = QString::number(res, 'g', 12);
    ui->lineEditItog->setText(temp);
    res = round((res - creditSum) * 100) / 100;
    temp = QString::number(res, 'g', 12);
    ui->lineEditPereplata->setText(temp);
  }
  if (ui->comboBoxType->currentText() == "Дифференцированный") {
    res = 0;
    double tmp = creditSum / creditTerm, plateg = 0, ostatok = creditSum;
    interestRate = interestRate / 100;
    for (int i = 1; i <= creditTerm; i++) {
      if (i % 2 == 0) {
        plateg = tmp + (ostatok * interestRate * 30 / 365);
      } else if (i % 2 == 1) {
        plateg = tmp + (ostatok * interestRate * 31 / 365);
      }
      plateg = round(plateg * 100) / 100;
      ostatok = ostatok - tmp;
      ui->listWidget->addItem(QString::number(plateg, 'g', 12));
      res = res + plateg;
    }
    res = round(res * 100) / 100;
    ui->lineEditItog->setText(QString::number(res, 'g', 12));
    res = res - creditSum;
    ui->lineEditPereplata->setText(QString::number(res, 'g', 12));
  }
}
