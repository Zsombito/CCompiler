#include "Unaries/ast_neg_unary.hpp"

NegOperator::NegOperator(NodePtr operand) 
{
    branches.push_back(operand);
}

void NegOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string realType = branches[0]->getType(program_data);
    if(realType != "float")
    {
        int operandReg = ExecuteOperand(output, program_data, destReg, branches[0]->getType(program_data));

        output << "sub $" << destReg << ", $0, $" << operandReg << std::endl;

        program_data.SetRegisterUnused(operandReg);
    }
    else
    {
        int operandReg = ExecuteOperand(output, program_data, destReg, branches[0]->getType(program_data));

        output << "neg.s $f" << destReg << ", $f" << operandReg << std::endl;

        program_data.SetRegisterUnused(operandReg);
    }
}