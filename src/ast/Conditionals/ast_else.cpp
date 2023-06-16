#include "Conditionals/ast_else.hpp"

IfElse::IfElse(NodePtr ifstat, NodePtr body)
{
    branches.push_back(ifstat);
    branches.push_back(body);
}
IfElse::IfElse(NodePtr ifstat)
{
    branches.push_back(ifstat);
}
void IfElse::VariableParse(Program_Data &program_data, std::string functionName)
{
    branches[0]->VariableParse(program_data, functionName);
    if(branches.size() != 1)
        if(branches[1] != NULL)
        {
            program_data.EnterScope(functionName);
            
            scopeNumber = program_data.functions[functionName].currentScope;
            program_data.functions[functionName].scopes[scopeNumber].startLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].startLabel;
            program_data.functions[functionName].scopes[scopeNumber].endLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].endLabel;
            branches[1]->VariableParse(program_data, functionName);
            program_data.ExitScope(functionName);
            
        }
}
void IfElse::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->branches[0]->CodeGen(output, program_data, destReg, type);
    std::string endLabel = program_data.LabelGenerator("endif");
    std::string elseLabel = program_data.LabelGenerator("elseLabel");
    output << "beq $0, $" << destReg << ", " << elseLabel << std::endl;
    output << "nop" << std::endl;

    if(branches[0]->branches[1] != NULL)
        branches[0]->branches[1]->CodeGen(output, program_data, destReg, type);
    output << "b " << endLabel << std::endl;
    output << "nop" << std::endl;
    output << elseLabel << ":" << std::endl;
    if(branches[1] != NULL)
        branches[1]->CodeGen(output, program_data, destReg, type);

    output << endLabel << ":" << std::endl;
}