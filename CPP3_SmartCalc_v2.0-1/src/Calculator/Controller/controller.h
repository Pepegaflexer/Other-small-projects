#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model *m);
  ~Controller();

  double start_calculate(std::string str, double num);
  int check_brackets(std::string str);
  std::vector<double> start_calc_credit(std::vector<double> &data);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CONTROLLER_H
