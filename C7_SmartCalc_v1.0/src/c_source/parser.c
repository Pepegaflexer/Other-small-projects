#include "s21_smartCalc.h"

void popFromStash(node **start, char *stash) {
  int tmp = strlen(stash) - 1;
  switch (stash[tmp]) {
    case '+':
      push(start, 0, SUM);
      break;
    case '-':
      push(start, 0, SUB);
      break;
    case '*':
      push(start, 0, MUL);
      break;
    case '/':
      push(start, 0, DIV);
      break;
    // case 'x':
    //   push(start, 0, X);
    //   break;
    case '^':
      push(start, 0, POW);
      break;
    case 'l':
      push(start, 0, LN);
      break;
    case 'c':
      push(start, 0, COS);
      break;
    case 's':
      push(start, 0, SIN);
      break;
    case 'g':
      push(start, 0, LOG);
      break;
    case 't':
      push(start, 0, TAN);
      break;
    case 'o':
      push(start, 0, ACOS);
      break;
    case 'i':
      push(start, 0, ASIN);
      break;
    case 'q':
      push(start, 0, SQRT);
      break;
    case 'a':
      push(start, 0, ATAN);
      break;
    case 'm':
      push(start, 0, MOD);
      break;
    case '~':
      push(start, 0, UN_MINUS);
      break;
    default:
      break;
  }

  stash[strlen(stash) - 1] = '\0';
}

void pushInStash(char *stash, char buff) { stash[strlen(stash)] = buff; }

int perviye(char simbol) {
  int res = 0;
  if (simbol == '+' || simbol == '-') {
    res = 1;
  }
  return res;
}

int vtoriye(char simbol) {
  int res = 0;
  if (simbol == '*' || simbol == '/' || simbol == 'm' || simbol == '^') {
    res = 1;
  }
  return res;
}

int tretiye(char simbol) {
  char o3[10] = {'l', 'c', 's', 't', 'o', 'i', 'q', 'a', 'g'};
  int res = 0;
  if (strchr(o3, simbol)) {
    res = 1;
  }
  return res;
}

const char *odnosimvolniye(node **start, const char *format, char *buff,
                           int *buffCount, int *flag, char *stash,
                           double xValue) {
  if ((buff[0] >= '0' && buff[0] <= '9') || buff[0] == '.') {
    while ((*format >= '0' && *format <= '9') || *format == '.') {
      buff[(*buffCount)++] = *format++;
    }
    const char *value = buff;
    double chislo = atof(value);
    push(start, chislo, NUM);
    *flag = 1;
  } else if (buff[0] == '+') {
    while ((strlen(stash) > 0) && (vtoriye(stash[strlen(stash) - 1]) ||
                                   perviye(stash[strlen(stash) - 1]))) {
      popFromStash(start, stash);
    }
    pushInStash(stash, '+');
    *flag = 1;
  } else if (buff[0] == '-') {
    if (*(format - 2) == '(') {
      pushInStash(stash, '~');
    } else {
      while ((strlen(stash) > 0) && (vtoriye(stash[strlen(stash) - 1]) ||
                                     perviye(stash[strlen(stash) - 1]))) {
        popFromStash(start, stash);
      }
      pushInStash(stash, '-');
    }
    *flag = 1;
  } else if (buff[0] == '(') {
    pushInStash(stash, '(');
    *flag = 1;
  } else if (buff[0] == ')') {
    while ((strlen(stash) > 0) && (stash[strlen(stash) - 1] != '(')) {
      popFromStash(start, stash);
    }
    stash[strlen(stash) - 1] = '\0';
    if ((strlen(stash) > 0) && tretiye(stash[strlen(stash) - 1])) {
      popFromStash(start, stash);
    }
    *flag = 1;
  } else if (buff[0] == 'x') {
    push(start, xValue, X);
    *flag = 1;
  } else if (buff[0] == '^') {
    pushInStash(stash, '^');
    *flag = 1;
  } else if (buff[0] == '*') {
    while ((strlen(stash) > 0) && vtoriye(stash[strlen(stash) - 1])) {
      popFromStash(start, stash);
    }
    pushInStash(stash, '*');
    *flag = 1;
  } else if (buff[0] == '/') {
    while ((strlen(stash) > 0) && vtoriye(stash[strlen(stash) - 1])) {
      popFromStash(start, stash);
    }
    pushInStash(stash, '/');
    *flag = 1;
  }
  return format;
}

void trehsimvolniye(char *buff, int *flag, char *stash) {
  if (!strcmp(buff, "cos")) {
    pushInStash(stash, 'c');
    *flag = 1;
  } else if (!strcmp(buff, "sin")) {
    pushInStash(stash, 's');
    *flag = 1;
  } else if (!strcmp(buff, "log")) {
    pushInStash(stash, 'g');
    *flag = 1;
  } else if (!strcmp(buff, "tan")) {
    pushInStash(stash, 't');
    *flag = 1;
  } else if (!strcmp(buff, "mod")) {
    pushInStash(stash, 'm');
    *flag = 1;
  }
}

void chetirehsimvolniye(char *buff, int *flag, char *stash) {
  if (!strcmp(buff, "acos")) {
    pushInStash(stash, 'o');
    *flag = 1;
  } else if (!strcmp(buff, "asin")) {
    pushInStash(stash, 'i');
    *flag = 1;
  } else if (!strcmp(buff, "sqrt")) {
    pushInStash(stash, 'q');
    *flag = 1;
  } else if (!strcmp(buff, "atan")) {
    pushInStash(stash, 'a');
    *flag = 1;
  }
}

void deleteList(node **head) {
  node *prev = NULL;
  while ((*head)) {
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
  }
  free(*head);
}

void reverseList(node **src, node **dst) {
  node *prev = NULL;
  while (*src != NULL) {
    prev = (*src);
    push(dst, prev->value, prev->opr);
    *src = (*src)->next;
    free(prev);
  }
  free(*src);
}

double pop(node **head) {
  node *prev = NULL;
  double val;
  if (head == NULL) {
    exit(-1);
  } else {
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
  }
}

void push(node **head, double data, type_opr oper) {
  node *tmp = (node *)malloc(sizeof(node));
  tmp->value = data;
  tmp->opr = oper;
  tmp->next = *head;
  *head = tmp;
}