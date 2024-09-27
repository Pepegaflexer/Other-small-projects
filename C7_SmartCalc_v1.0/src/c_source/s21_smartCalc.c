#include "s21_smartCalc.h"

double startCalculate(const char *str, double xValue, int *error) {
  int errorSqrt = 0;
  node *start = NULL;
  const char *format = str;
  char stash[1024] = "\0";
  while (*format != '\0') {
    char buff[1024] = {'\0'};
    int buffCount = 0;
    int flag = 0;
    buff[buffCount++] = *format++;
    format =
        odnosimvolniye(&start, format, buff, &buffCount, &flag, stash, xValue);
    if (flag == 0) {
      buff[buffCount++] = *format++;
      if (!strcmp(buff, "ln")) {
        pushInStash(stash, 'l');
        flag = 1;
      }
      if (flag == 0) {
        buff[buffCount++] = *format++;
        trehsimvolniye(buff, &flag, stash);
      }
      if (flag == 0) {
        buff[buffCount++] = *format++;
        chetirehsimvolniye(buff, &flag, stash);
      }
    }
  }
  while (strlen(stash)) {
    if (stash[strlen(stash) - 1] == '(') {
      *error = 1;
    }
    popFromStash(&start, stash);
  }

  node *reverseStart = NULL;
  reverseList(&start, &reverseStart);
  double res = calculate(&reverseStart, &errorSqrt);
  if (errorSqrt == 1) {
    *error = 2;
  }
  deleteList(&reverseStart);
  deleteList(&start);

  return res;
}

double calculate(node **start, int *errorSqrt) {
  double tmp[100] = {0};
  int tmpCounter = 0;
  double a = 0, b = 0;
  while (*start) {
    if (tmpCounter > 0) {
    }
    switch ((*start)->opr) {
      case NUM:
        pushForCalculate(tmp, &tmpCounter, pop(start));
        break;
      case X:
        pushForCalculate(tmp, &tmpCounter, pop(start));
        break;
      case SUM:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, a + b);
        pop(start);
        break;
      case SUB:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, a - b);
        pop(start);
        break;
      case MUL:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, a * b);
        pop(start);
        break;
      case DIV:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, a / b);
        pop(start);
        break;
      case MOD:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, fmod(a, b));
        pop(start);
        break;
      case COS:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, cos(a));
        pop(start);
        break;
      case SIN:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, sin(a));
        pop(start);
        break;
      case TAN:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, tan(a));
        pop(start);
        break;
      case ACOS:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, acos(a));
        pop(start);
        break;
      case ASIN:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, asin(a));
        pop(start);
        break;
      case ATAN:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, atan(a));
        pop(start);
        break;
      case LN:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, log(a));
        pop(start);
        break;
      case LOG:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, log10(a));
        pop(start);
        break;
      case SQRT:
        a = popForCalculate(tmp, &tmpCounter);
        if (a < 0) {
          *errorSqrt = 1;
        }
        pushForCalculate(tmp, &tmpCounter, sqrt(a));

        pop(start);
        break;
      case POW:
        b = popForCalculate(tmp, &tmpCounter);
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, pow(a, b));
        pop(start);
        break;
      case UN_MINUS:
        a = popForCalculate(tmp, &tmpCounter);
        pushForCalculate(tmp, &tmpCounter, a * (-1));
        pop(start);
        break;
      default:
        break;
    }
  }
  return (tmp[0]);
}

void pushForCalculate(double tmp[], int *tmpCounter, double value) {
  tmp[(*tmpCounter)++] = value;
}

double popForCalculate(double tmp[], int *tmpCounter) {
  double value = 0;
  value = tmp[(*tmpCounter) - 1];
  *tmpCounter = *tmpCounter - 1;
  return value;
}
