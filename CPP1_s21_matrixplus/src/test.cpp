#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(Constructor, Based) {
  S21Matrix test;
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Constructor, Args) {
  S21Matrix test = S21Matrix(2, 4);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 4);
}

TEST(Constructor, WrongArgs) {
  EXPECT_THROW(S21Matrix test(-1, -1), std::invalid_argument);
}

TEST(Constructor, Copy) {
  S21Matrix test = S21Matrix(2, 4);
  test(0, 0) = 3;
  S21Matrix test2 = (test);
  EXPECT_EQ(test2.GetRows(), 2);
  EXPECT_EQ(test2.GetCols(), 4);
  EXPECT_EQ(test2(0, 0), 3);
}

TEST(Constructor, Move) {
  S21Matrix test = S21Matrix(2, 4);
  test(0, 0) = 3;
  S21Matrix test2 = std::move(test);
  EXPECT_EQ(test2.GetRows(), 2);
  EXPECT_EQ(test2.GetCols(), 4);
  EXPECT_EQ(test2(0, 0), 3);
}

TEST(Setter, Rows) {
  S21Matrix test = S21Matrix(2, 2);
  test(0, 0) = 3;
  test(0, 1) = 1;
  test(1, 0) = 2;
  test(1, 1) = -2;
  EXPECT_EQ(test.GetRows(), 2);
  test.SetRows(3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test(1, 1), -2);
  test.SetRows(1);
  test.SetCols(1);
  test.SetRows(2);
  test.SetCols(2);
  EXPECT_EQ(test(1, 1), 0);
}

TEST(Setter, Cols) {
  S21Matrix test = S21Matrix(2, 1);
  test(0, 0) = 3;
  test(1, 0) = 2;
  EXPECT_EQ(test.GetCols(), 1);
  test.SetCols(10);
  EXPECT_EQ(test.GetCols(), 10);
  EXPECT_EQ(test(1, 9), 0);
  EXPECT_EQ(test(0, 0), 3);
}

TEST(Setter, WrongRows) {
  S21Matrix test = S21Matrix(2, 2);
  EXPECT_THROW(test.SetRows(-1), std::invalid_argument);
}

TEST(Setter, WrongCols) {
  S21Matrix test = S21Matrix(2, 1);
  EXPECT_THROW(test.SetCols(0), std::invalid_argument);
}

TEST(Arithmethic, EqMatrix) {
  S21Matrix test1 = S21Matrix();
  S21Matrix test2 = S21Matrix();
  test1.InitMatrix();
  test2.InitMatrix();
  EXPECT_EQ(test1.EqMatrix(test2), true);
  EXPECT_EQ(test2.EqMatrix(test1), true);
  EXPECT_EQ(test1 == test2, true);
  EXPECT_EQ(test2 == test1, true);
  test1(0, 0) = 10;
  EXPECT_EQ(test1.EqMatrix(test2), false);
  EXPECT_EQ(test2.EqMatrix(test1), false);
  EXPECT_EQ(test1 == test2, false);
  EXPECT_EQ(test2 == test1, false);
}

TEST(Arithmethic, SumMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 2);
  test1.InitMatrix();
  test2.InitMatrix();
  test1 += test2;
  EXPECT_EQ(test1(0, 0), 0);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 4);
}

TEST(Arithmethic, WrongSumMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 1);
  test1.InitMatrix();
  test2.InitMatrix();
  EXPECT_THROW(test1 += test2, std::invalid_argument);
}

TEST(Arithmethic, SubMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 2);
  test1.InitMatrix();
  test2.InitMatrix();
  test1 *= 3;
  test1 -= test2;
  EXPECT_EQ(test1(0, 0), 0);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 4);
}

TEST(Arithmethic, WrongSubMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(3, 2);
  EXPECT_THROW(test1 -= test2, std::invalid_argument);
}

TEST(Arithmethic, MulMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 2);
  test1.InitMatrix();
  test2.InitMatrix();
  test1 *= test2;
  EXPECT_EQ(test1(0, 0), 1);
  EXPECT_EQ(test1(1, 0), 2);
  EXPECT_EQ(test1(0, 1), 2);
  EXPECT_EQ(test1(1, 1), 5);
}

TEST(Arithmethic, WrongMulMatrix) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 32);
  EXPECT_THROW(test1 * test2, std::invalid_argument);
}

TEST(Arithmethic, MulNum) {
  S21Matrix test1 = S21Matrix(2, 2);
  S21Matrix test2 = S21Matrix(2, 2);
  test1.InitMatrix();
  test2.InitMatrix();
  S21Matrix test3 = 3 * test1;
  S21Matrix test4 = test2 * 3;
  EXPECT_EQ(test3(0, 0), 0);
  EXPECT_EQ(test3(1, 0), 3);
  EXPECT_EQ(test3(0, 1), 3);
  EXPECT_EQ(test3(1, 1), 6);
  EXPECT_EQ(test4(0, 0), 0);
  EXPECT_EQ(test4(1, 0), 3);
  EXPECT_EQ(test4(0, 1), 3);
  EXPECT_EQ(test4(1, 1), 6);
}

TEST(Actions, Transpose) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  test1 = test1.Transpose();
  EXPECT_EQ(test1(0, 0), 3);
  EXPECT_EQ(test1(0, 1), 20);
  EXPECT_EQ(test1(1, 0), 1);
  EXPECT_EQ(test1(1, 1), -2);
}

TEST(Actions, Complements) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  test1 = test1.CalcComplements();
  EXPECT_EQ(test1(0, 0), -2);
  EXPECT_EQ(test1(0, 1), -20);
  EXPECT_EQ(test1(1, 0), -1);
  EXPECT_EQ(test1(1, 1), 3);
}

TEST(Actions, WrongComplements) {
  S21Matrix test1 = S21Matrix(2, 3);
  EXPECT_THROW(test1.CalcComplements(), std::invalid_argument);
}

TEST(Actions, DDeterminant) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 20;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), -26);
  test1(0, 0) = 2;
  test1(0, 1) = 1;
  test1(1, 0) = 4;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), -8);
  test1(0, 0) = 2;
  test1(0, 1) = -5;
  test1(1, 0) = 1;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), 1);
  test1(0, 0) = 3;
  test1(0, 1) = -1;
  test1(1, 0) = 7;
  test1(1, 1) = -2;
  EXPECT_EQ(test1.Determinant(), 1);
}

TEST(Actions, TDeterminant) {
  S21Matrix test1 = S21Matrix(3, 3);
  test1(0, 0) = 2;
  test1(0, 1) = 5;
  test1(0, 2) = 7;
  test1(1, 0) = 6;
  test1(1, 1) = 3;
  test1(1, 2) = 4;
  test1(2, 0) = 5;
  test1(2, 1) = -2;
  test1(2, 2) = -3;
  EXPECT_EQ(test1.Determinant(), -1);
}

TEST(Actions, WrongDeterminant) {
  S21Matrix test = S21Matrix(3, 100);
  EXPECT_THROW(test.Determinant(), std::invalid_argument);
}

TEST(Actions, Inverse) {
  S21Matrix test1 = S21Matrix(2, 2);
  test1(0, 0) = 3;
  test1(0, 1) = 1;
  test1(1, 0) = 2;
  test1(1, 1) = -2;
  test1 = test1.InverseMatrix();
  EXPECT_EQ(test1(0, 0), 0.25);
  EXPECT_EQ(test1(0, 1), 0.125);
  EXPECT_EQ(test1(1, 0), 0.25);
  EXPECT_EQ(test1(1, 1), -0.375);
}

TEST(Actions, Inverse2) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 2;
  m1(0, 1) = 5;
  m1(0, 2) = 7;
  m1(1, 0) = 6;
  m1(1, 1) = 3;
  m1(1, 2) = 4;
  m1(2, 0) = 5;
  m1(2, 1) = -2;
  m1(2, 2) = -3;
  S21Matrix test(3, 3);
  test(0, 0) = 1;
  test(0, 1) = -1;
  test(0, 2) = 1;
  test(1, 0) = -38;
  test(1, 1) = 41;
  test(1, 2) = -34;
  test(2, 0) = 27;
  test(2, 1) = -29;
  test(2, 2) = 24;
  m2 = m1.InverseMatrix();
  ASSERT_EQ(1, m2 == test);
}

TEST(Actions, OOR) {
  S21Matrix test = S21Matrix(4, 4);
  EXPECT_THROW(test(-12, 1) = 1, std::out_of_range);
  EXPECT_THROW(test(1, 123) = 14, std::out_of_range);
}
