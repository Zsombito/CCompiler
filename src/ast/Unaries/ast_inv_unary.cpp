#include "Unaries/ast_inv_unary.hpp"

InvOperator::InvOperator(NodePtr operand) 
{
    branches.push_back(operand);
}

void InvOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int operandReg = ExecuteOperand(output, program_data, destReg, type);

    output << "nor $" << destReg << ", $" << operandReg << ", $" << operandReg << std::endl;

    program_data.SetRegisterUnused(operandReg);
}