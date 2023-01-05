#include "record.h"
#include "query.h"

class Data
{
public:
    std::vector<Record> records;
    bool insertRecord(Record);
    bool deleteRecord(Record);
    std::vector<Record> searchRecord(Condition);
    bool loadData(std::vector<std::string>);
};