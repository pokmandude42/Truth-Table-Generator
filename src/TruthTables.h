#ifndef TRUTHTABLES_H
#define TRUTHTABLES_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
class Table{//base truth table class.
    public:
    int varCount, rows;
    std::map<std::string, int> places;
    std::vector<std::string> varNames;
    std::vector<std::vector<bool>> truthtable={{true,false}};//Vector for truth table values.
    Table(){};
    Table(int input){//Gets the variable count and the appropriate amount of rows. Sets up truth table base. Constructor.
        varCount=input;
        rows=pow(2,varCount);
        expandTable();
        writeTable();//Immediately writes the base table values upon initialization of the object.
    };
    void expandTable(){
        for(int i=1;i<varCount;i++){//used to create proper amount of rows for truth table.
            std::vector<bool> temput={true};
            truthtable.push_back(temput);
        }
    }

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
              if(truthtable[i][j]){std::cout<<"T ";}//Uses T and F to make it easier to look at for true and false respectively.
              else {std::cout<<"F ";}  
            };
            std::cout<<std::endl;
        };
    }

    void printTable(std::string joke){//Alternate function for printing, testing traditional collumns.
        std::cout<< " Printing Truth Table! \n";
        std::vector<std::string> spacing;
        for(int y=0;y<truthtable.size();y++){
            std::cout<<varNames[y]<<"    ";
            int z=varNames[y].length();z=(z+1)/2;
            std::string tempspace="";
            for(int i=0;i<z;i++){
                tempspace=tempspace+" ";
            }
            if(varNames[y].length()>1){tempspace+=" ";}
            if(tempspace!=" "){
            spacing.push_back(tempspace);
            }
            else{spacing.push_back("");}
        }
        std::cout<<std::endl;
        for(int c=0;c<rows;c++){//Increments through every row. Row count is 2 to the power of the variable count.
            for(int u=0;u<truthtable.size();u++){//Increments and prints for each value in a row. Three overall collumns.
                if(truthtable[u][c]){std::cout<<"T    "<<spacing[u];}//Uses T and F for true and false because it is easier to look at visually.
                else {std::cout<<"F    "<<spacing[u];}
            };
            std::cout<<std::endl;
        }
    }

    void op_and(std::string varA, std::string varB, std::vector<int> varAmount){
        std::vector<bool> rowInsert={true,false};
        truthtable.push_back(rowInsert);
        int indexA=places[varA], indexB=places[varB];
        for(int j=0;j<rows;j++){
            bool tempbuddy=true;
            tempbuddy=tempbuddy&&truthtable[indexA][j];
            tempbuddy=tempbuddy&&truthtable[indexB][j];
            truthtable[truthtable.size()-1][j]=tempbuddy;
        }
        appendNames(varA,varB,"and");
    }

    void op_or(std::string varA, std::string varB, std::vector<int> varAmount){
        std::vector<bool> rowInsert={true,false};
        truthtable.push_back(rowInsert);
        int indexA=places[varA], indexB=places[varB];
        for(int j=0;j<rows;j++){
            bool tempbuddy=false;
            tempbuddy=tempbuddy||truthtable[indexA][j];
            tempbuddy=tempbuddy||truthtable[indexB][j];
            truthtable[truthtable.size()-1][j]=tempbuddy;
        }
        appendNames(varA, varB, "or");
    }

    void appendNames(std::vector<int> varAmount, std::string type){//Pushes Names for each collumn.
        std::string tempTitle="";
        for(int i=0;i<varAmount.size();i++){
            tempTitle=tempTitle+varNames[varAmount[i]];
            if(type=="and"){
                tempTitle=tempTitle+'&';
            }
            if(type=="or"){
                tempTitle=tempTitle+'|';
            }
        }
        tempTitle.pop_back();
        varNames.push_back(tempTitle);
    }
    
    void appendNames(std::string varA, std::string varB, std::string type){//Create a collumn title using strings
        std::string tempTitle="";
        tempTitle=tempTitle+varA;
        if(type=="and"){
            tempTitle=tempTitle+'&';
        }
        if(type=="or"){
            tempTitle=tempTitle+'|';
        }
        tempTitle=tempTitle+varB;
        varNames.push_back(tempTitle);
    }

    void readfunc(){//Function to interpret and use inputs
        std::string logicLine,inParenthesis;
        std::vector<std::string> vecInParenthesis;
        int parenthesisCount=0;//Keeps count of amount of parenthesis
        std::cout<<"What would you like to input?: (& is AND, | is OR. letters are variable. Parenthesis work.)";
        std::cin>>logicLine;
        bool parenthesis=false,parenthOp=false;
        std::vector<int> opLine;//Vector of integers to hold which lines are operators.
        std::vector<std::vector<int>>vecParOpline;
        std::vector<int> varNumber;
        int VarOverload=0, tempVarCount=0;//Will be the amount of variables read from the function here.
        for(int i=0; i<logicLine.length();i++){//Read each character and act accordingly.
            if(logicLine[i]=='('){
                parenthesis=true;
            }
            if(logicLine[i]==')'){
                vecInParenthesis[parenthesisCount].push_back(')');
                parenthesis=false;
                parenthesisCount++;
                if(logicLine[i+1]){
                    if(logicLine[i+1]=='&'||logicLine[i+1]=='|'){
                        parenthOp=true;
                    }
                }
            }
            if(parenthesis==true){
                if(logicLine[i]!='&'&&logicLine[i]!='|'&&logicLine[i]!='('&&logicLine[i]!=')'){
                    std::string tempcomp=" ";
                    tempcomp[0]=logicLine[i];
                    if(places.count(tempcomp)==1){//Tests if variable already exists.
                     continue;   
                    }
                    else{
                        VarOverload++;
                std::string tempString="a";tempString[0]=logicLine[i];
                varNames.push_back(tempString);//Pushes each variable name into the varNames vector.
                tempVarCount++;
                varNumber.push_back(tempVarCount-1);//Loads the index for the variable in the truthtable into this vector.
                places[tempString]=(tempVarCount-1);//Loads Variable index into Dictionary
                    }
                
            }

            else if(logicLine[i]=='&'||logicLine[i]=='|'){//Tests if the current characters is an operator.
                if(vecParOpline.size()!=(parenthesisCount+1))
                {vecParOpline.resize(parenthesisCount+1);}
                vecParOpline[parenthesisCount].push_back(i);
            }
            inParenthesis.push_back(logicLine[i]);
            if(vecInParenthesis.size()!=(parenthesisCount+1)){//
                vecInParenthesis.resize(parenthesisCount+1);
            }
            vecInParenthesis[parenthesisCount].push_back(logicLine[i]);//Pushes into parentehsis vector
            }//end parenthesis if
            else{
            if(logicLine[i]!='&'&&logicLine[i]!='|'&&logicLine[i]!='('&&logicLine[i]!=')'){
                std::string tempcomp=" ";
                    tempcomp[0]=logicLine[i];
                    if(places.count(tempcomp)==1){//Tests if variable already exists.
                     continue;   
                    }
                    else{
                VarOverload++;
                std::string tempString="a";tempString[0]=logicLine[i];
                varNames.push_back(tempString);//Pushes each variable name into the varNames vector.
                tempVarCount++;
                varNumber.push_back(tempVarCount-1);//Loads the index for the variable in the truthtable into this vector.
                places[tempString]=(tempVarCount-1);//Loads Variable index into Dictionary/map
            }
        }
            else if(logicLine[i]=='&'||logicLine[i]=='|'){//Tests if the current characters is an operator.
                opLine.push_back(i);
            }
        }//end else
        }
        varCount=VarOverload;
        rows=pow(2,varCount);
        expandTable();
        writeTable();
        if(vecInParenthesis.size()!=0){//Used to evaluate when parenthesis are involved
            for(int x=0;x<vecParOpline.size();x++){
                for(int i=0;i<vecParOpline[x].size();i++){
                    if(logicLine[vecParOpline[x][i]]=='|'){
                        std::string tempOne="a",tempTwo="a";
                        tempOne[0]=logicLine[vecParOpline[x][i]-1];
                        tempTwo[0]=logicLine[vecParOpline[x][i]+1];
                        op_or(tempOne,tempTwo,varNumber);

                    }
                    else if(logicLine[vecParOpline[x][i]]=='&'){
                        std::string tempOne="a",tempTwo="a";
                        tempOne[0]=logicLine[vecParOpline[x][i]-1];
                        tempTwo[0]=logicLine[vecParOpline[x][i]+1];
                        op_and(tempOne,tempTwo,varNumber);
                    }
                }
            }
            if(parenthOp){//Used to compare parenthesis as a whole to another variable.
                
            }
        }//End if handling parenthesis

        
        for(int i=0;i<opLine.size();i++){//Test to see if I can have OR and AND in the same line with current implementation.
        if(logicLine[opLine[i]]=='|'){//Checks which operator opLine is pointing to. Formats response.
           std::string tempOne="a",tempTwo="a";
        tempOne[0]=logicLine[opLine[i]-1];
        tempTwo[0]=logicLine[opLine[i]+1];
           op_or(tempOne,tempTwo,varNumber);//This and the line above pass the strings around the operator to the dictionary
        }
        else if(logicLine[opLine[i]=='&']){//Formats response for and operations.
         std::string tempOne="a",tempTwo="a";
        tempOne[0]=logicLine[opLine[i]-1];
        tempTwo[0]=logicLine[opLine[i]+1];
            op_and(tempOne,tempTwo,varNumber);
        }
    
};
    }
};
/*For single variable and parenthesis function, if blah[i+-1]=')' etc., have it go backwards/fowards till it hits the other parenthesis
and use everything in between as a string to search in the Places map for the true/false table in the truthtable vector.
*/
//Use the Places map to load the index/values for parenthesis functions.
#endif