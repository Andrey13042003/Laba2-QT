#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <struct.h>
#include <utilisation.h>

char** readFromfile(FILE* file, size_t *lines);
char** stringSplit(char* crudeData, size_t* box, const char sign);
FuncReturningValue* sortingByRegion(FuncReturningValue* tmp, const char* regionnametmp);
#endif // READFROMFILE_H
