#include "record.h"

class Data {
    std::vector<Record> records;
    bool insertRecord(Record);
    bool deleteRecord(Record);
    bool searchRecord(Condition);
    bool loadData(std::vector<std::string>);
};