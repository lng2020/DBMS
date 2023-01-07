#ifndef BLOCK_H_
#define BLOCK_H_

#include <vector>
#include "record.h"

#define MAX_RECORD 1024

// Data structure defining a block holding many records
struct Block {
    // Records in this block
    std::vector<Record> records;

    // Add a record to this block
    void addRecord(Record record);

    void DeleteRecord(std::string key);

    // Get number of records in this block
    int getNumRecords();

    std::vector<Record> getRecord(std::string key);

    void toString();

    bool haveSpace() {
        if (records.size() < MAX_RECORD)
            return true;
        return false;
    }
};

#endif    // BLOCK_H_
