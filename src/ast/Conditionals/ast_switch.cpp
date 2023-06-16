#include "Conditionals/ast_switch.hpp"

Switch::Switch(NodePtr variable, NodePtr body)
{
    branches.push_back(variable);
    branches.push_back(body);
}

void Switch::VariableParse(Program_Data &program_data, std::string functionName)
{
    program_data.EnterScope(functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
    branches[0]->VariableParse(program_data, functionName);
    if(branches[1] != NULL)
        branches[1]->VariableParse(program_data, functionName);
    program_data.ExitScope(functionName);
}
void Switch::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string endLabel = program_data.LabelGenerator("endLabel");
    program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel = endLabel;
    branches[0]->CodeGen(output, program_data, destReg, type);
    if(branches[1] != NULL)
        branches[1]->CodeGen(output, program_data, destReg, branches[0]->getType(program_data));
    output << endLabel << ":" << std::endl;
}