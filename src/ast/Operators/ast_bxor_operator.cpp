#include "Operators/ast_bxor_operator.hpp"

BXorOperator::BXorOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void BXorOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
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
    output << "xor $" << destReg << ", $" << leftReg << ", $" << rightReg << std::endl;
    //Sets leftreg and rightreg unused so they can be reused
    program_data.SetRegisterUnused(leftReg);
    program_data.SetRegisterUnused(rightReg);
}
