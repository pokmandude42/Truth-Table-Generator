#ifndef TRUTHTABLES_H
#define TRUTHTABLES_H

#include <iostream>
#include <cmath>
#include <vector>
class Table{//base truth table class.
    public:
    int varCount, rows;
    std::vector<std::vector<bool>> truthtable={{true,false}};//Vector for truth table values.
    Table(){};
    Table(int input){//Gets the variable count and the appropriate amount of rows. Sets up truth table base. Constructor.
        varCount=input;
        for(int i=1;i<varCount;i++){//used to create proper amount of rows for truth table.
            std::vector<bool> temput={true};
            truthtable.push_back(temput);
        }
        rows=pow(2,varCount);
    };
    void writeTable(){//Writes the variable true/false values based on the variable count.
        int sequence=1,measure=0;//Sequence for the length of True/False segments. Measure to compare with sequence.
        for(int i=(varCount-1);!(i<0);i=i-1){//Counts from varcount-1 down to zero. For index values.
            bool value=true;//Ensure each collumn starts on true.
            measure=0;
            for(int j=0;j<rows;j++){//sets value and increments measure. If measure is as long as sequence, flips boolean inputs, then resets the length of measure.
                if(measure==sequence){
                    if(value){
                        value=false;
                    }
                    else if(!value){
                        value=true;
                    }
                    measure=0;
                }
                truthtable[i][j]=value;
                measure++;
            }
            sequence=sequence*2;//Doubles sequence according to the length of true false sequences.
        };
    }

    void printTable(){//Function to print the truth table. 
        std::cout<<" Printing Truth Table! \n";
        for(int i=0;i<truthtable.size();i++){//Prints the values of truth table. Uses the size() function for when the table gets appended to with the operations.
            for(int j=0;j<rows;j++){
              if(truthtable[i][j]){std::cout<<"T ";}
              else {std::cout<<"F ";}  
            };
            std::cout<<std::endl;
        };
    }//Could be improved upon by taking the dynamic row count of truth tables.
    void printTable(std::string joke){//Alternate function for printing, testing traditional collumns.
        std::cout<< " Printing Truth Table! \n";
        for(int y=0;y<truthtable.size();y++){
            std::cout<<(y+1)<<" ";
        }
        std::cout<<std::endl;
        for(int c=0;c<rows;c++){//Increments through every row. Makes 8 rows for three collumns.
            for(int u=0;u<truthtable.size();u++){//Increments and prints for each value in a row. Three overall collumns.
                if(truthtable[u][c]){std::cout<<"T ";}
                else {std::cout<<"F ";}
            };
            std::cout<<std::endl;
        }
    }

    void op_and(){//Uses and to compare all variables in the table.
        std::vector<bool> rowInsert={true, false};
        truthtable.push_back(rowInsert);
        for(int i=0;i<rows;i++){
            bool tempbuddy=true;
            for(int j=0;j<=truthtable.size()-2;j++){//This loop should decide if all of them are true (and).
                tempbuddy=tempbuddy&&truthtable[j][i];
            }
           //truthtable[truthtable.size()-1][i]=truthtable[truthtable.size()-3][i]&&truthtable[truthtable.size()-2][i];
           truthtable[truthtable.size()-1][i]=tempbuddy;
        }


    };
    
};


#endif