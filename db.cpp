#include <fstream>
#include <sstream>
#include <io.h>
#include "db.h"

using namespace std;

// 创建新数据库
bool createDatabase(string databaseName)
{
    // 判断新数据库名是否已经存在
    string path = "./" + databaseName + "/";
    if (!access(path.c_str(), 0)) // 返回值为0时，文件存在
        return false;
    string command = "mkdir " + databaseName;
    system(command.c_str());
    return true;
}
// 删除数据库
bool dropDatabase(string databaseName)
{
    // 判断数据库名是否已经存在
    string path = "./" + databaseName + "/";
    if (access(path.c_str(), 0)) // 返回值不为0时，文件不存在
        return false;
    string command = "rd/s/q .\\" + databaseName;
    system(command.c_str());
    return true;
}
// 创建新表
bool createTable(string databaseName, string tableName, vector<Field> fields)
{
    // 默认输入的数据库名是存在的
    // 判断新表名是否存在
    string path = "./" + databaseName + "/" + tableName + "/";
    if (!access(path.c_str(), 0)) // 返回值为0时，文件存在
        return false;
    string command = "IF NOT EXIST ./" + databaseName + "/" + tableName + " (mkdir ./" + databaseName + "/" + tableName + ")";
    system(command.c_str());

    // 创建新表
    Table newTable;
    newTable.TableName = tableName;
    newTable.DataNum = 0;
    newTable.FieldNum = fields.size();

    // fieldMap pkName
    for (int i = 0; i < fields.size(); i++)
    {
        newTable.fieldMap[fields[i].FieldName] = fields[i];
        if (fields[i].Key)
            newTable.pkName = fields[i].FieldName;
    }
    // data 为空

    // path
    newTable.FieldPath = "./" + databaseName + "/" + tableName + "/Field.db";
    newTable.DataPath = "./" + databaseName + "/" + tableName + "/Data.db";

    // 写field.db文件
    ofstream outfile;
    outfile.open(newTable.FieldPath, ios::app);
    for (int i = 0; i < fields.size(); i++)
    {
        outfile << fields[i].Offset << "," << fields[i].FieldName << "," << fields[i].FieldType << "," << fields[i].Size << "," << fields[i].Key << "," << fields[i].NullFlag << "," << fields[i].ValidFlag << endl;
    }
    outfile.close();
    return true;
}

// 删除表
bool dropTable(string databaseName, string tablename)
{
    // 默认数据库名是合法的
    // 判断删除的表名是否存在
    string path = "./" + databaseName + "/" + tablename + "/";
    if (access(path.c_str(), 0)) // 返回值不为0时，文件不存在
        return false;
    string command = "rd/s/q .\\" + databaseName + "\\" + tablename;
    system(command.c_str());
    return true;
}

// 重命名表的名字
bool renameTable(string databaseName, string oldname, string newname)
{
    // 默认数据库名是合法的
    // 判断修改的旧表名是否存在
    string path = "./" + databaseName + "/" + oldname + "/";
    if (access(path.c_str(), 0)) // 返回值不为0时，文件不存在
        return -1;
    string command = "ren .\\" + databaseName + "\\" + oldname + " " + newname;
    system(command.c_str());
    return 0;
}