#ifndef STRUCT_H
#define STRUCT_H

#define BUFFER_SIZE 256
#define NUM_MAX 0
#define NUM_MIN 1
#define NUM_MED 2
#define DEBAG -30000
#define HEADER 0
#define REG_COLUMT_NUM 1
#define CURSOR_REGION 0
#define NUM_OF_COLOUMNS 1
#define NUM_OF_LINES 0
#define MAX_SIZE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//исходные данные
typedef struct{
    char *filename; //имя файла
    char *regionname; //имя региона
    int numcolumns; //номер колонки
    char **table_headers; //заголовки таблицы
    char ***data; //данные
    size_t lines; //количество строк
    size_t coloumns; //количество столбцов
} FunctionArgument;

//выходные данные
typedef struct{
    char **table_headers;
    char ***data;
    double calculation_res[3]; //результаты вычисления
    size_t lines;
    size_t coloumns;
} FuncReturningValue;
#endif // STRUCT_H
