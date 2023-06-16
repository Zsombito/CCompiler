#include "Pointer/ast_address_of.hpp"

Address::Address(NodePtr variable)
{
    branches.push_back(variable);
}
void Address::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    branches[0]->VariableParse(program_data, functionName);
}
void Address::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int variable_offset = -9;
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[0]->getName()) > 0)
        {
            
            variable_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->getName()].stack_offset;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    if(variable_offset != -9)
    {
        output << "addiu $" << destReg << ", $sp, " << variable_offset << std::endl; 
    }
    else
    {
        output << "lui $" << destReg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
        output << "addui $" << destReg  << ", $" << destReg << ", %lo(" << branches[0]->getName() << ")($" << destReg << ")" << std::endl;
    }
}