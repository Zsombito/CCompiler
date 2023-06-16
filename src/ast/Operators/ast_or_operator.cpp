#include "Operators/ast_or_operator.hpp"

OrOperator::OrOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void OrOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
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
    output << "add $" << destReg << ", $" << leftReg << ", $" << rightReg << std::endl;
    output << "slt $" << destReg << ", $0, $" << destReg << std::endl;

    //Sets leftreg and rightreg unused so they can be reused
    program_data.SetRegisterUnused(leftReg);
    program_data.SetRegisterUnused(rightReg);
}
