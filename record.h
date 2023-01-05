#include "basic_lib_header.h"

typedef std::string Value;
typedef std::string Key;

class Record {
public:
    std::string pk; //主键值
    std::map<Key, Value> kv;
    bool loadRecord(std::string);
};