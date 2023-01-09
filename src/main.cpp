#include "../src/table.h"
#include "iostream"

int main(){
    Table table("STUDENT");
    
    table.data.PrintStats();
    return 0;
}