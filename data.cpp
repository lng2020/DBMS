#include "data.h"


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
bool Data::loadData(std::vector<std::string>){

};