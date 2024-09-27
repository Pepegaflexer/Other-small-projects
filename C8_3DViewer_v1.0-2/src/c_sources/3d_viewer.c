#include "3d_viewer.h"

void reader(dataStruct *srcData, char *path) {
  const char *pattern_v = "^v( +-?[0-9]+((,|.)([0-9]+))?){3}";
  const char *pattern_f = "^f ";
  regex_t regex_v;
  regex_t regex_f;
  regcomp(&regex_v, pattern_v, REG_EXTENDED);
  regcomp(&regex_f, pattern_f, REG_EXTENDED);
  sumPointPoly(srcData, path, regex_v, regex_f);
  s21_create_matrix(srcData->count_of_vertexes, 3, &srcData->matrix_3d);
  srcData->polygons = calloc(srcData->count_of_facets, sizeof(polygon_t));
  parserObj(srcData, path, regex_v, regex_f);
  findMinMaxX(srcData);
  findMinMaxY(srcData);
  findMinMaxZ(srcData);
  regfree(&regex_f);
  regfree(&regex_v);
}

void sumPointPoly(dataStruct *srcData, char *path, regex_t regex_v,
                  regex_t regex_f) {
  ssize_t read;
  char *line = NULL;
  size_t len = 0;
  FILE *src;
  if ((src = fopen(path, "r")) == NULL) {
    printf("файл не открылся\n");
  } else {
    while ((read = getline(&line, &len, src)) != -1) {
      if (!(regexec(&regex_v, line, 0, NULL, 0))) {
        srcData->count_of_vertexes++;
      } else if (!(regexec(&regex_f, line, 0, NULL, 0))) {
        srcData->count_of_facets++;
      }
    }
    fclose(src);
  }
  free(line);
}

void parserObj(dataStruct *srcData, char *path, regex_t regex_v,
               regex_t regex_f) {
  ssize_t read;
  char *line = NULL;
  size_t len = 0;
  FILE *src;
  char tmp[100] = {'\n'};
  int forF[1000] = {0};
  int rm = 0, i = 0, cm = 0, cur = 0, f = 0, facet = 0;

  if ((src = fopen(path, "r")) == NULL) {
    printf("файл не открылся\n");
  } else {
    while ((read = getline(&line, &len, src)) != -1) {
      i = 0;
      int flag = 0;
      if (!(regexec(&regex_v, line, 0, NULL, 0))) {
        while (line[i] != '\n') {
          if (isDigit(line[i]) || line[i] == '.' || line[i] == ',' ||
              line[i] == '-') {
            tmp[cur] = line[i];
            cur++;
            flag = 1;
          } else if (flag == 1) {
            srcData->matrix_3d.matrix[rm][cm] = atof(tmp);
            memset(tmp, 0, 100);
            cm++;
            cur = 0;
            flag = 0;
          }
          i++;
        }
        if (flag == 1) {
          srcData->matrix_3d.matrix[rm][cm] = atof(tmp);
          memset(tmp, 0, 100);
          cm++;
          cur = 0;
          flag = 0;
        }
        rm++;
        cm = 0;
      } else if (!(regexec(&regex_f, line, 0, NULL, 0))) {
        f = 0;
        while (line[i] != '\n') {
          if (line[i] == '/') {
            flag = 1;
          } else if ((line[i] == '-' || isDigit(line[i])) && flag == 0) {
            tmp[cur] = line[i];
            cur++;
          } else if ((line[i] == ' ' || line[i + 1] == '\n') &&
                     line[i - 1] != 'f' && strlen(tmp)) {
            forF[f] = atoi(tmp);
            f++;
            memset(tmp, 0, 100);
            cur = 0;
            flag = 0;
            srcData->polygons[facet].num_of_ver_in_facets++;
          }
          i++;
        }
        srcData->polygons[facet].vertexes =
            calloc(srcData->polygons->num_of_ver_in_facets, sizeof(int));
        for (int k = 0; k < srcData->polygons->num_of_ver_in_facets; k++) {
          srcData->polygons[facet].vertexes[k] = forF[k];
        }
        memset(forF, 0, 100);
        memset(tmp, 0, 100);
        f = 0;
        facet++;
      }
    }
    fclose(src);
  }
  free(line);
}

int isDigit(char c) {
  int lab = 0;
  if (c >= '0' && c <= '9') lab = 1;
  return lab;
}

void findMinMaxX(dataStruct *srcData) {
  if (srcData->matrix_3d.matrix != NULL) {
    srcData->minMaxX[0] = srcData->matrix_3d.matrix[0][0];
    srcData->minMaxX[1] = srcData->matrix_3d.matrix[0][0];
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      if (srcData->matrix_3d.matrix[i][0] > srcData->minMaxX[1]) {
        srcData->minMaxX[1] = srcData->matrix_3d.matrix[i][0];
      } else if (srcData->matrix_3d.matrix[i][0] < srcData->minMaxX[0]) {
        srcData->minMaxX[0] = srcData->matrix_3d.matrix[i][0];
      }
    }
  }
}

void findMinMaxY(dataStruct *srcData) {
  if (srcData->matrix_3d.matrix != NULL) {
    srcData->minMaxY[0] = srcData->matrix_3d.matrix[0][1];
    srcData->minMaxY[1] = srcData->matrix_3d.matrix[0][1];
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      if (srcData->matrix_3d.matrix[i][1] > srcData->minMaxY[1]) {
        srcData->minMaxY[1] = srcData->matrix_3d.matrix[i][1];
      } else if (srcData->matrix_3d.matrix[i][1] < srcData->minMaxY[0]) {
        srcData->minMaxY[0] = srcData->matrix_3d.matrix[i][1];
      }
    }
  }
}

void findMinMaxZ(dataStruct *srcData) {
  if (srcData->matrix_3d.matrix != NULL) {
    srcData->minMaxZ[0] = srcData->matrix_3d.matrix[0][2];
    srcData->minMaxZ[1] = srcData->matrix_3d.matrix[0][2];
    for (int i = 0; i < srcData->count_of_vertexes; i++) {
      if (srcData->matrix_3d.matrix[i][2] > srcData->minMaxZ[1]) {
        srcData->minMaxZ[1] = srcData->matrix_3d.matrix[i][2];
      } else if (srcData->matrix_3d.matrix[i][2] < srcData->minMaxZ[0]) {
        srcData->minMaxZ[0] = srcData->matrix_3d.matrix[i][2];
      }
    }
  }
}

void freeData(dataStruct *srcData) {
  s21_remove_matrix(&(srcData->matrix_3d));
  for (int i = 0; i < srcData->count_of_facets; i++) {
    free(srcData->polygons[i].vertexes);
    srcData->polygons[i].num_of_ver_in_facets = 0;
  }
  free(srcData->polygons);
  srcData->polygons = NULL;
  srcData->count_of_facets = 0;
  srcData->count_of_vertexes = 0;
}