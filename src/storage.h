#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <vector>
#include <memory>

#include "block.h"

/*
Singleton structure representing the disk storage of a database system.
holds multiple blocks in memory, where each blocks holds multiple records.
*/

struct Storage {
    // Blocks in this record
    std::vector <std::shared_ptr<Block>> blocks;

    // Add a block
    void addBlock(std::shared_ptr<Block> block);

    // Get number of blocks
    int getNumBlocks();

    // get number of records
    int getNumRecords();

    void writeBack(std::string); //写回文件

};

#endif    // STORAGE_H_
