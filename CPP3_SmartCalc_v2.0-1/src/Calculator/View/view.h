#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QRegularExpression>
#include <QVector>

#include "../Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;
  Controller *controller_;

  void init_slots();
 private slots:
  void number_clicked();
  void op_clicked();
  void d_clicked();
  void ac_clicked();
  void bs_clicked();
  void graphic();
  void credit_clicked();

  void validate();
  void calculation();
};
}  // namespace s21
#endif  // VIEW_H
