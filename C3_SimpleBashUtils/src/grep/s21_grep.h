#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char eArg[2048];
  char fArg[2048];
} opt;

void parcer(int argc, char *argv[], opt *options);
void reader(int argc, char *argv[], opt *options);
void makeString(char *argv[], opt *options, char *summaryLine);
void flagOseach(char *summaryLine, char *line, int counterString, opt *options,
                int nameFlag, char *argv[]);

#endif  // SRC_GREP_S21_GREP_H_