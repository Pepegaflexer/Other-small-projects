#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_PI 3.14159265358979323846264338327950288
#define S21_2PI 6.28318530717958647692528676655900576
#define S21_EPS 1e-8
#define S21_EXP 2.71828182845904523536
#define S21_DBL_MAX 1.79769e+308
#define s21_isNan(x) __builtin_isnan(x)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

double rotate_circle(double x);  // function for sin, cos (tan)
long double whole_exp_pow(double base, long exp);  // function for pow
double s21_maxvalue(double x);                     // function for sqrt

#endif  //  SRC_S21_MATH_H_
