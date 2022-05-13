#include <utilisation.h>

//очищение char **
void clean2DArray(char **arr, size_t size){ //вместо arr и size мы будем передавать любые другие массивы/переменные
    if(arr == NULL)
        return;
    for(size_t i = 0; i < size; i++){
        if (arr[i] != NULL)
        {
            free(arr[i]);
            arr[i] = NULL;
        }
    }
    free(arr);
}

//очищение char ***
void clean3DArray(char ***arr, size_t sizeX, size_t sizeY){ // Где sizeX - размер char***, а sizeY - размер char **
    if(arr == NULL)
        return;
    for(size_t i = 0; i < sizeX; i++){
        clean2DArray(arr[i], sizeY);//arr[i] - это arr в случае с clean2DArray
    }
    free(arr);
}
//Следовательно, очищение char *** происходит таким образом, что мы движемся по массиву(1), в котором есть еще массивы(2), в которых также есть массивы(3)
// Сначала мы обращаемся к массиву(2), передаем его в clean2DArray, и тот в свою очередь очищает и сам этот массив(2), и его подмассивы(3).
//Затем, в функции clean3DArray засчет free(arr) мы очищаем непосредственно массив(1).
