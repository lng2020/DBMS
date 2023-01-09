#ifndef _record
#define _record

#include "basic_lib_header.h"

class Record {
public:

    std::string pk; //主键
    std::vector<std::string> recordData; //record数据
    Record();
    Record(std::vector<std::string>);
    Record(std::string);
    void setRecord(std::vector<std::string>);
    std::string toString();
};

#endif