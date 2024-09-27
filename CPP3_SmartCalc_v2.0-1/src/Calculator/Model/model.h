#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>

namespace s21 {
class Model {
 public:
  Model();
  ~Model();

  enum Operator {
    END = -1,
    NUM,
    X,
    OPB,
    CLB,
    SUM,
    SUB,
    MUL,
    MOD,
    DIV,
    COS,
    SIN,
    TAN,
    ACOS,
    ASIN,
    ATAN,
    LN,
    LOG,
    SQRT,
    POW,
    UN_MINUS
  };

  void SetResult(double result);
  double GetResult() const;
  std::vector<double> GetCredit() const;

  void calc(std::string str, double num);
  int count_brackets(std::string str);
  void calc_credit(std::vector<double>& data);

 private:
  class Node {
   public:
    Node() : value_(0), opr_(-1){};
    Node(double value, char opr) : value_(value), opr_(opr) {}
    double GetValue() const { return value_; }
    void SetValue(const double& value) { value_ = value; }
    int GetOperator() const { return opr_; }
    void SetOperator(const int& opr) { opr_ = opr; }

   private:
    double value_;
    int opr_;
  };

  double result_;
  std::list<Node> polska_;
  std::vector<double> cred_res_;

 private:
  void str_to_pol(std::string str);
  int check_opr(std::string str);
  int change_iterator(int opr);
  int priority(int opr);
  void change_x(double num);
  void calculate_pol();
};
}  // end of namespace s21

#endif  // MODEL_H
