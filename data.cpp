#include "data.h"

Data::Data(std::vector<Record> records){
    this->records = records;
}

std::string Data::findNewPk() {
    std::vector<Record>::iterator p = this->records.begin();
    std::vector<Record>::iterator pNext = p++;
    while ( pNext->pk != std::to_string(std::stoi(p->pk) + 1)) {
        return std::to_string(std::stoi(p->pk) + 1);
    }
};

bool Data::insertRecord(Record record){
    this->records.push_back(record);
    return true;
};

bool Data::deleteRecord(Record record){
    for (std::vector<Record>::iterator p = this->records.begin(); p != this->records.end(); p++){
        if ( p->pk == record.pk){
            this->records.erase(p);
            return true;
        }
    }
    return false;
};

std::vector<Record> Data::searchRecord(Condition condition){
    if (condition.op1IsField == false && condition.op2IsField == false) {
        return this->records;
    }
    std::vector<Record> res;
    if (condition.op1IsField == true && condition.op2IsField == false) {
        for (std::vector<Record>::iterator p = this->records.begin(); p != this->records.end(); p++){
            if ( (p->kv)[condition.op1] == condition.op2){
                res.push_back(*p);
            }
        }
    }
    if (condition.op1IsField == false && condition.op2IsField == true) {
        for (std::vector<Record>::iterator p = this->records.begin(); p != this->records.end(); p++){
            if ( (p->kv)[condition.op2] == condition.op1){
                res.push_back(*p);
            }
        }
    }
    if (condition.op1IsField == true && condition.op2IsField == true) {
        for (std::vector<Record>::iterator p = this->records.begin(); p != this->records.end(); p++){
            if ( (p->kv)[condition.op2] == (p->kv)[condition.op1]){
                res.push_back(*p);
            }
        }
    }
    return res;
};


void Data::loadData(std::vector<std::string> data, std::string pkName){
    for (std::vector<std::string>::iterator p = data.begin(); p != data.end(); p++){
        Record newRecord;
        newRecord.loadRecord(*p, pkName);
        this->records.push_back(newRecord);
    } 
};