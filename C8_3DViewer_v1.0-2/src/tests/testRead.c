#include "test.h"
START_TEST(test_success) {
    dataStruct srcData = {0};
    char *path = "cube.obj";
    matrix_t tmp = {0};
    s21_create_matrix(8, 3, &tmp);
    
    tmp.matrix[0][0] = -0.5;
    tmp.matrix[0][1] = -0.5;
    tmp.matrix[0][2] = 0.5;
    tmp.matrix[1][0] = 0.5;
    tmp.matrix[1][1] = -0.5;
    tmp.matrix[1][2] = 0.5;
    tmp.matrix[2][0] = -0.5;
    tmp.matrix[2][1] = 0.5;
    tmp.matrix[2][2] = 0.5;
    tmp.matrix[3][0] = 0.5;
    tmp.matrix[3][1] = 0.5;
    tmp.matrix[3][2] = 0.5;
    tmp.matrix[4][0] = -0.5;
    tmp.matrix[4][1] = 0.5;
    tmp.matrix[4][2] = -0.5;
    tmp.matrix[5][0] = 0.5;
    tmp.matrix[5][1] = 0.5;
    tmp.matrix[5][2] = -0.5;
    tmp.matrix[6][0] = -0.5;
    tmp.matrix[6][1] = -0.5;
    tmp.matrix[6][2] = -0.5;
    tmp.matrix[7][0] = 0.5;
    tmp.matrix[7][1] = -0.5;
    tmp.matrix[7][2] = -0.5;
    int facer[36] = {1,2,3,3,2,4,3,4,5,5,4,6,5,6,7,7,6,8,7,8,1,1,8,2,2,8,4,4,8,6,7,1,5,5,1,3};
	reader(&srcData, path);

    ck_assert_int_eq(srcData.count_of_facets, 12);
    ck_assert_int_eq(srcData.count_of_vertexes, 8);
    ck_assert_double_eq(srcData.minMaxX[0], -0.5);
    ck_assert_double_eq(srcData.minMaxX[1], 0.5);
    ck_assert_double_eq(srcData.minMaxY[0], -0.5);
    ck_assert_double_eq(srcData.minMaxY[1], 0.5);
    ck_assert_double_eq(srcData.minMaxZ[0], -0.5);
    ck_assert_double_eq(srcData.minMaxZ[1], 0.5);
    for (int i = 0; i < srcData.count_of_vertexes; i++){
        for(int j = 0; j < 3; j++){
            ck_assert_double_eq(srcData.matrix_3d.matrix[i][j],tmp.matrix[i][j]);
        }
    }
    int q = 0;
    
    for (int i = 0; i < srcData.count_of_vertexes; i++){
        for(int j = 0; j < srcData.polygons[i].num_of_ver_in_facets; j++){
            ck_assert_int_eq(srcData.polygons[i].vertexes[j],facer[q]);
            q++;
        }
    }
    freeData(&srcData);
    s21_remove_matrix(&tmp);
}
END_TEST

START_TEST(test_wrongPath) {
    dataStruct srcData = {0};
    char *path = "wrongPath.obj";
    reader(&srcData, path);
    ck_assert_int_eq(srcData.count_of_facets, 0);
    ck_assert_int_eq(srcData.count_of_vertexes, 0);
    ck_assert_double_eq(srcData.minMaxX[0], 0);
    ck_assert_double_eq(srcData.minMaxX[1], 0);
    ck_assert_double_eq(srcData.minMaxY[0], 0);
    ck_assert_double_eq(srcData.minMaxY[1], 0);
    ck_assert_double_eq(srcData.minMaxZ[0], 0);
    ck_assert_double_eq(srcData.minMaxZ[1], 0);
    freeData(&srcData);
}
END_TEST

START_TEST(test_wrongVert) {
    dataStruct srcData = {0};
    char *path = "wrong_cube.obj";
    matrix_t tmp = {0};
    s21_create_matrix(8, 3, &tmp);
    reader(&srcData, path);
    tmp.matrix[0][0] = -0.5;
    tmp.matrix[0][1] = -0.5;
    tmp.matrix[0][2] = 0.5;
    tmp.matrix[1][0] = 0.5;
    tmp.matrix[1][1] = -0.5;
    tmp.matrix[1][2] = 0.5;
    tmp.matrix[2][0] = -0.5;
    tmp.matrix[2][1] = 0.5;
    tmp.matrix[2][2] = 0.5;
    tmp.matrix[3][0] = 0.5;
    tmp.matrix[3][1] = 0.5;
    tmp.matrix[3][2] = 0.5;
    tmp.matrix[4][0] = -0.5;
    tmp.matrix[4][1] = 0.5;
    tmp.matrix[4][2] = -0.5;
    tmp.matrix[5][0] = 0.5;
    tmp.matrix[5][1] = 0.5;
    tmp.matrix[5][2] = -0.5;
    tmp.matrix[6][0] = -0.5;
    tmp.matrix[6][1] = -0.5;
    tmp.matrix[6][2] = -0.5;
    tmp.matrix[7][0] = 0.5;
    tmp.matrix[7][1] = -0.5;
    tmp.matrix[7][2] = -0.5;
    int facer[36] = {1,2,3,3,2,4,3,4,5,5,4,6,5,6,7,7,6,8,7,8,1,1,8,2,2,8,4,4,8,6,7,1,5,5,1,3};

    ck_assert_int_eq(srcData.count_of_facets, 12);
    ck_assert_int_eq(srcData.count_of_vertexes, 8);
    ck_assert_double_eq(srcData.minMaxX[0], -0.5);
    ck_assert_double_eq(srcData.minMaxX[1], 0.5);
    ck_assert_double_eq(srcData.minMaxY[0], -0.5);
    ck_assert_double_eq(srcData.minMaxY[1], 0.5);
    ck_assert_double_eq(srcData.minMaxZ[0], -0.5);
    ck_assert_double_eq(srcData.minMaxZ[1], 0.5);
    for (int i = 0; i < srcData.count_of_vertexes; i++){
        for(int j = 0; j < 3; j++){
            ck_assert_double_eq(srcData.matrix_3d.matrix[i][j],tmp.matrix[i][j]);
        }
    }
    int q = 0;
    
    for (int i = 0; i < srcData.count_of_vertexes; i++){
        for(int j = 0; j < srcData.polygons[i].num_of_ver_in_facets; j++){
            ck_assert_int_eq(srcData.polygons[i].vertexes[j],facer[q]);
            q++;
        }
    }
    freeData(&srcData);
    s21_remove_matrix(&tmp);
}
END_TEST

Suite *test_view(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[43m-=S21_VIEW=-\033[0m.");
    tc = tcase_create("add_tc");

  suite_add_tcase(s, tc);
    tcase_add_test(tc, test_success);
    tcase_add_test(tc, test_wrongPath);
    tcase_add_test(tc, test_wrongVert);
  return s;
}
