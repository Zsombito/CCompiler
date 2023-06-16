#include "Others/ast_empty_scope.hpp"

EmptyScope::EmptyScope(NodePtr body)
{
    branches.push_back(body);
}
void EmptyScope::VariableParse(Program_Data &program_data, std::string functionName)
{
    program_data.EnterScope(functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.functions[functionName].scopes[scopeNumber].startLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].startLabel;
    program_data.functions[functionName].scopes[scopeNumber].endLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].endLabel;
    branches[0]->VariableParse(program_data, functionName);
    program_data.ExitScope(functionName);
    
}
void EmptyScope::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, type);
}