#include <fstream>
#include <sstream>
#include <io.h>
#include "db.h"

using namespace std;

// 创建新数据库
int createDatabase(string databaseName)
{
    // 判断新数据库名是否已经存在
    string path = "./" + databaseName + "/";
    if (!access(path.c_str(), 0)) // 返回值为0时，文件存在
        return -1;
    string command = "mkdir " + databaseName;
    system(command.c_str());
    return 0;
}
// 创建新表
int create(string databaseName, string tableName, vector<Field> fields)
{
    // 默认输入的数据库名是存在的
    // 判断新表名是否存在
    string path = "./" + databaseName + "/" + tableName + "/";
    if (!access(path.c_str(), 0)) // 返回值为0时，文件存在
        return -1;
    string command = "IF NOT EXIST ./" + databaseName + "/" + tableName + " (mkdir ./" + databaseName + "/" + tableName + ")";
    system(command.c_str());
    Table newTable;
    newTable.TableName = tableName;
    newTable.FieldNum = fields.size();
    newTable.FieldPath = "./" + databaseName + "/" + tableName + "/Field.db";
    newTable.DataPath = "./" + databaseName + "/" + tableName + "/Data.db";
    newTable.PFieldHead = &fields[0];
    newTable.PFieldTail = &fields[0];
    for (int i = 1; i < fields.size(); i++)
    {
        newTable.PFieldTail->Next = &fields[i];
        newTable.PFieldTail = newTable.PFieldTail->Next;
        if (i == fields.size() - 1)
        {
            newTable.PFieldTail->Next = NULL;
        }
    }
    // 写field.db文件
    ofstream outfile;
    outfile.open(newTable.FieldPath, ios::app);
    Field *Tail = newTable.PFieldHead;
    while (Tail != NULL)
    {
        outfile << Tail->FieldName << "," << Tail->FieldType << "," << Tail->Size << "," << Tail->Key << "," << Tail->NullFlag << "," << Tail->ValidFlag << endl;
        Tail = Tail->Next;
    }
    outfile.close();
    return 0;
}

// 删除表
int dropTable(string databaseName, string tablename)
{
    // 默认数据库名是合法的
    // 判断删除的表名是否存在
    string path = "./" + databaseName + "/" + tablename + "/";
    if (access(path.c_str(), 0)) // 返回值不为0时，文件不存在
        return -1;
    string command = "rd/s/q .\\" + databaseName + "\\" + tablename;
    system(command.c_str());
    return 0;
}

// 重命名表的名字
int renameTable(string databaseName, string oldname, string newname)
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