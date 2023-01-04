#ifndef basic_lib_header
#include "basic_lib_header.h"
#endif

class Field
{
public:
    std::string FieldName; // 字段名
    std::string FieldType; // 字段类型
    int Offset;            // 位置
    int Size;              // 字长
    bool Key;              // 该字段是否为KEY键
    bool NullFlag;         // 该字段是否允许为空
    bool ValidFlag;        // 该字段是否有效，可用于以后对表中该字段的删除
    Field *Next;
};
