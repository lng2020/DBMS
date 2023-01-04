#include "field.h"

class Record {
public:
    int pk; //主键
    std::vector<Field> fields;
};