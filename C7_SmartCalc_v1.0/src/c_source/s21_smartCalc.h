#ifndef SRC_C_SOURCE_S21_SMARTCALC_H
#define SRC_C_SOURCE_S21_SMARTCALC_H

#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// l=ln c=cos s=sin g=log t=tan m=mod
// o=acos i=asin q=sqrt a=atan

typedef struct node {
  double value;
  char opr;
  struct node *next;
} node;

typedef enum type_opr {
  END = -1,
  NUM,
  X,
  OPB,
  CLB,
  SUM,
  SUB,
  MUL,
  DIV,
  MOD,
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
} type_opr;

void push(node **head, double data, type_opr oper);
double pop(node **head);
void deleteList(node **head);
void reverseList(node **src, node **dst);
void printLinkedList(const node *head);
const char *odnosimvolniye(node **start, const char *format, char *buff,
                           int *buffCount, int *flag, char *stash,
                           double xValue);
void trehsimvolniye(char *buff, int *flag, char *stash);
void chetirehsimvolniye(char *buff, int *flag, char *stash);
void pushInStash(char *stash, char buff);
void popFromStash(node **start, char *stash);
int perviye(char simbol);
int vtoriye(char simbol);
int tretiye(char simbol);
double calculate(node **start, int *errorSqrt);
void pushForCalculate(double tmp[], int *tmpCounter, double value);
double popForCalculate(double tmp[], int *tmpCounter);
double startCalculate(const char *str, double xValue, int *error);

#ifdef __cplusplus
}
#endif

#endif  // SRC_C_SOURCE_S21_SMARTCALC_H