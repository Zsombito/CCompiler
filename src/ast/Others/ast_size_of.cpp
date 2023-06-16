#include "Others/ast_size_of.hpp"

Sizeof::Sizeof(NodePtr variable)
{
    branches.push_back(variable);
}
void Sizeof::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string structname = "none";
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    int startoffset;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].structVars.count(branches[0]->getName()) > 0)
        {
            structname = program_data.functions[program_data.currentFunctionName].scopes[currentScope].structVars[branches[0]->getName()].structname;
            startoffset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].structVars[branches[0]->getName()].offset;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    if(structname != "none")
    {
        output << "addiu $" << destReg << ", $0, "<< program_data.structBindings[structname].size << std::endl; 
    }
    else
    {
        if(branches[0]->getType(program_data) == "float" || branches[0]->getType(program_data) == "int" || branches[0]->getType(program_data) == "usnigned")
        {
            output << "addiu $" << destReg << ", $0, 4" << std::endl; 
        }
        else if(branches[0]->getType(program_data) == "char")
        {
        output << "addiu $" << destReg << ", $0, 1" << std::endl; 
        }
    }
    
}