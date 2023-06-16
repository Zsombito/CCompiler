#include "Operators/ast_operator_master.hpp"


int Operator::ExecuteLeft(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(type == "int" || type == "unsigned" || type == "pointer" || type =="char")
    {
    //Executes left branch and puts the output into an empty register, freeing up destination register
    branches[0]->CodeGen(output, program_data, destReg, type);
    int regnumber = program_data.GetEmptyRegister();
    output << "move $" << regnumber << ", $" << destReg << std::endl;
    return regnumber;
    }
    else if(type == "float")
    {
    branches[0]->CodeGen(output, program_data, destReg, type);
    int regnumber = program_data.GetEmptyRegister();
    output << "mov.s $f" << regnumber << ", $f" << destReg << std::endl;
    return regnumber;
    }
}
int Operator::ExecuteRight(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(type == "int" || type == "unsigned" || type == "pointer" || type =="char")
    {
    //Executes right branch and puts the output into an empty register, freeing up destination register
    branches[1]->CodeGen(output, program_data, destReg, type);
    int regnumber = program_data.GetEmptyRegister();
    output << "move $" << regnumber << ", $" << destReg << std::endl; 
    return regnumber;
    }
    else if(type == "float")
    {
    branches[1]->CodeGen(output, program_data, destReg, type);
    int regnumber = program_data.GetEmptyRegister();
    output << "mov.s $f" << regnumber << ", $f" << destReg << std::endl; 
    return regnumber;
    }
}
