#include "Unaries/ast_not_unary.hpp"

NotOperator::NotOperator(NodePtr operand) 
{
    branches.push_back(operand);
}

void NotOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int operandReg = ExecuteOperand(output, program_data, destReg, type);
    std::string label_one = program_data.LabelGenerator("label_one");
    std::string label_end = program_data.LabelGenerator("label_end");
    output << "beq $" << operandReg << ", $0, " << label_one << std::endl;
    output << "nop" << std::endl;
    output << "move $" << destReg << ", $0" << std::endl;
    output << "b " << label_end << std::endl;
    output << "nop" << std::endl;
    output << label_one << ":" << std::endl;
    output << "addiu $" << destReg << ", $" << destReg << ", 1" << std::endl;
    output << label_end << ":" << std::endl;

    program_data.SetRegisterUnused(operandReg);
}