#ifndef SRC_GREP_S21_CAT_H_
#define SRC_GREP_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int E;
  int v;
  int T;
} opt;
void parcer(int argc, char *argv[], opt *options);
void reader(int argc, char *argv[], opt *options);

#endif  // SRC_GREP_S21_CAT_H_
