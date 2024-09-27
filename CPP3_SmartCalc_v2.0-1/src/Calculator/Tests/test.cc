#include <gtest/gtest.h>

#include "../Model/model.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(Calc, sum) {
  s21::Model model;
  double res = 12 + 13;
  model.calc("12+13", 0);
  EXPECT_EQ(model.GetResult(), res);
}

TEST(Calc, sub) {
  s21::Model model;
  double res = 123.123 - 253.4324;
  model.calc("123.123-253.4324", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, mul) {
  s21::Model model;
  double res = 123.123 * 253.4324;
  model.calc("123.123*253.4324", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, div) {
  s21::Model model;
  double res = 417298.123 / 378;
  model.calc("417298.123/378", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, pow) {
  s21::Model model;
  double res = pow(12.32, 3.45);
  model.calc("12.32^3.45", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, mod) {
  s21::Model model;
  double res = fmod(123, 34);
  model.calc("123%34", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, cos) {
  s21::Model model;
  double res = cos(0.5);
  model.calc("cos(0.5)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, sin) {
  s21::Model model;
  double res = sin(0.312);
  model.calc("sin(0.312)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, tan) {
  s21::Model model;
  double res = tan(0.8);
  model.calc("tan(0.8)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, acos) {
  s21::Model model;
  double res = acos(0.1);
  model.calc("acos(0.1)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, asin) {
  s21::Model model;
  double res = asin(0.4);
  model.calc("asin(0.4)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, atan) {
  s21::Model model;
  double res = atan(0.8);
  model.calc("atan(0.8)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, ln) {
  s21::Model model;
  double res = log(123.123);
  model.calc("ln(123.123)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}
TEST(Calc, log) {
  s21::Model model;
  double res = log10(78.12);
  model.calc("log(78.12)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, sqrt) {
  s21::Model model;
  double res = sqrt(144);
  model.calc("sqrt(144)", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, str1) {
  s21::Model model;
  std::string str = "sin(x)+cos(x)-ln(x)+log(x)";
  model.calc(str, 5);
  ASSERT_NEAR(model.GetResult(), -1.5857299973, 1e-7);
}

TEST(Calc, str2) {
  double res = sin(sin(sin(0.3)));
  s21::Model model;
  model.calc("sin(sin(sin(0.3)))", 0);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, str3) {
  double res = 3 + 2;
  s21::Model model;
  model.calc("3+x", 2);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(Calc, str4) {
  double res = log(10) + sin(0.3) - pow(1.2, 2);
  s21::Model model;
  model.calc("ln(x)+sin(0.3)-1.2^2", 10);
  ASSERT_NEAR(model.GetResult(), res, 1e-7);
}

TEST(ModelTest, test5) {
  s21::Model model;
  std::string str = "sin(x)+cos(x)-ln(x)+log(x)";
  model.calc(str, 5);
  ASSERT_NEAR(model.GetResult(), -1.5857299973, 1e-7);
}

TEST(Model, test_brackets1) {
  s21::Model model;
  std::string str = "sqrt(x)+)(x^1.5";
  int st = model.count_brackets(str);
  ASSERT_EQ(st, 1);
}

TEST(Model, test_brackets2) {
  s21::Model model;
  std::string str = "sqrt(x)+(x^1.5)";
  int st = model.count_brackets(str);
  ASSERT_EQ(st, 0);
}

TEST(Model, test_brackets3) {
  s21::Model model;
  std::string str = ")(x)+x^1.5";
  int st = model.count_brackets(str);
  ASSERT_EQ(st, 1);
}

TEST(ModelTest, CreditTest1) {
  std::vector<double> data{10000, 10, 1, 10};
  s21::Model model;
  model.calc_credit(data);
  std::vector<double> res = model.GetCredit();

  EXPECT_EQ(res.at(0), 10464);
  EXPECT_EQ(res.at(1), 464);
  EXPECT_EQ(res.at(2), 1046.4);
}

TEST(ModelTest, CreditTest2) {
  std::vector<double> data{10000, 3, 2, 10};
  s21::Model model;
  model.calc_credit(data);
  std::vector<double> res = model.GetCredit();

  ASSERT_NEAR(res.at(0), 10168.03, 1e-2);
  ASSERT_NEAR(res.at(1), 168.03, 1e-2);
  ASSERT_NEAR(res.at(2), 3418.26, 1e-2);
  ASSERT_NEAR(res.at(3), 3388.13, 1e-2);
  ASSERT_NEAR(res.at(4), 3361.64, 1e-2);
}