
#include <iostream>
#include <vector>
#include <memory>

#include "storage.h"

void Storage::addBlock(std::shared_ptr<Block> block) {
    blocks.push_back(block);
}

int Storage::getNumBlocks() {
    return blocks.size();
}

int Storage::getNumRecords() {
    int numRecords = 0;

    for (int i=0; i < getNumBlocks(); i++){
        numRecords += blocks[i]->getNumRecords();
    }
    return numRecords;
}

void Storage::writeBack(std::string dataPath) {
    std::ofstream outfile;
    outfile.open(dataPath);
    // std::cout << "Writing file..."<<std::endl;

    if (!outfile) {
        std::cout << "Error in writing the file" <<std::endl;
        exit(1);
    }else {
        // std::cout << "File sucessfully opened, processing file ..."<< std::endl;
    }

    for (auto p = this->blocks.begin(); p != this->blocks.end(); p++){
        for (auto q = (*p)->records.begin(); q != (*p)->records.end(); q++){
            outfile << (*q).toString();
            outfile << std::endl;
        }
    }
    outfile.close();
    // std::cout << "Finishing writing file..." << std::endl;
}







