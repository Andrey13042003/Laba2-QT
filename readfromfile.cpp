#include <readfromfile.h>

//чтение строк из файла
char** readFromfile(FILE* file, size_t *lines){
    char line[BUFFER_SIZE];
    size_t count = NUM_OF_LINES;
    size_t max_size = MAX_SIZE;
    char** data = (char**)malloc(sizeof(char*) * max_size);
    if(data != NULL) {
        while(fgets(line, BUFFER_SIZE, file)){//line - строка для записи результата, BUFFER_SIZE - максимальное количество байт, file - файловый объект для чтения данных
            if(count >= max_size - 1){
                max_size *= 2;
                char** data = (char**)realloc(data, sizeof(char*) * max_size);
                if(data == NULL){
                    for(size_t i = 0; i < max_size + 1; i++){
                        free(data[i]);
                    }
                    free(data);
                    break;
                }
            }
            size_t lineLen = strlen(line);
            data[count] = (char*)calloc(sizeof(char), lineLen);
            strncpy(data[count], line, lineLen - 1);
            count++;
        }
        *lines = count;
    }

    return data;//возвращаем массив строк
}

//разбиваем строку на массив слов
char** stringSplit(char* crudeData, size_t* box, const char sign){ //получает на вход строку, которую будет разбивать на массив строк, переменную, в которую запишется количество столбцов(в функцию не копируется значение, а передается сама переменная), и парметр, по которому будет разделяться строка(в нашем случае запятая)
    size_t count = NUM_OF_COLOUMNS; //изначальное количество столбцов, которое условно равно 0  в начале
    char* tmp = crudeData; //указатель на строку, которую мы передали
    char** result = 0; //массив строк, в который будет записываться наша поделённая строка
    while(*tmp){ //пока строка не закончилась делаем
        if(sign == *tmp){ //здесь мы смотрим, равен наш символ запятой
            count++; //если да, то прибавляем 1
        }
        tmp++; //смещаемся на следующий символ
    }
    *box = count + 1; //количество столбцов которое мы посчитали
    count++; //увеличиваем на один, чтобы выделилась память под нужное количество слов
    result = (char**)malloc(sizeof(char*) * count); //выделяем память под массив строк
    if(result != NULL){ //если память выделилась - начинаем
        size_t indx = 0; //этот индекс нужен, чтобы для каждой строки в массиве строк, выделять память (типо сначала result[0], result[1] .... result[count])
        char *token = crudeData; //указатель на переданную строку
        for(char *ending = (char*)strchr(token, sign); //здесь мы ищем первое вхождение запятой в строку
        ending; //пока строка не закончится
         token = ending + 1, ending = (char*) strchr(token, sign), indx++) //смещаемся на следующий элемент после запятой, при этом ending ищет следующую запятую, result переходит на слудующею строку
        {
            *(result + indx) = (char*)calloc(sizeof(char), ending - token + 1); //выделяем память под строку в массиве строк. ending - token + 1 это память под слово от начала до первой запятой, от первой запятой до второй и так далее
            if(result + indx == NULL){ //если память не выделилась, то сообщаешь об ошибке
                printf("Ошибка выделения памяти");
                free(result + indx);
                return 0;
            }
            strncpy(*(result + indx), token, ending - token); //переносишь в массив строк слово
        }
        result[indx + 1] = strdup(token);  //это функция вроде переопределяет память, нужно посмотреть(дублируем строку)
        result[indx + 1] = 0; //ставишь последним символом в массив строк нулевой символ
    }
    return result; //возвращение массива строк
}

//сортировка данных, чтобы остался один регион
FuncReturningValue* sortingByRegion(FuncReturningValue* tmp, const char* regionnametmp){
    size_t cursor = CURSOR_REGION; //cursor = 0
    for(size_t i = 0; i < tmp->lines - 1; i++){
        if(!strcmp(tmp->data[i][REG_COLUMT_NUM], regionnametmp)){//сравниваем строки
            tmp->data[cursor++] = tmp->data[i];
        } else
            clean2DArray(tmp->data[i], tmp->coloumns);
    }
    tmp->lines = cursor;

    return tmp;
}
