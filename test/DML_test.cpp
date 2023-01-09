#include "../src/table.h"
#include "iostream"

int main(){
    Table table("STUDENT");
    //插入100条数据
    for (int i = 1 ; i <= 100 ; i++){
        table.DML_Insert(Record("student"+std::to_string(i)+"\t1\t1").recordData);
    }
    //删除前50条
    for (int i = 1; i <= 50 ; i++) {
        table.DML_Delete("student" + std::to_string(i));
    }
    //更新后50条
    for (int i = 76; i <= 100 ; i++){
        table.DML_Update(Record("student"+std::to_string(i)+"\t1\t0").recordData);
    }
    //查找3的倍数记录
    for (int i = 3; i <= 100; i += 3){
        std::vector<Record> res = table.DML_Select("student" + std::to_string(i));
        if (res.size() == 0){
            std::cout<<"cant found studnet"+ std::to_string(i)<<std::endl;
        }
        else {
            for ( auto p = res.begin(); p != res.end(); p++){
                std::cout<<(*p).toString();
                std::cout<<std::endl;
            }
        }
    }
    table.data.PrintStats();
    return 0;
}