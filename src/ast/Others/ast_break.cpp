#include "Others/ast_break.hpp"

Break::Break(){}

void Break::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
}
void Break::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    output << "b " << program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel << std::endl;
    output << "nop" << std::endl;
}

