#include "s21_cat.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  if (argc > 1) {
    parcer(argc, argv, &options);
    if (options.b == 1) {
      options.n = 0;
    }
    if (options.t == 1) {
      options.T = 1;
      options.v = 1;
    }
    if (options.e == 1) {
      options.v = 1;
      options.E = 1;
    }

    reader(argc, argv, &options);

  } else {
    fprintf(stderr, "no arguments");
  }
  return 0;
}

void parcer(int argc, char *argv[], opt *options) {
  int opt;

  static struct option longopts[] = {{"number", 0, 0, 'n'},
                                     {"number-nonblank", 0, 0, 'b'},
                                     {"squeeze-blank", 0, 0, 's'},
                                     {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "benstvET", longopts, &optind)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        break;
      case 'T':
        options->T = 1;
        break;
      case 'E':
        options->E = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      default:
        exit(1);
        break;
    }
  }
}

void reader(int argc, char *argv[], opt *options) {
  int curChar;
  int curLine = 1, sum = 1, indB = 0, indN = 0;

  while ((optind < argc)) {
    FILE *fi = fopen(argv[optind], "r");
    if (fi != NULL) {
      while ((curChar = fgetc(fi)) != EOF) {
        if (options->s == 1) {
          if (curChar == '\n') {
            sum++;
          } else {
            sum = 0;
          }
        }
        if (options->n == 1 && sum < 3) {
          if (indN == 0) {
            printf("%6d\t", curLine);
            curLine++;
            indN = 1;
          }
          if (curChar == '\n') {
            indN = 0;
          }
        }

        if (options->E == 1 && curChar == '\n' && sum < 3) {
          printf("$");
        }
        if (options->b == 1) {
          if (curChar == '\n') {
            indB = 0;
          } else if (indB == 0) {
            printf("%6d\t", curLine);
            curLine++;
            indB = 1;
          }
        }
        if (sum < 3) {
          if (options->v == 1) {
            if (((curChar >= 0 && curChar <= 8) ||
                 (curChar >= 11 && curChar <= 31) || curChar == 127)) {
              curChar = (curChar + 64) % 128;
              printf("^");
            }
          }
          if (options->T == 1 && curChar == '\t') {
            printf("^I");
          } else {
            printf("%c", curChar);
          }
        }
      }
      fclose(fi);
    } else {
      fprintf(stderr, "%s No such file or directory", argv[optind]);
    }

    optind++;
  }
}