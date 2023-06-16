#include "Operators/ast_and_operator.hpp"

AndOperator::AndOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void AndOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
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
    std::string label_zero = program_data.LabelGenerator("label_zero");
    std::string label_end = program_data.LabelGenerator("label_end");
    //Adds them together into destReg
    output << "beq $" << leftReg << ", $0, " << label_zero << std::endl;
    output << "nop" << std::endl;
    output << "beq $" << rightReg << ", $0, " << label_zero << std::endl;
    output << "nop" << std::endl;
    output << "addiu $" << destReg << ", $0, 1" << std::endl;
    output << "b " << label_end << std::endl;
    output << "nop" << std::endl;
    output << label_zero << ":" << std::endl;
    output << "move $" << destReg << ", $0" << std::endl;
    output << label_end << ":" << std::endl;

    //Sets leftreg and rightreg unused so they can be reused
    program_data.SetRegisterUnused(leftReg);
    program_data.SetRegisterUnused(rightReg);
}
