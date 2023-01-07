#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include "query.h"
#include "db.h"
using namespace std;

void judge(string str[])
{
	string signTree = str[0].substr(0, 3); //通过前三位初步判断语句类型
	signTree = toUpper(signTree);
	// DDL
	int Num = 0;
	if (signTree == "CRE") //创建表或者数据库
	{
		string temstr = toUpper(str[0]);
		if (temstr.find("DATABASE") != string::npos)
		{
			//变量定义
			string dbName; //表名

			char *cstr = new char[str[0].length() + 1]; //首行读入
			strcpy_s(cstr, str[0].length() + 1, str[0].c_str());

			//通过空格进行分割
			char *ptr = NULL, *token = NULL;
			const char *seps = " ";
			token = strtok_s(cstr, seps, &ptr);
			while (token != NULL)
			{
				string temtoken = toUpper(token);
				if (temtoken == "CREATE" || temtoken == "DATABASE")
					token = strtok_s(NULL, seps, &ptr);
				else
				{
					dbName = token;
					break;
				}
			}
			createDatabase(dbName);
			//
		}
		else
		{

			while (str[Num][0]!= ')')
			{
				Num++;
			}
			//变量定义
			string tableName, dbName; //表名
			vector<Field> fields;	  //所有列

			char *cstr = new char[str[0].length() + 1]; //首行读入
			strcpy_s(cstr, str[0].length() + 1, str[0].c_str());

			//通过空格进行分割
			char *ptr = NULL, *token = NULL;
			const char *seps = " ";
			token = strtok_s(cstr, seps, &ptr);
			while (token != NULL)
			{
				string temtoken = toUpper(token);
				if (temtoken == "CREATE" || temtoken == "TABLE")
					token = strtok_s(NULL, seps, &ptr);
				else
				{
					tableName = token;
					break;
				}
			}
			//读取列
			for (int i = 1; i <= Num; i++)
			{
				Field tempfield;
				char *cstr = new char[str[i].length() + 1]; //每行读入
				strcpy_s(cstr, str[i].length() + 1, str[i].c_str());
				if (i == Num)
				{
					//获取数据库名
					strtok_s(cstr, seps, &ptr);
					strtok_s(NULL, seps, &ptr);
					dbName = strtok_s(NULL, seps, &ptr);
					break;
				}
				//通过空格进行分割
				char *ptr = NULL, *token = NULL;
				const char *seps = " ";
				std::string::size_type sz; // alias of size_t

				tempfield.FieldName = strtok_s(cstr, seps, &ptr);
				tempfield.FieldType = strtok_s(NULL, seps, &ptr);
				tempfield.Size = std::stoi(strtok_s(NULL, seps, &ptr), &sz);
				tempfield.Key = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
				tempfield.NullFlag = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
				tempfield.ValidFlag = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
				fields.push_back(tempfield);
			}
			cout << dbName;
			cout << tableName;
			createTable(dbName, tableName, fields);
		}
	}
	else if (signTree == "DRO") //删除表
	{
		string tableName; //表名
		string dbName;

		char *cstr = new char[str[0].length() + 1]; //首行读入
		strcpy_s(cstr, str[0].length() + 1, str[0].c_str());

		//通过空格进行分割
		char *ptr = NULL, *token = NULL;
		const char *seps = " ";
		token = strtok_s(cstr, seps, &ptr);
		while (token != NULL)
		{
			string temtoken = toUpper(token);
			if (temtoken == "DROP" || temtoken == "TABLE")
				token = strtok_s(NULL, seps, &ptr);
			else
			{
				tableName = token;
				break;
			}
		}
		strtok_s(NULL, seps, &ptr);

		//数据库名
		dbName = strtok_s(NULL, seps, &ptr);
		dropTable(dbName, tableName);
	}
	else if (signTree == "EDI") //编辑表
	{
		string tableName;	  //表名
		string dbName;		  //数据库名
		vector<Field> fields; //所有列

		char *cstr = new char[str[0].length() + 1]; //首行读入
		strcpy_s(cstr, str[0].length() + 1, str[0].c_str());

		//通过空格进行分割
		char *ptr = NULL, *token = NULL;
		const char *seps = " ";
		token = strtok_s(cstr, seps, &ptr);
		while (token != NULL)
		{
			string temtoken = toUpper(token);
			if (temtoken == "EDIT" || temtoken == "TABLE")
				token = strtok_s(NULL, seps, &ptr);
			else
			{
				tableName = token;
				break;
			}
		}
		//读取列
		Field tempfield;
		strcpy_s(cstr, str[1].length() + 1, str[1].c_str());

		//通过空格进行分割
		ptr = NULL, token = NULL;

		std::string::size_type sz; // alias of size_t

		//属性
		tempfield.FieldName = strtok_s(cstr, seps, &ptr);
		tempfield.FieldType = strtok_s(NULL, seps, &ptr);
		tempfield.Size = std::stoi(strtok_s(NULL, seps, &ptr), &sz);
		tempfield.Key = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
		tempfield.NullFlag = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
		tempfield.ValidFlag = bool(std::stoi(strtok_s(NULL, seps, &ptr), &sz));
		fields.push_back(tempfield);

		strtok_s(NULL, seps, &ptr);
		strtok_s(NULL, seps, &ptr);

		//数据库名
		cout << dbName << " " << tableName;
		dbName = strtok_s(NULL, seps, &ptr);
		// editTable(dbName, tableName, fields);
	}
	else if (signTree == "REN") //重命名表
	{
		string tableOldName, tableNewName; //表名
		string dbName;					   //数据库名

		char *cstr = new char[str[0].length() + 1]; //首行读入
		strcpy_s(cstr, str[0].length() + 1, str[0].c_str());

		//通过空格进行分割
		char *ptr = NULL, *token = NULL;
		const char *seps = " ";
		token = strtok_s(cstr, seps, &ptr);
		while (token != NULL)
		{
			string temtoken = toUpper(token);
			if (temtoken == "RENAME" || temtoken == "TABLE")
				token = strtok_s(NULL, seps, &ptr);
			else
			{
				//旧表名
				tableOldName = token;
				break;
			}
		}
		//新表名
		tableNewName = strtok_s(NULL, seps, &ptr);
		strtok_s(NULL, seps, &ptr);

		//数据库名
		dbName = strtok_s(NULL, seps, &ptr);

		renameTable(dbName, tableOldName, tableNewName);
	}

	// DML
	else if (signTree == "SEL") //查询数据
	{

	}
	else if (signTree == "UPD") //更新数据
	{

	}
	else if (signTree == "DEL") //删除数据
	{

	}
	else if (signTree == "INS") //插入数据
	{
        
	}
}


