#include "math_operations.h"

double searchMax(double* data, size_t lines){
    double maximum = data[0];
    for(size_t i = 1; i < lines; i++){
        if (data[i] > maximum)
            maximum = data[i];
    }
    return maximum;
}

double searchMin(double* data, size_t lines){
    double minimum = data[0];
    for(size_t i = 1; i < lines; i++){
        if (data[i] < minimum)
            minimum = data[i];
    }
    return minimum;
}

double searchMed(double* data, size_t lines){
    double medium;
     for(size_t i = 0; i < lines; i++){
         for(size_t j = 0; j < lines - 1; j++){
             if(data[j] > data[j + 1]){
                 double tmp = data[j];
                 data[j] == data[j + 1];
                 data[j + 1] = tmp;
             }
         }
     }
     if (lines % 2 == 0){
         medium = (data[lines / 2] + data[lines / 2 - 1]) / 2;
     }
     else
         medium = data[lines / 2];
     return medium;
}
