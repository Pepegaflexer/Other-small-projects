#include "model.h"

s21::Model::Model() : result_(0) {}

s21::Model::~Model(){};

double s21::Model::GetResult() const { return result_; };

void s21::Model::SetResult(double result) { result_ = result; };

std::vector<double> s21::Model::GetCredit() const { return cred_res_; };

/**
 * Calculate the model with the given string and number.
 *
 * @param str the string input
 * @param num the number input
 *
 * @return void
 *
 */
void s21::Model::calc(std::string str, double num) {
  str_to_pol(str);
  change_x(num);
  calculate_pol();
  polska_.clear();
}

/**
 * Counts the number of brackets in the given string and returns 1 if there is a
 * closing bracket without a corresponding opening bracket, 0 otherwise.
 *
 * @param str the input string to count brackets in
 *
 * @return 1 if there is a closing bracket without a corresponding opening
 * bracket, 0 otherwise
 */
int s21::Model::count_brackets(std::string str) {
  int count = 0;
  int error = 0;
  for (size_t i = 0; i < str.size(); i++) {
    if (str.at(i) == '(') {
      count++;
    } else if (str.at(i) == ')' && count > 0) {
      count--;
    } else if (str.at(i) == ')' && count == 0) {
      error = 1;
    }
  }
  return error;
}

/**
 * Calculate credit based on the input data.
 *
 * @param data vector containing credit data: [creditSum, creditTerm,
 * paymentType, interestRate]
 *
 */
void s21::Model::calc_credit(std::vector<double> &data) {
  cred_res_.clear();
  double creditSum = data.at(0);
  double creditTerm = data.at(1);
  double interestRate = data.at(3);
  if (data.at(2) == 1) {
    cred_res_.resize(3, 0);
    double mes = interestRate / 12 / 100;
    double kef =
        (mes * pow(1 + mes, creditTerm)) / (pow(1 + mes, creditTerm) - 1);
    cred_res_.at(2) = round((creditSum * kef) * 100) / 100;
    cred_res_.at(0) = round((cred_res_.at(2) * creditTerm) * 100) / 100;
    cred_res_.at(1) = cred_res_.at(0) - creditSum;
  }
  if (data.at(2) == 2) {
    cred_res_.resize(creditTerm + 3, 0);
    double tmp = creditSum / creditTerm, ostatok = creditSum;
    interestRate = interestRate / 100;
    for (int i = 1; i <= creditTerm; i++) {
      if (i % 2 == 0) {
        cred_res_.at(i + 1) = tmp + (ostatok * interestRate * 30 / 365);
      } else if (i % 2 == 1) {
        cred_res_.at(i + 1) = tmp + (ostatok * interestRate * 31 / 365);
      }
      cred_res_.at(i + 1) = round(cred_res_.at(i + 1) * 100) / 100;
      ostatok = ostatok - tmp;

      cred_res_.at(0) =
          round((cred_res_.at(0) + cred_res_.at(i + 1)) * 100) / 100;
    }
    cred_res_.at(1) = cred_res_.at(0) - creditSum;
  }
}

/**
 * Convert a string to a postfix notation and store the result in the polska_
 * vector.
 *
 * @param str the input string to be converted
 *
 * @return void
 */
void s21::Model::str_to_pol(std::string str) {
  const char *cstr = str.c_str();
  int opr = 0;
  char *tmp = (char *)cstr;
  int s_count = 0;
  int stack[100] = {0};
  while ((unsigned int)(tmp - cstr) < strlen(cstr)) {
    opr = check_opr(tmp);
    tmp += change_iterator(opr);

    if (opr == NUM) {
      double numr = strtod(tmp, &tmp);
      polska_.push_back(Node(numr, NUM));
    } else if (opr == X) {
      polska_.push_back(Node(0, X));
      tmp++;
    } else if (opr == OPB) {
      stack[s_count++] = OPB;
      tmp++;
    } else if (opr == CLB) {
      while (s_count > 0 && stack[s_count - 1] != OPB) {
        polska_.push_back(Node(0, stack[s_count - 1]));
        stack[s_count - 1] = 0;
        s_count--;
      }
      stack[s_count - 1] = 0;
      s_count--;
      tmp++;
    } else {
      while (s_count > 0 && priority(stack[s_count - 1]) >= priority(opr)) {
        polska_.push_back(Node(0, stack[s_count - 1]));
        stack[s_count - 1] = 0;
        s_count--;
      }
      stack[s_count++] = opr;
      tmp++;
    }
  }
  while (s_count > 0) {
    polska_.push_back(Node(0, stack[s_count - 1]));
    stack[s_count - 1] = 0;
    s_count--;
  }
}

/**
 * Function to check the operation type based on the input substring.
 *
 * @param substr the input substring to be checked
 *
 * @return the operation type as an integer value
 *
 */
int s21::Model::check_opr(std::string substr) {
  int res = END;

  if (substr.at(0) >= '0' && substr.at(0) <= '9') {
    res = NUM;
  } else if (substr.at(0) == '+') {
    res = SUM;
  } else if (substr.at(0) == '-') {
    if (substr[-1] == '(') {
      res = UN_MINUS;
    } else {
      res = SUB;
    }
  } else if (substr.at(0) == '*') {
    res = MUL;
  } else if (substr.at(0) == '/') {
    res = DIV;
  } else if (substr.at(0) == '^') {
    res = POW;
  } else if (substr.at(0) == '%') {
    res = MOD;
  } else if (substr.at(0) == 's' && substr.at(1) == 'q') {
    res = SQRT;
  } else if (substr.at(0) == 'l' && substr.at(1) == 'o') {
    res = LOG;
  } else if (substr.at(0) == 'l' && substr.at(1) == 'n') {
    res = LN;
  } else if (substr.at(0) == 'a' && substr.at(1) == 't') {
    res = ATAN;
  } else if (substr.at(0) == 'a' && substr.at(1) == 's') {
    res = ASIN;
  } else if (substr.at(0) == 'a' && substr.at(1) == 'c') {
    res = ACOS;
  } else if (substr.at(0) == 't' && substr.at(1) == 'a') {
    res = TAN;
  } else if (substr.at(0) == 's' && substr.at(1) == 'i') {
    res = SIN;
  } else if (substr.at(0) == 'c' && substr.at(1) == 'o') {
    res = COS;
  } else if (substr.at(0) == 'x') {
    res = X;
  } else if (substr.at(0) == ')') {
    res = CLB;
  } else if (substr.at(0) == '(') {
    res = OPB;
  }
  return res;
}

/**
 * Change the iterator based on the given operation.
 *
 * @param opr the operation to be performed
 *
 * @return the updated iterator value
 */
int s21::Model::change_iterator(int opr) {
  int res = 0;
  if (opr == COS || opr == SIN || opr == TAN || opr == LOG) {
    res = 2;
  } else if (opr == ACOS || opr == ASIN || opr == ATAN || opr == SQRT) {
    res = 3;
  } else if (opr == LN) {
    res = 1;
  }
  return res;
}

/**
 * Priority of the given operation.
 *
 * @param opr the operation code
 *
 * @return the priority of the operation
 */
int s21::Model::priority(int opr) {
  int res = 0;
  if (opr == OPB) {
    res = 0;
  } else if (opr == SUM || opr == SUB) {
    res = 1;
  } else if (opr == MUL || opr == DIV) {
    res = 2;
  } else if (opr == POW) {
    res = 3;
  } else if (opr == COS || opr == SIN || opr == TAN || opr == ACOS) {
    res = 4;
  } else if (opr == ASIN || opr == ATAN || opr == LN || opr == LOG ||
             opr == SQRT || opr == UN_MINUS) {
    res = 4;
  }
  return res;
}

void s21::Model::change_x(double num) {
  for (auto &i : polska_) {
    if (i.GetOperator() == X) {
      i.SetValue(num);
      i.SetOperator(NUM);
    }
  }
}
/**
 * Calculate the result of a given expression in reverse Polish notation.
 *
 * @param None
 *
 * @return None
 *
 * @throws None
 */
void s21::Model::calculate_pol() {
  int opr = 0;
  int s_count = 0;
  double stack[20] = {0};
  for (auto const &i : polska_) {
    opr = i.GetOperator();
    if (opr == NUM) {
      stack[s_count++] = i.GetValue();
    } else if (opr == SUM) {
      stack[s_count - 2] += stack[s_count - 1];
      s_count--;
    } else if (opr == SUB) {
      stack[s_count - 2] -= stack[s_count - 1];
      s_count--;
    } else if (opr == MUL) {
      stack[s_count - 2] *= stack[s_count - 1];
      s_count--;
    } else if (opr == DIV) {
      stack[s_count - 2] /= stack[s_count - 1];
      s_count--;
    } else if (opr == UN_MINUS) {
      stack[s_count - 1] *= -1;
    } else if (opr == MOD) {
      int left = stack[s_count - 2];
      int right = stack[s_count - 1];
      left %= right;
      stack[s_count - 2] = left;
      s_count--;
    } else if (opr == COS) {
      stack[s_count - 1] = cos(stack[s_count - 1]);
    } else if (opr == SIN) {
      stack[s_count - 1] = sin(stack[s_count - 1]);
    } else if (opr == TAN) {
      stack[s_count - 1] = tan(stack[s_count - 1]);
    } else if (opr == ACOS) {
      stack[s_count - 1] = acos(stack[s_count - 1]);
    } else if (opr == ASIN) {
      stack[s_count - 1] = asin(stack[s_count - 1]);
    } else if (opr == ATAN) {
      stack[s_count - 1] = atan(stack[s_count - 1]);
    } else if (opr == LN) {
      stack[s_count - 1] = log(stack[s_count - 1]);
    } else if (opr == LOG) {
      stack[s_count - 1] = log10(stack[s_count - 1]);
    } else if (opr == SQRT) {
      stack[s_count - 1] = sqrt(stack[s_count - 1]);
    } else if (opr == POW) {
      stack[s_count - 2] = pow(stack[s_count - 2], stack[s_count - 1]);
      s_count--;
    }
  }
  SetResult(stack[s_count - 1]);
}