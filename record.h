#include "basic_lib_header.h"

typedef std::string Value;

class Record {
public:
    int pk; //主键值
    std::vector<Value> values;
    bool loadRecord(std::string);
};