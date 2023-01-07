#include "table.h"
#include "query.h"
#include <sstream>

Table::Table(std::string tableName){
    this->TableName = tableName;
    this->FieldPath = "./data/db/" + tableName + "/Field.db";
    this->loadField();
    this->DataPath = "./data/db/" + tableName + "/Data.db";
    this->loadData();
};

// std::vector<std::map<Key, Value>> Table::DML_Select(Query query){
//     //利用条件筛选，返回一个record的vector
//     std::vector<Record> res = this->data.records;
//     for (std::vector<Condition>::iterator p = query.conditions.begin(); p != query.conditions.end(); p++){
//          res = Data(res).searchRecord(*p);
//     }
//     //对vector进行投影操作，返回投影后的vector
//     std::vector<std::map<Key, Value>> result;
//     for (std::vector<Record>::iterator p = res.begin(); p != res.end(); p++){
//         std::map<Key, Value> resultRecord;
//         for (std::vector<std::string>::iterator strPtr = query.fieldNames.begin(); strPtr != query.fieldNames.end(); strPtr++){
//             resultRecord[*strPtr] = (*p).kv[*strPtr]; 
//         }
//     }
//     return result;
// };

// bool Table::DML_Insert(Query query){
//     std::vector<Insert> inserts = query.inserts;
//     //如果有fieldName是主键
//     if(std::find(query.fieldNames.begin(), query.fieldNames.end(), this->pkName) != query.fieldNames.end()){
//         for (std::vector<Insert>::iterator p = inserts.begin(); p != inserts.end(); p++){
//             //若主键重复，返回
//             Condition condition = {this->pkName, true, (*p)[this->pkName], false};
//             if(this->data.searchRecord(condition).size()==0){
//                 return false;
//             }
//             //若主键无重复，生成一个record，插进data中
//             Record newRecord;
//             newRecord.pk = (*p)[this->pkName];
//             newRecord.kv = *p;
//             this->data.insertRecord(newRecord);
//         }
//     }
//     //如果没有fieldName是主键，那就分配一个主键
//     else {
//         for (std::vector<Insert>::iterator p = inserts.begin(); p != inserts.end(); p++){
//             std::string pk = this->data.findNewPk();
//             Record newRecord;
//             newRecord.kv = *p;
//             newRecord.kv[this->pkName] = pk;
//             this->data.insertRecord(newRecord);
//         }
//     }
//     return true;
// };

// bool Table::DML_Delete(Query query){
//     //利用条件筛选，若不存在满足的记录，直接返回
//     std::vector<Record> res = this->data.records;
//     for (std::vector<Condition>::iterator p = query.conditions.begin(); p != query.conditions.end(); p++){
//          res = Data(res).searchRecord(*p);
//     }
//     if (res.size() == 0){
//         return true;
//     }
//     //若存在记录，将这些记录删除
//     else {
//         for (std::vector<Record>::iterator p = res.begin(); p != res.end(); p++){
//             this->data.deleteRecord(*p);
//         }
//     }
//     return false;
// };

// bool Table::DML_Update(Query query){
//     //利用条件筛选，若不存在满足的记录，直接返回
//     std::vector<Record> res = this->data.records;
//     for (std::vector<Condition>::iterator p = query.conditions.begin(); p != query.conditions.end(); p++){
//          res = Data(res).searchRecord(*p);
//     }
//     if (res.size() == 0){
//         return true;
//     }
//     //若存在记录，生成一个更新后数据的记录vector，先调用Insert，再调用Delete
//     //更新记录
//     else {
//         for (std::vector<Record>::iterator p = res.begin(); p != res.end(); p++){
//             Record newRecord = *p;
//             for (std::map<Key, Value>::iterator ptr = query.updates.begin(); ptr != query.updates.end(); ptr++){
//                 std::map<Key, Value>::iterator it = newRecord.kv.find(ptr->first);
//                 if (it != newRecord.kv.end())
//                     it->second = ptr->second;
//             }
//             this->data.deleteRecord(*p);
//             this->data.insertRecord(newRecord);
//         }
//     }
//     return true;
// };

void Table::loadField()
{
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
        this->field.push_back(temp);
        if(temp.Key) this->pkName = temp.FieldName;
    }
};

void Table::loadData()
{
    // init storage
    Block initBlock;
    std::shared_ptr<Block> initBlockPtr = std::make_shared<Block>(std::move(initBlock));
    this->storage.addBlock(initBlockPtr);
    int lastBlockIndex = storage.getNumBlocks() - 1;

    // Read Input File
    std::ifstream infile;
    infile.open("data/data.tsv");
    std::cout << "Reading file... " << std::endl;

    if (!infile) {
        std::cout << "Error in reading the file" << std::endl;    // show error if can't read file
        exit(1);
    } else {
        std::cout << "File sucessfully opened, processing file ..." << std::endl;
    }

    // process data line by line
    std::string line;

    getline(infile, line);     // skip header

    while (getline(infile, line)) {
        Record newRecord;
        std::istringstream iss(line);
        std::string fieldData;
        // 第一个是主键
        getline(iss, fieldData, '\t');
        newRecord.recordData.push_back(fieldData);
        newRecord.pk = fieldData;
        while (getline(iss, fieldData, '\t')) {
            newRecord.recordData.push_back(fieldData);
        }
        // insert into block in storage if there is space in the last block
        std::shared_ptr<Block> blockPtr;
        if (this->storage.blocks[lastBlockIndex]->haveSpace()) {
            this->storage.blocks[lastBlockIndex]->addRecord(newRecord);
            blockPtr = this->storage.blocks[lastBlockIndex];
        } else {
            Block newBlock;
            newBlock.addRecord(newRecord);
            blockPtr = std::make_shared<Block>(newBlock);
            this->storage.addBlock(blockPtr);
            lastBlockIndex++;
        }

        this->data.InsertKey(newRecord.pk, blockPtr);
    }

    infile.close();     // close file

    std::cout << "Processing done... \n" << std::endl;
};