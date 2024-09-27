#include "controller.h"

s21::Controller::Controller(Model *m) : model_(m) {}

s21::Controller::~Controller(){};

/**
 * Start the calculation process.
 *
 * @param str the string input for calculation
 * @param num the numeric input for calculation
 *
 * @return the result of the calculation
 */
double s21::Controller::start_calculate(std::string str, double num) {
  model_->calc(str, num);
  return model_->GetResult();
}

/**
 * Checks the brackets in a given string.
 *
 * @param str the string to check the brackets in
 *
 * @return the count of brackets in the string
 *
 */
int s21::Controller::check_brackets(std::string str) {
  return model_->count_brackets(str);
}

std::vector<double> s21::Controller::start_calc_credit(
    std::vector<double> &data) {
  model_->calc_credit(data);
  return model_->GetCredit();
}