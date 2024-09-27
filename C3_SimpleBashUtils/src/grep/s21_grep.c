#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    opt options = {0};
    parcer(argc, argv, &options);
    reader(argc, argv, &options);
  } else {
    fprintf(stderr, "no arguments");
  }

  return 0;
}

void parcer(int argc, char *argv[], opt *options) {
  int opt;
  char stringArgs[2048] = "";

  static struct option longopts[] = {{0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", longopts, &optind)) !=
         -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        strcat(stringArgs, optarg);
        strcat(stringArgs, "|");
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        strcpy(options->fArg, optarg);
        break;
      case 'o':
        options->o = 1;

        break;
      default:
        exit(1);
        break;
    }
  }
  stringArgs[strlen(stringArgs) - 1] = '\0';
  strcpy(options->eArg, stringArgs);
  // printf ("%s\n\n\n\n\n", options -> eArg);
}

void reader(int argc, char *argv[], opt *options) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  regex_t regex;
  int res = 0, nameFlag = 1, compare = 0;
  char regFlags = 0;
  char summaryLine[2048];
  makeString(argv, options, summaryLine);
  if (optind + 1 < argc) {
    nameFlag = 0;
  }
  if (options->h == 1) {
    nameFlag = 1;
  }
  if (options->i == 1) {
    regFlags = REG_ICASE;
  }
  if (options->e || options->f) {
    regFlags = REG_EXTENDED;
    if (options->l) {
      regFlags = REG_EXTENDED | REG_ICASE;
    }
  }

  regcomp(&regex, summaryLine, regFlags);
  while (optind < argc) {
    FILE *fi = fopen(argv[optind], "r");
    int counterString = 1, flagCcounter = 0, flagL = 1;
    if (fi == NULL) {
      if (!options->s) {
        fprintf(stderr, "s21_grep:%s No such file or directory\n",
                argv[optind]);
      }
    } else {
      while ((read = getline(&line, &len, fi)) != -1) {
        res = regexec(&regex, line, 0, NULL, 0);
        if (options->v) {
          compare = REG_NOMATCH;
        }
        if (res == compare) {
          if (options->c) {
            flagCcounter++;
          }
          if (options->l) {
            flagL = 0;
          }
          if (!options->l && !options->c) {
            if (nameFlag == 0 && !options->o) {
              printf("%s:", argv[optind]);
            }
            if (options->n && !options->o) {
              printf("%d:", counterString);
            }
            if (options->o) {
              flagOseach(summaryLine, line, counterString, options, nameFlag,
                         argv);
            } else {
              printf("%s", line);
              if (line[strlen(line) - 1] != '\n') {
                printf("\n");
              }
            }
          }
        }
        counterString++;
      }

      if (flagL == 0) {
        printf("%s\n", argv[optind]);
        flagL = 1;
      }
      if (options->c && !options->l) {
        if (nameFlag) {
          printf("%d\n", flagCcounter);
        } else {
          printf("%s:%d\n", argv[optind], flagCcounter);
        }
      }
      fclose(fi);
    }
    optind++;
  }
  free(line);
  regfree(&regex);
}

void makeString(char *argv[], opt *options, char *summaryLine) {
  if (options->e) {
    strcpy(summaryLine, options->eArg);
  } else if (options->f) {
    char omega[4096];
    FILE *sourceFile = fopen(options->fArg, "r");
    int i = 0;
    char c = ' ';
    while ((c = fgetc(sourceFile)) != EOF) {
      if (c == '\n') {
        omega[i++] = '|';
      } else {
        omega[i++] = c;
      }
    }
    if (omega[strlen(omega) - 1] == '|') {
      omega[strlen(omega) - 1] = '\0';
    }
    strcpy(summaryLine, omega);
    fclose(sourceFile);
  } else {
    strcpy(summaryLine, argv[optind++]);
  }
}

void flagOseach(char *summaryLine, char *line, int counterString, opt *options,
                int nameFlag, char *argv[]) {
  char *tempo = strstr(line, summaryLine);
  int capacity = strlen(summaryLine);
  while (tempo != NULL) {
    if (!nameFlag) {
      printf("%s:", argv[optind]);
    }
    if (options->n) {
      printf("%d:", counterString);
    }
    printf("%s\n", summaryLine);
    line = tempo + capacity;
    tempo = strstr(line, summaryLine);
  }
}