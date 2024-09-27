#include "s21_matrix_oop.h"

// base constr
S21Matrix ::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  MemoryAllocate();
}

// constr with args
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Error incorrect meaning");
  } else {
    rows_ = rows;
    cols_ = cols;
    MemoryAllocate();
  }
}

// copy
S21Matrix ::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryAllocate();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix[i][j] = other.matrix[i][j];
    }
  }
}

// transfer
S21Matrix ::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix = other.matrix;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix = nullptr;
}
// destr
S21Matrix ::~S21Matrix() { MemoryFree(); }

// getter
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

// setter
void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Error incorrect meaning");
  } else if (rows != rows_) {
    S21Matrix tmp_matrix(rows, cols_);
    for (int i = 0; i < rows_ && i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp_matrix.matrix[i][j] = matrix[i][j];
      }
    }
    *this = std::move(tmp_matrix);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Error incorrect meaning");
  } else if (cols != cols_) {
    S21Matrix tmp_matrix(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_ && j < cols; j++) {
        tmp_matrix.matrix[i][j] = matrix[i][j];
      }
    }
    *this = std::move(tmp_matrix);
  }
}

// ==
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix[i][j] - other.matrix[i][j]) > 01e-7) {
          res = false;
        }
      }
    }
  }
  return res;
}

// summ
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Error: different sizes of matrix");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix[i][j] += other.matrix[i][j];
      }
    }
  }
}

// minus

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Error: different sizes of matrix");
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix[i][j] -= other.matrix[i][j];
    }
  }
}

// matrix * number
void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix[i][j] *= num;
    }
  }
}

// atrix * matrix
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ != other.cols_ || cols_ != other.rows_)
    throw std::invalid_argument("Error: different sizes of matrix");
  S21Matrix Mul_matrix(rows_, other.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      for (auto k = 0; k < other.rows_; k++) {
        Mul_matrix.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
      }
    }
  }
  *this = std::move(Mul_matrix);
}

// rows = cols cols = rows
S21Matrix S21Matrix ::Transpose() const {
  S21Matrix transponse(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      transponse.matrix[i][j] = matrix[j][i];
    }
  }
  return transponse;
}

S21Matrix S21Matrix ::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: wrong matrix sizes");
  }
  S21Matrix Calc_Complements(rows_, cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      S21Matrix Minor_matrix = this->MinorMatrix(i + 1, j + 1);
      Calc_Complements.matrix[i][j] =
          Minor_matrix.Determinant() * pow(-1, (i + j));
    }
  }
  return Calc_Complements;
}

// Determinant
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Error: wrong matrix sizes");
  }
  double res = 0;
  if (rows_ == 1) {
    res = matrix[0][0];
  } else {
    double tmp = 0;
    int sign = 1;
    for (auto i = 0; i < cols_; i++) {
      S21Matrix minor = this->MinorMatrix(1, i + 1);
      if (minor.rows_ == 2) {
        tmp = minor.DMDeter();
      } else {
        tmp = minor.Determinant();
      }
      res += matrix[0][i] * tmp * sign;
      sign *= -1;
    }
  }
  return res;
}

S21Matrix S21Matrix ::InverseMatrix() const {
  double deter = 0;
  deter = this->Determinant();
  if (fabs(deter - 0) < 01e-7) {
    throw std::invalid_argument("Determinant is null");
  }
  S21Matrix Inverse_Matrix = this->CalcComplements();
  Inverse_Matrix = Inverse_Matrix.Transpose();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < rows_; j++) {
      Inverse_Matrix.matrix[i][j] = Inverse_Matrix.matrix[i][j] * (1.0 / deter);
    }
  }
  return Inverse_Matrix;
}

// summatrix
S21Matrix& S21Matrix ::operator+(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

// submatrix
S21Matrix& S21Matrix ::operator-(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

//
S21Matrix& S21Matrix ::operator*(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& operator*(const double num, S21Matrix& M) {
  M.MulNumber(num);
  return M;
}

S21Matrix& operator*(S21Matrix& M, const double num) {
  M.MulNumber(num);
  return M;
}

// EqMatrix
bool S21Matrix ::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

// copy
S21Matrix& S21Matrix ::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->MemoryFree();
    cols_ = other.cols_;
    rows_ = other.rows_;
    MemoryAllocate();
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        matrix[i][j] = other.matrix[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix ::operator=(S21Matrix& other) {
  if (this != &other) {
    this->MemoryFree();
    cols_ = other.cols_;
    rows_ = other.rows_;
    matrix = other.matrix;
    other.matrix = nullptr;
  }
  return *this;
}

// SumMatrix
S21Matrix& S21Matrix ::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

// SubMatrix
S21Matrix& S21Matrix ::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix ::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

// MulNumber
S21Matrix& S21Matrix ::operator*=(const double& num) {
  MulNumber(num);
  return *this;
}

//Индексация по элементам матрицы(строки, столбцы)
double& S21Matrix::operator()(const int i, const int j) {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::out_of_range("Error, index is out of range");
  return matrix[i][j];
}

double S21Matrix::operator()(const int i, const int j) const {
  if (i > rows_ || i < 0 || j > cols_ || j < 0)
    throw std::out_of_range("Error, index is out of range");
  return matrix[i][j];
}

// allocate
void S21Matrix::MemoryAllocate() {
  matrix = new double*[rows_]();
  matrix[0] = new double[rows_ * cols_]();
  for (auto i = 1; i != rows_; i++) {
    matrix[i] = matrix[i - 1] + cols_;
  }
}

// delete
void S21Matrix::MemoryFree() {
  if (matrix && matrix[0]) {
    delete[] matrix[0];
    delete[] matrix;
    rows_ = 0;
    cols_ = 0;
  }
}

// assists
void S21Matrix::PrintMatrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      std ::cout << matrix[i][j] << " ";
    }
    std ::cout << std ::endl;
  }
  std ::cout << std ::endl;
}

void S21Matrix::InitMatrix() {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix[i][j] = i + j;
    }
  }
}

// determinant for double matrix
double S21Matrix::DMDeter() const {
  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// minor matrix
S21Matrix S21Matrix::MinorMatrix(int rows, int cols) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  rows--;
  cols--;
  int rowsMin = 0;
  for (int i = 0; i < rows_; i++) {
    int colsMin = 0;
    for (auto j = 0; j < cols_; j++) {
      if (i != rows && j != cols) {
        minor.matrix[rowsMin][colsMin] = this->matrix[i][j];
        colsMin++;
      }
    }
    if (i != rows) rowsMin++;
  }
  return minor;
}