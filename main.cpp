#include <iostream>
#include "src/TruthTables.h"

int main(){

    //Used to input the amount of variables.
    std::cout<<"How many variables do you need?: ";
    int input;
    std::cin>>input;
    Table truth(input);
    truth.writeTable();
    //truth.printTable();
    truth.printTable("yo");
    return 0;
}