#include "Unaries/ast_unary_master.hpp"

int Unary::ExecuteOperand(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, type);
    int regNumber = program_data.GetEmptyRegister();
    if(type != "float")
        output << "move $" << regNumber << ", $" << destReg << std::endl;
    else
        output << "mov.s $f" << regNumber << ", $f" << destReg << std::endl;
    return regNumber;
}
