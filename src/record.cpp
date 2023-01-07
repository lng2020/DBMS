#include "record.h"

void Record::setRecord(std::vector<std::string> _data) {
    this->recordData = _data;
    this->pk = recordData[0];
    this->size = recordData.size();
}

int Record::getRecordSize() {
    return this->size;
}

std::string Record::toString() {
    std::string res;
    for (auto p = this->recordData.begin(); p != this->recordData.end(); p++)
        res += *p;
    return res;
}
