#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  // operators
  S21Matrix& operator+(const S21Matrix& other);
  S21Matrix& operator-(const S21Matrix& other);
  S21Matrix& operator*(const S21Matrix& other);
  friend S21Matrix& operator*(const double num, S21Matrix&);
  friend S21Matrix& operator*(S21Matrix&, const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num);
  double& operator()(const int i, const int j);
  double operator()(const int i, const int j) const;

  // assists
  void PrintMatrix();
  void InitMatrix();

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix = nullptr;

  void MemoryAllocate();
  void MemoryFree();
  double DMDeter() const;
  S21Matrix MinorMatrix(int rows, int cols) const;
};