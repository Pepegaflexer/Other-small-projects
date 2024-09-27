#include "test.h"
START_TEST(test_sum) {
    int sqrtError = 0;
    double res = 12+13;
    double resCalc = startCalculate("12+13", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_sub) {
    int sqrtError = 0;
    double res = 123.123-253.4324;
    double resCalc = startCalculate("123.123-253.4324", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_mul) {
    int sqrtError = 0;
    double res = 123.123*253.4324;
    double resCalc = startCalculate("123.123*253.4324", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_div) {
    int sqrtError = 0;
    double res = 417298.123/378;
    double resCalc = startCalculate("417298.123/378", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_pow) {
    int sqrtError = 0;
    double res = pow(12.32, 3.45);
    double resCalc = startCalculate("12.32^3.45", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_mod) {
    int sqrtError = 0;
    double res = fmod(534.123,124);
    double resCalc = startCalculate("534.123mod124", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_cos) {
    int sqrtError = 0;
    double res = cos(0.5);
    double resCalc = startCalculate("cos(0.5)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_sin) {
    int sqrtError = 0;
    double res = sin(0.312);
    double resCalc = startCalculate("sin(0.312)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_tan) {
    int sqrtError = 0;
    double res = tan(0.8);
    double resCalc = startCalculate("tan(0.8)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_acos) {
    int sqrtError = 0;
    double res = acos(0.1);
    double resCalc = startCalculate("acos(0.1)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_asin) {
    int sqrtError = 0;
    double res = asin(0.4);
    double resCalc = startCalculate("asin(0.4)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_atan) {
    int sqrtError = 0;
    double res = atan(0.8);
    double resCalc = startCalculate("atan(0.8)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_ln) {
    int sqrtError = 0;
    double res = log(123.123);
    double resCalc = startCalculate("ln(123.123)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_log) {
    int sqrtError = 0;
    double res = log10(78.12);
    double resCalc = startCalculate("log(78.12)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_sqrt) {
    int sqrtError = 0;
    double res = sqrt(144);
    double resCalc = startCalculate("sqrt(144)", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc0) {
    int sqrtError = 0;
    double res = asin(0.5)-123+4.12*pow(cos(0.5),2);
    double resCalc = startCalculate("asin(0.5)-123+4.12*cos(0.5)^2", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc1) {
    int sqrtError = 0;
    double res = fmod(3812,734)*sin(5-4.5+pow(0.3,2));
    double resCalc = startCalculate("3812mod734*sin(5-4.5+0.3^2)", 0, &sqrtError);

    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc2) {
    int sqrtError = 0;
    double resCalc = startCalculate("37.12*((-3) + 4)/asin(3)", 0, &sqrtError);
    ck_assert_double_nan(resCalc);
}
END_TEST

START_TEST(test_calc3) {
    int sqrtError = 0;
    double res = pow(10,(100-25*3.76))+log10(5-pow(sin(3),3));
    double resCalc = startCalculate("10^(100-25*3.76)+log(5-sin(3)^3)", 0, &sqrtError);   // ln(x)+sin(0.3)-1.2^2",
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc4) {
    int sqrtError = 0;
    double res =37.12*(-3)*sin(3) ;
    double resCalc = startCalculate("37.12*(-3)*sin(3)", 0, &sqrtError);
    
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc5) {
    int sqrtError = 0;
    double res =sin(sin(sin(0.3)));
    double resCalc = startCalculate("sin(sin(sin(0.3)))", 0, &sqrtError);
    
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc6) {
    int sqrtError = 0;
    double res =3+2;
    double resCalc = startCalculate("3+x", 2, &sqrtError );

    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc7) {
    int sqrtError = 0;
    double res =3+2;
    double resCalc = startCalculate("3+x", 2, &sqrtError);

    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc8) {
    int sqrtError = 0;
    double res =log(10)+sin(0.3)-pow(1.2,2);
    double resCalc = startCalculate("ln(x)+sin(0.3)-1.2^2", 10, &sqrtError);

    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc9) {
    int sqrtError = 0;
    double res =12-3*(75-90*(1+1*(4-4)));
    double resCalc = startCalculate("12-3*(75-90*(1+1*(4-4)))", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

START_TEST(test_calc10) {
    int sqrtError = 0;
    double res =3*(75-90*(1+1*(4-4)));
    double resCalc = startCalculate("3*(75-90*(1+1*(4-4)))", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST


START_TEST(test_calc11) {
    int sqrtError = 0;
    double res =78*(12+3*(4-2*(33-33)));
    double resCalc = startCalculate("78*(12+3*(4-2*(33-33)))", 0, &sqrtError);
    ck_assert_double_eq(res, resCalc);
}
END_TEST

Suite *test_calc(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_CALC=-\033[0m.");
    tc = tcase_create("add_tc");
    tcase_add_test(tc,test_sum);
    tcase_add_test(tc,test_sub);
    tcase_add_test(tc,test_mul);
    tcase_add_test(tc,test_div);
    tcase_add_test(tc,test_pow);
    tcase_add_test(tc,test_mod);
    tcase_add_test(tc,test_sin);
    tcase_add_test(tc,test_cos);
    tcase_add_test(tc,test_tan);
    tcase_add_test(tc,test_asin);
    tcase_add_test(tc,test_acos);
    tcase_add_test(tc,test_atan);
    tcase_add_test(tc,test_ln);
    tcase_add_test(tc,test_log);
    tcase_add_test(tc,test_sqrt);
    tcase_add_test(tc,test_calc0);
    tcase_add_test(tc,test_calc1);
    tcase_add_test(tc,test_calc2);
    tcase_add_test(tc,test_calc3);
    tcase_add_test(tc,test_calc4);
    tcase_add_test(tc,test_calc5);
    tcase_add_test(tc,test_calc6);
    tcase_add_test(tc,test_calc7);
    tcase_add_test(tc,test_calc8);
    tcase_add_test(tc,test_calc9);
    tcase_add_test(tc,test_calc10);
    tcase_add_test(tc,test_calc11);



  suite_add_tcase(s, tc);

  return s;
}
