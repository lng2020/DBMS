#include "record.h"

void Record::setRecord(std::vector<std::string> _data) {
    this->recordData = _data;
    this->pk = recordData[0];
}

std::string Record::toString() {
    std::string res;
    for (auto p = this->recordData.begin(); p != this->recordData.end(); p++)
        res += *p;
    return res;
}
