#ifndef LOGIC_H
#define LOGIC_H

#include "struct.h"
#include "math_operations.h"
#include "utilisation.h"
#include "readfromfile.h"

enum FunctionType{
    getDataFromFile,
    calculationData,
    cleanData
};

FuncReturningValue* entryPoint(FunctionType func, FunctionArgument* funcA);
FuncReturningValue* getDataFromFileDo(const char* filename, const char* regionname);
FuncReturningValue* calculationDataDo(char*** data, size_t lines, int numcolumn);
double* convertDouble(char*** data, size_t lines, int numcolumn);
void cleanAll(FunctionArgument *arg);
#endif // LOGIC_H
