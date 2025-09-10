#include <iostream>
#include "src/TruthTables.h"

int main(){
    Table truth;
    truth.readfunc();
    truth.printTable("Jeff");
    //Used to input the amount of variables.
    /*
    std::cout<<"How many variables do you need?: ";
    int input;
    std::cin>>input;
    Table truth(input);
    Table truthtable(input);
    */
   // truth.writeTable();
    //truth.printTable();
    /*
    std::cout<<"\nTable 1: AND ::\n";
    truth.op_and();
    truth.printTable("yo");

    std::cout<<"\nTable 2: OR :: \n";
    truthtable.op_or();
    truthtable.printTable("yo!");
*/
    return 0;
}