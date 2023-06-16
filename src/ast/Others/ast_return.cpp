#include "Others/ast_return.hpp"

Return::Return(NodePtr value)
{
    branches.push_back(value);
}
void Return::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, program_data.functions[program_data.currentFunctionName].type);
    if(program_data.functions[program_data.currentFunctionName].type == "float")
        output << "mov.s $f0, $f" << destReg << std::endl;
    else
        output << "move $2, $" << destReg << std::endl;
    output << "move $sp, $fp" << std::endl;
    output << "lw $fp, " << (program_data.functions[program_data.currentFunctionName].stackSize-4) << "($sp)" << std::endl;
    if(program_data.functions[program_data.currentFunctionName].functionCalls.size() > 0)
    {
        output << "lw $ra, " << (program_data.functions[program_data.currentFunctionName].stackSize-12) << "($sp)" << std::endl;
    }
    output << "addiu $sp, $sp, " << program_data.functions[program_data.currentFunctionName].stackSize << std::endl;
    
    output << "j $31" << std::endl;
    output << "nop" << std::endl;
}