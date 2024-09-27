#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int *res = s21_NULL;
  for (s21_size_t i = 0; i < n; i++) {
    if (*((unsigned char *)str + i) == c) {
      return ((unsigned char *)str + i);
    }
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n; i++) {
    res = *((unsigned char *)str1 + i) - *((unsigned char *)str2 + i);
    if (res) {
      i = n;
    }
  }
  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *((unsigned char *)dest + i) = *((unsigned char *)src + i);
  }
  return (unsigned char *)dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *((unsigned char *)dest + i) = *((unsigned char *)src + i);
  }
  return (unsigned char *)dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *((unsigned char *)str + i) = c;
  }
  return (unsigned char *)str;
}

char *s21_strcat(char *dest, const char *src) {
  int len = 0;
  for (int i = 0; dest[i] != '\0'; i++) {
    len++;
  }
  for (int i = 0; src[i] != '\0'; i++) {
    dest[len + i] = src[i];
    dest[len + 1 + i] = '\0';
  }
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int len = 0;
  for (int i = 0; dest[i] != '\0'; i++) {
    len++;
  }
  for (int i = 0; src[i] != '\0' && i < (int)n; i++) {
    dest[len + i] = src[i];
    dest[len + 1 + i] = '\0';
  }
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  char *res = s21_NULL;
  for (; str[i] != '\0' && str[i] != c; i++) {
  }
  if (str[i] == c) {
    res = (char *)str + i;
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  int check = 1;
  for (int i = 0; check; i++) {
    res = str1[i] - str2[i];
    if (res || str1[i] == '\0' || str2[i] == '\0') {
      check = 0;
    }
  }
  return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  int check = 1;
  for (int i = 0; check && i < (int)n; i++) {
    res = str1[i] - str2[i];
    if (res || str1[i] == '\0' || str2[i] == '\0') {
      check = 0;
    }
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  char *d = dest;
  while (*src) {
    *d++ = *src++;
  }
  *d = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *d = dest;
  while (*src && n) {
    *d++ = *src++;
    --n;
  }
  while (n) {
    *d++ = '\0';
    --n;
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int len_str1 = 0;
  int len_str2 = 0;
  s21_size_t count = 0;
  int check = 1;
  // find len = strlen(src)
  for (int i = 0; str1[i] != '\0'; i++) {
    len_str1++;
    if (str1[i + 1] == '\0') {
      len_str1++;
    }
  }
  for (int i = 0; str2[i] != '\0'; i++) {
    len_str2++;
    if (str2[i + 1] == '\0') {
      len_str2++;
    }
  }
  for (int i = 0; i < len_str1 && check; i++) {
    for (int k = 0; k < len_str2 && check; k++) {
      if (str1[i] == str2[k]) {
        check = 0;
      }
    }
    count = (check == 1) ? count + 1 : count;
  }
  return count;
}

char *s21_strerror(int errnum) {
  char *ERRORS[] = ERR_LIST;
  char *res = s21_NULL;
  static char buf[50] = {'\0'};
  if (errnum >= 0 && errnum < N) {
    res = ERRORS[errnum];
  } else {
    if (std == 0) {
      s21_sprintf(buf, "Unknown error: %d", errnum);
    } else if (std == 1) {
      s21_sprintf(buf, "Unknown error %d", errnum);
    }
  }
  return res == s21_NULL ? buf : res;
}

// Masha
s21_size_t s21_strlen(const char *str) {
  s21_size_t res = 0;
  while (str[res]) {
    res++;
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *res = s21_NULL;
  int check = 1;
  for (int i = 0; str1[i] != '\0' && check; i++) {
    for (int k = 0; str2[k] != '\0' && check; k++) {
      if (str1[i] == str2[k]) {
        res = str1 + i;
        check = 0;
      }
    }
  }
  return (char *)res;
}

char *s21_strrchr(const char *str, int c) {
  int i = 0;
  char *res = s21_NULL;
  for (; str[i] != '\0'; i++) {
    if (str[i] == c) {
      res = (char *)str + i;
    }
  }
  if (c == '\0') {
    res = (char *)str + i;
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  int plus_len = 0;
  int check = 1;
  s21_size_t len_spn = 0;
  for (int i = 0; str1[i] != '\0' && check; i++) {
    for (int k = 0; str2[k] != '\0' && check; k++) {
      if (str1[i] == str2[k]) {
        plus_len = 1;
        check = 0;
      }
    }
    if (plus_len) {
      len_spn++;
      plus_len = 0;
      check = 1;
    } else {
      check = 0;
    }
  }
  return len_spn;
}

char *s21_strstr(const char *haystack, const char *needle) {
  while (*haystack) {
    const char *hptr = haystack;
    const char *nptr = needle;
    while (*nptr && *nptr == *hptr) {
      ++hptr;
      ++nptr;
    }
    if (!*nptr) {
      break;
    }
    ++haystack;
  }
  return (*haystack || !*needle ? (char *)haystack : s21_NULL);
}

// char *s21_strtok(char *src, const char *delim) {
//   static char *ptr;
//   char *str;
//   if (src != s21_NULL) {
//     ptr = src;
//   }
//   str = ptr;
//   if (str != s21_NULL) {
//     str += s21_strspn(str, delim);
//     if (*str) {
//       ptr = str + s21_strcspn(str, delim);
//       if (*ptr) {
//         *ptr++ = '\0';
//       }
//     } else {
//       str = ptr = s21_NULL;
//     }
//   }
//   return (str);
// }

static int s21_delim(char c, const char *delim) {
  int flag = 0;
  while (*delim != '\0') {
    if (c == *delim) flag = 1;
    delim++;
  }
  return flag;
}

char *s21_strtok(char *s, const char *delim) {
  static char *st_ch = s21_NULL;
  char *ch_pointer;

  if (!s) s = st_ch;
  if (*s == '\0') {
    ch_pointer = s21_NULL;
  } else {
    while (1) {
      if (s21_delim(*s, delim)) {
        s++;
        continue;
      }
      if (*s == '\0') s = s21_NULL;
      break;
    }
    ch_pointer = s;
    while (s != s21_NULL) {
      if (*s == '\0') {
        st_ch = s;
        break;
      }
      if (s21_delim(*s, delim)) {
        *s = '\0';
        st_ch = s + 1;
        break;
      }
      s++;
    }
  }
  return (ch_pointer);
}

// Masha -->

void *s21_to_upper(const char *buff) {
  s21_size_t offset = 'a' - 'A';
  char *res = s21_NULL;
  if (buff != s21_NULL) {
    s21_size_t len = s21_strlen(buff);
    res = malloc(sizeof(char) * (len + 1));
    if (res != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        if (buff[i] >= 'a' && buff[i] <= 'z') {
          res[i] = buff[i] - offset;
        } else {
          res[i] = buff[i];
        }
      }
      res[len] = '\0';
    }
  }
  return (void *)res;
}

void *s21_to_lower(const char *buff) {
  s21_size_t offset = 'a' - 'A';
  char *res = s21_NULL;
  if (buff != s21_NULL) {
    s21_size_t len = s21_strlen(buff);
    res = malloc(sizeof(char) * (len + 1));
    if (res != s21_NULL) {
      for (s21_size_t i = 0; i < len; i++) {
        if (buff[i] >= 'A' && buff[i] <= 'Z') {
          res[i] = buff[i] + offset;
        } else {
          res[i] = buff[i];
        }
      }
      res[len] = '\0';
    }
  }
  return (void *)res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  const char *begin = src;
  const char *end;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    while (*begin != '\0' && s21_strchr(trim_chars, *begin) != s21_NULL) {
      ++begin;
    }
    if (*begin == '\0') {
      res = calloc(1, sizeof(char));
    } else {
      end = src + s21_strlen(src) - 1;
      while (end != begin && s21_strchr(trim_chars, *end) != s21_NULL) {
        --end;
      }
      s21_size_t len = end - begin + 1;
      res = malloc(sizeof(char) * (len + 1));
      if (res != s21_NULL) {
        for (s21_size_t i = 0; i < len; ++i) {
          res[i] = begin[i];
        }
        res[len] = '\0';
      }
    }
  } else if (src != s21_NULL && trim_chars == s21_NULL) {
    res = calloc(s21_strlen(src), sizeof(char));
    s21_strcpy(res, src);
  }
  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;
  if (src && str) {
    if (s21_strlen(src) >= start_index) {
      res =
          (char *)calloc((s21_strlen(src) + s21_strlen(str) + 1), sizeof(char));
      if (res) {
        s21_size_t i = 0;
        s21_size_t j = 0;
        for (; i < start_index; i++) {
          res[i] = src[i];
        }
        for (; j < s21_strlen(str); j++) {
          res[i + j] = str[j];
        }
        for (i = start_index; i < s21_strlen(src); i++) {
          res[i + j] = src[i];
        }
      }
    }
  }
  return (void *)res;
}
