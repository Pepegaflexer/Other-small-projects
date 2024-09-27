#include "s21_string.h"

void print_flags(format_flags flags);
void num_to_string(char *buff, int64_t var, int base);
void get_value(char *buff, format_flags flags, va_list ptr, int len);
void edit_presicion(char *buff, format_flags flags);
void char_to_string(char *buff, unsigned char c);
int edit_width(char *buff, format_flags flags);
void edit_sharp(char *buff, format_flags flags);
void get_int(format_flags flags, char *buff, va_list ptr);
void get_u_int(format_flags flags, char *buff, va_list ptr);
void get_x_int(format_flags flags, char *buff, va_list ptr);
void get_o_int(format_flags flags, char *buff, va_list ptr);
void get_p_int(format_flags flags, char *buff, va_list ptr);
void edit_flags(char *buff, format_flags flags);
void double_to_string_e(char *buff, long double var, format_flags flags);
void insert_last_char(char *buff, char c);
void to_upper(char *buff);
void double_to_string_six(char *buff, long double var, format_flags flags);
void double_to_string_g(char *buff, long double var, format_flags flags);
void reverse_str(char *dest, char *src);
void delete_last_null(char *buff);
void delete_last_null_e(char *buff);
void u_num_to_string(char *buff, uint64_t var, int base);
void insert_e_notation(char *buff, int exp);
void moove_left(char *buff, int count_spaces);

void parse_string(char *buff, format_flags flags, va_list ptr);
void parse_f(char *buff, format_flags flags, va_list ptr);
void parse_e(char *buff, format_flags flags, va_list ptr);
void parse_x(char *buff, format_flags flags, va_list ptr);
void parse_n(va_list ptr, int len);
void parse_g(char *buff, format_flags flags, va_list ptr);

int s21_sprintf(char *str, const char *format, ...) {
  format_flags flags = {0};
  char *str_begining = str;
  va_list ptr;
  int len = 0;
  va_start(ptr, format);
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&flags, 0, sizeof(flags));
    }
    format = parser_flags(format, &flags);
    format = parser_width(format, &flags);
    format = parser_precision(format, &flags);
    format = parser_length(format, &flags);

    flags.specifier = *format;
    format++;

    char buff[BUFF_SIZE] = {'\0'};
    // len = s21_strlen(str_begining);
    get_value(buff, flags, ptr, len);
    for (int i = s21_strlen(buff) - 1; i >= 0; i--, str++) {
      *str = *(buff + i);
      len++;
    }
  }
  *str = '\0';
  va_end(ptr);
  return str - str_begining;
}
// %[флаги][ширина][.точность][длина]спецификатор
// parse flags only
const char *parser_flags(const char *format, format_flags *flags) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '#' ||
         *format == '0') {
    switch (*format) {
      case '-':
        flags->minus = 1;
        format++;
        break;
      case '+':
        flags->plus = 1;
        format++;
        break;
      case ' ':
        flags->space = 1;
        format++;
        break;
      case '#':
        flags->sharp = 1;
        format++;
        break;
      case '0':
        flags->zero = 1;
        format++;
        break;
      default:
        break;
    }
  }
  return format;
}

// parse width only
const char *parser_width(const char *format, format_flags *flags) {
  if (is_digit(*format)) {
    char digit_string[1024] = {'\0'};
    int i = 0;
    while (is_digit(*format)) {
      digit_string[i] = *format++;
      i++;
    }
    flags->width = s21_atoi(digit_string);
  } else if (*format == '*') {
    flags->width_is_star = 1;
    format++;
  }
  return format;
}

// parse precision only
const char *parser_precision(const char *format, format_flags *flags) {
  if (*format == '.') {
    flags->precision = -1;
    format++;
    if (is_digit(*format)) {
      char digit_string[1024] = {'\0'};
      int i = 0;
      while (is_digit(*format)) {
        digit_string[i] = *format++;
        i++;
      }
      flags->precision =
          s21_atoi(digit_string) == 0 ? -1 : s21_atoi(digit_string);
    } else if (*format == '*') {
      flags->precision_is_star = 1;
      format++;
    }
  }
  return format;
}

// parse length only
const char *parser_length(const char *format, format_flags *flags) {
  switch (*format) {
    case 'h':
      flags->length = 'h';
      format++;
      break;
    case 'l':
      flags->length = 'l';
      format++;
      break;
    case 'L':
      flags->length = 'L';
      format++;
      break;
    default:
      break;
  }
  return format;
}

// print values of all flags
void print_flags(format_flags flags) {
  printf("-:%d +:%d space:%d #:%d 0:%d w:%d w*:%d .:%d .*:%d len:%c spec:%c\n",
         flags.minus, flags.plus, flags.space, flags.sharp, flags.zero,
         flags.width, flags.width_is_star, flags.precision,
         flags.precision_is_star, flags.length, flags.specifier);
}

// string to int (string consists only digits)
int s21_atoi(const char *str) {
  int res = 0;
  int len = s21_strlen(str);
  for (int i = len - 1; i >= 0; i--) {
    res += (str[i] - 48) * pow(10, (len - i - 1));
  }
  return res;
}
// if char c is digit, return 1
int is_digit(char c) {
  int res = 0;
  if ((c >= 48) && (c <= 57)) {
    res = 1;
  }
  return res;
}
// int to string
void num_to_string(char *buff, int64_t var, int base) {
  int i = 0;
  int minus = var < 0 ? 1 : 0;
  var = var < 0 ? -var : var;
  if (var == 0) {
    buff[i++] = '0';
  }
  while (var > 0) {
    buff[i++] = "0123456789abcdef"[var % base];
    var /= base;
  }
  buff[i] = (minus == 1) ? '-' : '\0';
}

void u_num_to_string(char *buff, uint64_t var, int base) {
  int i = 0;
  if (var == 0) {
    buff[i++] = '0';
  }
  while (var > 0) {
    buff[i++] = "0123456789abcdef"[var % base];
    var /= base;
  }
}

void char_to_string(char *buff, unsigned char c) { buff[0] = c; }

// get values from variables
void get_value(char *buff, format_flags flags, va_list ptr, int len) {
  if (flags.width_is_star) {
    flags.width = va_arg(ptr, int);
  }
  if (flags.precision_is_star) {
    flags.precision = va_arg(ptr, int);
  }
  if (flags.specifier == 'c') {
    flags.space = 0;
    flags.plus = 0;
    char_to_string(buff, va_arg(ptr, int));
    edit_width(buff, flags);
    edit_flags(buff, flags);
  } else if (flags.specifier == 'd' || flags.specifier == 'i') {
    get_int(flags, buff, ptr);
    edit_presicion(buff, flags);
    edit_width(buff, flags);
    edit_flags(buff, flags);
  } else if (flags.specifier == 'e') {
    parse_e(buff, flags, ptr);
  } else if (flags.specifier == 'E') {
    parse_e(buff, flags, ptr);
    to_upper(buff);
  } else if (flags.specifier == 'f') {
    parse_f(buff, flags, ptr);
  } else if (flags.specifier == 's') {
    parse_string(buff, flags, ptr);
  } else if (flags.specifier == 'u') {
    get_u_int(flags, buff, ptr);
    edit_width(buff, flags);
    edit_presicion(buff, flags);
    flags.space = 0;
    flags.plus = 0;
    edit_flags(buff, flags);
  } else if (flags.specifier == '%') {
    buff[0] = '%';
    //  } else if (flags.specifier == 'g') {
    //    parse_g(buff, flags, ptr);
    //  } else if (flags.specifier == 'G') {
    //    parse_g(buff, flags, ptr);
    //    to_upper(buff);
  } else if (flags.specifier == 'x') {
    parse_x(buff, flags, ptr);
  } else if (flags.specifier == 'X') {
    parse_x(buff, flags, ptr);
    to_upper(buff);
  } else if (flags.specifier == 'o') {
    get_o_int(flags, buff, ptr);
    edit_sharp(buff, flags);
    edit_width(buff, flags);
    edit_flags(buff, flags);
    edit_presicion(buff, flags);
  } else if (flags.specifier == 'p') {
    get_p_int(flags, buff, ptr);
    edit_width(buff, flags);
  } else if (flags.specifier == 'n') {
    parse_n(ptr, len);
  }
}

void parse_string(char *buff, format_flags flags, va_list ptr) {
  int count_spaces = 0;
  char temp[BUFF_SIZE] = {'\0'};
  if (flags.precision > 0) {
    char *res = s21_NULL;
    res = va_arg(ptr, char *);
    if (res) {
      reverse_str(buff, s21_strncpy(temp, res, flags.precision));
    }
  } else if (flags.precision == 0) {
    reverse_str(buff, va_arg(ptr, char *));
  }
  count_spaces = edit_width(buff, flags);
  if (flags.minus) {
    moove_left(buff, count_spaces);
  }
  flags.space = 0;
  flags.plus = 0;
  edit_flags(buff, flags);
}

void parse_f(char *buff, format_flags flags, va_list ptr) {
  // print_flags(flags);
  if (flags.precision == 0) {
    flags.precision = 6;
  }
  if (flags.length == 'L') {
    double_to_string_six(buff, va_arg(ptr, long double), flags);
  } else {
    double_to_string_six(buff, va_arg(ptr, double), flags);
  }
  edit_width(buff, flags);
  edit_flags(buff, flags);
}

void parse_e(char *buff, format_flags flags, va_list ptr) {
  if (flags.length == 'L') {
    double_to_string_e(buff, va_arg(ptr, long double), flags);
  } else {
    double_to_string_e(buff, va_arg(ptr, double), flags);
  }
  edit_width(buff, flags);
  edit_flags(buff, flags);
}

void parse_x(char *buff, format_flags flags, va_list ptr) {
  get_x_int(flags, buff, ptr);
  edit_presicion(buff, flags);
  edit_sharp(buff, flags);
  edit_width(buff, flags);
  edit_flags(buff, flags);
}

void parse_n(va_list ptr, int len) {
  int *p = va_arg(ptr, int *);
  *p = len;
}

void parse_g(char *buff, format_flags flags, va_list ptr) {
  if (flags.length == 'L') {
    long double res = va_arg(ptr, long double);
    double_to_string_g(buff, res, flags);
  } else {
    double res1 = va_arg(ptr, double);
    double_to_string_g(buff, res1, flags);
  }
}

void moove_left(char *buff, int count_spaces) {
  int len = s21_strlen(buff);
  for (int i = 0; i < count_spaces; i++) {
    for (int k = len - 1; k > 0; k--) {
      char tmp = buff[k];
      buff[k] = buff[k - 1];
      buff[k - 1] = tmp;
    }
  }
}

// if flags.presicion !=0 do it
void edit_presicion(char *buff, format_flags flags) {
  if (flags.precision > 0) {
    int minus = buff[s21_strlen(buff) - 1] == '-' ? 1 : 0;
    buff[s21_strlen(buff) - 1] = minus == 1 ? '\0' : buff[s21_strlen(buff) - 1];
    if ((int)s21_strlen(buff) < flags.precision) {
      for (int i = s21_strlen(buff); i < flags.precision; i++) {
        buff[i] = '0';
      }
    }
    buff[s21_strlen(buff)] = minus == 1 ? '-' : buff[s21_strlen(buff)];
    // printf("presision:%s\n", buff);
  } else if (flags.precision == -1) {
    if (buff[0] == '0' && buff[1] == '\0') {
      buff[0] = '\0';
    }
  }
}

// if flags.length !=0 do it, return count of added spaces
int edit_width(char *buff, format_flags flags) {
  int count = 0;
  int minus = 0;
  char *tmp = buff + s21_strlen(buff) - 1;
  if (s21_strlen(buff) > 0) {
    minus = *tmp == '-' ? 1 : 0;
  }
  // printf("WIDTH%c\n", *tmp);
  while (flags.width > (int)s21_strlen(buff)) {
    tmp++;
    if (flags.zero && minus) {
      *(tmp - 1) = '0';
      *tmp = '-';
    } else {
      *tmp = flags.zero ? '0' : ' ';
    }
    count++;
  }
  return count;
}

void edit_flags(char *buff, format_flags flags) {
  int count_spaces = 0;
  for (int i = 0; buff[i] != '\0'; i++) {
    if (buff[i] == ' ') {
      count_spaces++;
    }
  }
  if (flags.minus && flags.width && count_spaces) {
    if (flags.specifier != 's') {
      for (int i = s21_strlen(buff) - 1; i >= 0; i--) {
        if (buff[i] != ' ') {
          buff[i + count_spaces] = buff[i];
          buff[i] = ' ';
        }
      }
    }
  }
  int last_symb = s21_strlen(buff);
  if (flags.plus) {
    if (s21_strlen(buff) > 0) {
      for (int i = s21_strlen(buff) - 1; buff[i] == ' '; i--) {
        last_symb = i;
      }
    }
    buff[last_symb] = buff[last_symb - 1] == '-' ? buff[last_symb] : '+';
  } else if (flags.space) {
    if (s21_strlen(buff) > 0) {
      for (int i = s21_strlen(buff) - 1; buff[i] == ' ' && i > 0; i--) {
        last_symb = i;
      }
      buff[last_symb] = buff[last_symb - 1] == '-' ? buff[last_symb] : ' ';
    }
  }
}

void edit_sharp(char *buff, format_flags flags) {
  if (flags.sharp) {
    if (flags.specifier == 'o') {
      buff[s21_strlen(buff)] = '0';
    } else if (flags.specifier == 'x' || flags.specifier == 'X') {
      if (s21_strspn(buff, "0") != s21_strlen(buff)) {
        s21_strcat(buff, "x0");
      }
    }
  }
}

void get_int(format_flags flags, char *buff, va_list ptr) {
  int64_t var = va_arg(ptr, int64_t);
  switch (flags.length) {
    case 0:
      var = (int32_t)var;
      break;
    case 'h':
      var = (int16_t)var;
      break;
  }
  num_to_string(buff, var, 10);
}

void get_u_int(format_flags flags, char *buff, va_list ptr) {
  uint64_t var = va_arg(ptr, uint64_t);
  switch (flags.length) {
    case 0:
      var = (uint32_t)var;
      break;
    case 'h':
      var = (uint16_t)var;
      break;
  }
  u_num_to_string(buff, var, 10);
}

void get_x_int(format_flags flags, char *buff, va_list ptr) {
  uint64_t var = va_arg(ptr, uint64_t);
  switch (flags.length) {
    case 0:
      var = (uint32_t)var;
      break;
    case 'h':
      var = (uint16_t)var;
      break;
  }
  u_num_to_string(buff, var, 16);
}

void get_o_int(format_flags flags, char *buff, va_list ptr) {
  uint64_t var = va_arg(ptr, uint64_t);
  switch (flags.length) {
    case 0:
      var = (uint32_t)var;
      break;
    case 'h':
      var = (uint16_t)var;
      break;
  }
  u_num_to_string(buff, var, 8);
}

void get_p_int(format_flags flags, char *buff, va_list ptr) {
  uint64_t var = va_arg(ptr, uint64_t);
  u_num_to_string(buff, var, 16);
  edit_presicion(buff, flags);
  buff[s21_strlen(buff)] = 'x';
  buff[s21_strlen(buff)] = '0';
  // printf("pointer:%p\n", var);
}

void double_to_string_e(char *buff, long double var, format_flags flags) {
  if (flags.precision == 0) {
    flags.precision = 6;
  }
  int minus = var < 0 ? 1 : 0;
  var = var < 0 ? -var : var;
  int exp = 0;

  while (var >= 10) {
    var /= 10;
    exp++;
  }
  while (var < 1 && var > 0) {
    var *= 10;
    exp--;
  }
  for (int i = 0; i < flags.precision; i++) {
    var *= 10;
  }
  var = roundl(var);
  for (int i = 0; i < flags.precision; i++) {
    var /= 10;
  }

  double_to_string_six(buff, var, flags);
  insert_e_notation(buff, exp);
  if (minus) {
    buff[s21_strlen(buff)] = '-';
  }
}

void insert_last_char(char *buff, char c) {
  for (int i = s21_strlen(buff) - 1; i >= 0; i--) {
    buff[i + 1] = buff[i];
  }
  buff[0] = c;
}

void to_upper(char *buff) {
  for (int i = 0; buff[i] != '\0'; i++) {
    if (buff[i] >= 97 && buff[i] <= 122) {
      buff[i] = buff[i] - 32;
    }
  }
}

// double to string whith six gigits after point
void double_to_string_six(char *buff, long double var, format_flags flags) {
  if (flags.precision == -1) {
    var = roundl(var);
  }
  int minus = var < 0 ? 1 : 0;
  var = var < 0 ? -var : var;
  long double left = 0;
  long double right = modfl(var, &left);
  long long lleft = left;
  char left_str[50] = {'\0'};
  char right_str[50] = {'\0'};
  for (int i = 0; i < flags.precision; i++) {
    right *= 10;
  }
  long long rright = roundl(right);
  if (rright) {
    num_to_string(right_str, rright, 10);
  }
  while (flags.precision != -1 &&
         (int)s21_strlen(right_str) < flags.precision) {
    right_str[s21_strlen(right_str)] = '0';
  }
  num_to_string(left_str, lleft, 10);
  if (s21_strlen(right_str)) {
    s21_strcat(buff, right_str);
    s21_strcat(buff, ".");
  }
  s21_strcat(buff, left_str);

  if (minus) {
    buff[s21_strlen(buff)] = '-';
  }
}

void double_to_string_g(char *buff, long double var, format_flags flags) {
  if (flags.precision == 0) {
    flags.precision = 6;
  } else if (flags.precision == -1) {
    flags.precision = 1;
  }
  long double tmp = var;
  // int minus = var < 0 ? 1 : 0;
  var = var < 0 ? -var : var;
  int exp = 0;

  while (var >= 10) {
    var /= 10;
    exp++;
  }
  while (var < 1 && var > 0) {
    var *= 10;
    exp--;
  }
  for (int i = 0; i < flags.precision - 1; i++) {
    var *= 10;
  }
  var = roundl(var);
  for (int i = 0; i < flags.precision - 1; i++) {
    var /= 10;
  }
  if (exp >= -4 && exp < flags.precision) {
    flags.precision = (flags.precision - 1 - exp);
    double_to_string_six(buff, tmp, flags);
    delete_last_null(buff);
  } else {
    flags.precision = (flags.precision - 1);
    double_to_string_e(buff, tmp, flags);
    delete_last_null_e(buff);
  }
}

void reverse_str(char *dest, char *src) {
  int k = 0;
  if (src) {
    for (int i = s21_strlen(src) - 1; i >= 0; i--) {
      dest[k++] = src[i];
    }
  }
}

void delete_last_null(char *buff) {
  while (buff[0] == '0') {
    for (int i = 0; buff[i] != '\0'; i++) {
      buff[i] = buff[i + 1];
    }
  }
  if (buff[0] == '.') {
    for (int i = 0; buff[i] != '\0'; i++) {
      buff[i] = buff[i + 1];
    }
  }
}

void delete_last_null_e(char *buff) {
  while (buff[4] == '0') {
    for (int i = 4; buff[i] != '\0'; i++) {
      buff[i] = buff[i + 1];
    }
  }
  if (buff[4] == '.') {
    for (int i = 4; buff[i] != '\0'; i++) {
      buff[i] = buff[i + 1];
    }
  }
}

void insert_e_notation(char *buff, int exp) {
  insert_last_char(buff, 'e');
  char tmp[50] = {'\0'};
  if (exp < 0) {
    insert_last_char(buff, '-');
    exp *= -1;
  } else {
    insert_last_char(buff, '+');
  }
  num_to_string(tmp, exp, 10);
  if (s21_strlen(tmp) == 1) {
    insert_last_char(buff, '0');
    insert_last_char(buff, tmp[0]);
  } else {
    for (int i = 0; i < (int)s21_strlen(tmp); i++) {
      insert_last_char(buff, tmp[s21_strlen(tmp) - i - 1]);
    }
  }
}