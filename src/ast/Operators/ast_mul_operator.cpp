#include "Operators/ast_mul_operator.hpp"

MulOperator::MulOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void MulOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
{
    if(type == "int" || type == "unsigned")
    {
    //Executes left branch into leftReg, executes right branch into rightReg
    int leftReg = ExecuteLeft(output, program_data, destReg, type);
    if(branches[1]->isFunctionCall() == true)
    {
        output << "sw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
    }
    int rightReg = ExecuteRight(output, program_data, destReg, type);
    if(branches[1]->isFunctionCall() == true)
    {
        output << "lw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
    }
    //Adds them together into destReg
    output << "mul $" << destReg << ", $" << leftReg << ", $" << rightReg << std::endl;
    //Sets leftreg and rightreg unused so they can be reused
    program_data.SetRegisterUnused(leftReg);
    program_data.SetRegisterUnused(rightReg);
    }
    else if(type == "float")
    {
    int leftReg = ExecuteLeft(output, program_data, destReg, type);
    if(branches[1]->isFunctionCall() == true)
    {
        output << "s.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
    }
    int rightReg = ExecuteRight(output, program_data, destReg, type);
    if(branches[1]->isFunctionCall() == true)
    {
        output << "l.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
    }
    //Adds them together into destReg
    output << "mul.s $f" << destReg << ", $f" << leftReg << ", $f" << rightReg << std::endl;
    //Sets leftreg and rightreg unused so they can be reused
    program_data.SetRegisterUnused(leftReg);
    program_data.SetRegisterUnused(rightReg);
    }
}
