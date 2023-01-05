#include "record.h"
#include "query.h"

class Data
{
public:
    Data(std::vector<Record>); 
    std::vector<Record> records;
    bool insertRecord(Record);
    bool deleteRecord(Record);
    std::vector<Record> searchRecord(Condition);
    std::string findNewPk();
    bool loadData(std::vector<std::string>);
};