#include "Conditionals/ast_ifstatements.hpp"

IfStatment::IfStatment(NodePtr condition, NodePtr executant)
{
    branches.push_back(condition);
    branches.push_back(executant);
}


void IfStatment::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    
}
void IfStatment::VariableParse(Program_Data &program_data, std::string functionName) 
{
    program_data.EnterScope(functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.functions[functionName].scopes[scopeNumber].startLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].startLabel;
    program_data.functions[functionName].scopes[scopeNumber].endLabel = program_data.functions[functionName].scopes[program_data.functions[functionName].scopes[scopeNumber].parentScopeId].endLabel;
    branches[0]->VariableParse(program_data,functionName);
    if(branches[1] != NULL)
    {
        
        branches[1]->VariableParse(program_data, functionName);

    }
    program_data.ExitScope(functionName);
    
    
    
}