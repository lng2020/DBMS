#include "record.h"

bool Record::loadRecord(std::string str, std::string pkName){
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        Record newRecord;
        token = str.substr(0, pos);
        std::string kv_delimiter = ":";
        size_t kv_pos = token.find(kv_delimiter);
        std::string key = token.substr(0, kv_pos);
        std::string value = token.substr(kv_pos+1);
        if ( key == pkName) {
            newRecord.pk = value;
        }
        newRecord.kv.insert(key, value);
        str.erase(0, pos + delimiter.length());
    }
};