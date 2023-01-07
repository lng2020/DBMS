#include <iostream>

#include "block.h"

void Block::addRecord(Record record) {
    records.push_back(record);
}

void Block::DeleteRecord(std::string key) {
    if (records.size() == 0) {
        std::cerr << "[Block::DeleteRecord] error, no record avaliable" << std::endl;
        return;
    }
    std::vector<int> deletePos;
    for (int i = records.size()-1; i >= 0; i--) {
        if (records[i].pk == key) {
            records.erase(records.begin() + i);
        }
    }
}

std::vector<Record> Block::getRecord(std::string key) {
    std::vector<Record> recordFound;
    for (Record record : records) {
        if (record.pk == key) {
            recordFound.push_back(record);
            // return record;
        }
    }
    // return empty record, but should not happen
    return recordFound;
}

int Block::getNumRecords() {
    return records.size();
}

void Block::toString() {
    for (Record r : records) {
        std::cout << r.toString() << " ,";
    }
    std::cout << std::endl;
}







