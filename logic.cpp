#include <logic.h>
#include <math_operations.cpp>

//единая точка входа
FuncReturningValue* entryPoint(FunctionType func, FunctionArgument* funcA){
    FuncReturningValue *result = NULL;
    switch(func)
    {
        case getDataFromFile:
            result = getDataFromFileDo(funcA->filename, funcA->regionname);
            break;
       case calculationData:
            result = calculationDataDo(funcA->data, funcA->lines, funcA->numcolumns);
            break;
       case cleanData:
            cleanAll(funcA);
            break;
       default:
            break;
    }
    return result;
}

//чтение данных из файла
FuncReturningValue* getDataFromFileDo(const char* filename, const char* regionname)
{
    FuncReturningValue* smt = (FuncReturningValue*)malloc(sizeof(FuncReturningValue));
    if(smt != NULL)
    {
        FILE* file = fopen(filename, "r");
        if(file != NULL)
        {
            size_t lines, box;//количество строк и столбцов
            char** crudeData = readFromfile(file, &lines);//создаем пустой массив строк, записываем туда неотсортированные строки из файла
            if(**crudeData == NULL)
            {
                clean2DArray(crudeData, lines);//очищаем массив строк
                free(smt);
            }
            else
            {
                char*** data = (char***)malloc(sizeof(char**) * (lines - 1));//выделяем память под данные
                if(data != NULL)//если данные из файла не равны говну
                {
                    for(size_t i = 0; i < lines - 1; i++){//двигаемся до последней строки(lines - количество строк)
                        *(data + i) = stringSplit(crudeData[i + 1], &box, ',');//строка = раздробленная строка на массив слов
                        if(*(data + i) == NULL){
                            clean3DArray(data, lines - 1, box);
                            break;
                        }
                    }
                    lines--;//для чего?

                    char** table_headers = stringSplit(*(crudeData + HEADER), &box, ',');//Разбиваем заголовки таблицы на массив слов
                    if(table_headers == NULL)
                        clean2DArray(table_headers, box);
                    clean2DArray(crudeData, lines);
                    (*smt).lines = lines;
                    (*smt).coloumns = box;
                    (*smt).table_headers = table_headers;
                    (*smt).data = data;

                    smt = sortingByRegion(smt, regionname);//сортируем данные, чтобы остался один регион

                    fclose(file);//закрываем файл
                }
                else{
                    clean3DArray(data, lines - 1, box);
                    free(smt);
                }
            }
        }else{
            fclose(file);
            free(smt);
        }
    }
    else
        free(smt);

    return smt;//остается один регион
}

//вычисление данных таблицы
FuncReturningValue* calculationDataDo(char*** data, size_t lines, int numcolumn){ //данные, количество строк, номер колонки
    FuncReturningValue* smt = (FuncReturningValue*)malloc(sizeof(FuncReturningValue));
    if(smt != NULL){
        double* tmp = convertDouble(data, lines, numcolumn);//преобразуем в тип данных double
        smt->calculation_res[NUM_MAX] = searchMax(tmp, lines);//записываем в calculation_res[0] результат вычисления searchMax
        smt->calculation_res[NUM_MIN] = searchMin(tmp, lines);//tmp - массив чисел, которые мы взяли из выбранной колонки,
        smt->calculation_res[NUM_MED] = searchMed(tmp, lines);//которые мы отсортировали в math_operations.cpp
    }
    return smt;//возвращаем максимум/минимум/среднее значение
}

//преобразование строки в число типа double
double* convertDouble(char*** data, size_t lines, int numcolumn){
    double* tmp = (double*)malloc(sizeof(double) * lines);
    if(tmp != NULL){
        for(size_t i = 0; i < lines; i++){
            tmp[i] = atof(data[i][numcolumn - 1]);//atof - функция преобразования в double
        }
    }
    return tmp;
}

//очищаем данные
void cleanAll(FunctionArgument *arg) {//очищаем данные
    if(arg->filename != NULL) {
        free(arg->filename);
    } else if(arg->regionname != NULL) {
        free(arg->regionname);
    } else if(arg->data != NULL) {
        clean3DArray(arg->data, arg->lines, arg->coloumns);
    } else if(arg->table_headers != NULL) {
        clean2DArray(arg->table_headers, arg->coloumns);
    }
}


