#include "table.h"
#include <sstream>
#include "basic_lib_header.h"

Table::Table(std::string tableName)
{
    std::string dbName = "1";
    std::cout << "init table" << std::endl;
    this->TableName = tableName;
    this->FieldPath = "./DBMS/" + dbName + tableName + "/Field.db";
    this->loadField();
    this->DataPath = "./DBMS/" + dbName + tableName + "/Data.db";
    this->loadData();
    std::cout << "end init table" << std::endl;
};

std::vector<Record> Table::DML_Select(std::string pk){
    std::vector<Record> res;
    std::vector<std::shared_ptr<Block>> pointers = this->data.Find(pk);
    for (auto p = pointers.begin(); p != pointers.end(); p++){
        std::vector<Record> temp = (*p)->getRecord(pk);
        res.insert( res.end(), temp.begin(), temp.end());
    }
    return res;
};

bool Table::DML_Insert(std::vector<std::string> recordData)
{
    Record newRecord(recordData);
    int lastBlockIndex = storage.getNumBlocks() - 1;
    std::shared_ptr<Block> blockPtr;
    if (this->storage.blocks[lastBlockIndex]->haveSpace())
    {
        this->storage.blocks[lastBlockIndex]->addRecord(newRecord);
        blockPtr = this->storage.blocks[lastBlockIndex];
    }
    else
    {
        Block newBlock;
        newBlock.addRecord(newRecord);
        blockPtr = std::make_shared<Block>(newBlock);
        this->storage.addBlock(blockPtr);
        lastBlockIndex++;
    }
    this->data.InsertKey(newRecord.pk, blockPtr);
};

bool Table::DML_Delete(std::string pk)
{
    this->data.DeleteKey(pk);
};

bool Table::DML_Update(std::vector<std::string> recordData){
    Record newRecord(recordData);
    std::string pk = recordData[0];
    this->data.DeleteKey(pk);
    this->DML_Insert(recordData);
};

void Table::loadField()
{
    std::cout << "loading Field" << std::endl;
    std::ifstream infile;
    infile.open(this->FieldPath, std::ios::in);

    while (!infile.eof())
    {
        Field temp;
        std::string str;
        getline(infile, str);
        // 转换成C中的char*
        char *cstr = new char[str.length() + 1]; // 首行读入
        strcpy_s(cstr, str.length() + 1, str.c_str());
        // 通过,进行分割
        const char *seps = ",";
        char *token = NULL;
        temp.FieldName = strtok(cstr, seps);
        temp.FieldType = strtok(NULL, seps);
        temp.Size = std::stoi(strtok(NULL, seps));
        temp.Key = bool(std::stoi(strtok(NULL, seps)));
        temp.NullFlag = bool(std::stoi(strtok(NULL, seps)));
        temp.ValidFlag = bool(std::stoi(strtok(NULL, seps)));
        this->fields.push_back(temp);
        if (temp.Key)
            this->pkName = temp.FieldName;
    }
    std::cout << "end loading field" << std::endl;
};

void Table::loadData()
{
    std::cout << "loading data" << std::endl;
    std::cout << "init storage" << std::endl;
    Block initBlock;
    std::shared_ptr<Block> initBlockPtr = std::make_shared<Block>(std::move(initBlock));
    this->storage.addBlock(initBlockPtr);
    int lastBlockIndex = this->storage.getNumBlocks() - 1;

    // Read Input File
    std::ifstream infile;
    infile.open(this->DataPath);
    std::cout << "Reading file... " << std::endl;

    if (!infile)
    {
        std::cout << "Error in reading the file" << std::endl; // show error if can't read file
        exit(1);
    }
    else
    {
        std::cout << "File sucessfully opened, processing file ..." << std::endl;
    }

    // process data line by line
    std::string line;

    getline(infile, line); // skip header

    while (getline(infile, line))
    {
        Record newRecord;
        std::istringstream iss(line);
        std::string fieldData;
        // 第一个是主键
        getline(iss, fieldData, '\t');
        newRecord.recordData.push_back(fieldData);
        newRecord.pk = fieldData;
        while (getline(iss, fieldData, '\t'))
        {
            newRecord.recordData.push_back(fieldData);
        }
        // insert into block in storage if there is space in the last block
        std::shared_ptr<Block> blockPtr;
        if (this->storage.blocks[lastBlockIndex]->haveSpace())
        {
            this->storage.blocks[lastBlockIndex]->addRecord(newRecord);
            blockPtr = this->storage.blocks[lastBlockIndex];
        }
        else
        {
            Block newBlock;
            newBlock.addRecord(newRecord);
            blockPtr = std::make_shared<Block>(newBlock);
            this->storage.addBlock(blockPtr);
            lastBlockIndex++;
        }

        this->data.InsertKey(newRecord.pk, blockPtr);
    }

    infile.close(); // close file

    std::cout << "Processing done... \n"
              << std::endl;
};

void Table::writeBack(){
    this->storage.writeBack(this->DataPath);
}