#include "Others/ast_continue.hpp"

Continue::Continue(){}

void Continue::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
}
void Continue::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    output << "b " << program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].startLabel << std::endl;
    output << "nop" << std::endl;
}