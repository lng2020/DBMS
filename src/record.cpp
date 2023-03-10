#include "record.h"
#include "basic_lib_header.h"

Record::Record(){

}

Record::Record(std::string _recordData){
    std::istringstream iss(_recordData);
    std::string fieldData;
    // 第一个是主键
    getline(iss, fieldData, '\t');
    this->recordData.push_back(fieldData);
    this->pk = fieldData;
    while (getline(iss, fieldData, '\t'))
    {
        this->recordData.push_back(fieldData);
    }
}

void Record::setRecord(std::vector<std::string> _data) {
    this->recordData = _data;
    this->pk = recordData[0];
}

std::string Record::toString() {
    std::string res;
    for (auto p = this->recordData.begin(); p != this->recordData.end(); p++){
        res += *p;
        res += "\t";
    }
    return res;
}

Record::Record(std::vector<std::string> _recordData){
    this->pk = _recordData[0];
    this->recordData = _recordData;
}