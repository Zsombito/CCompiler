#include "Pointer/ast_dereference.hpp"

Dereference::Dereference(NodePtr pointer)
{
    branches.push_back(pointer);
}

void Dereference::VariableParse(Program_Data &program_data, std::string functionName) 
{
    branches[0]->VariableParse(program_data, functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
}
void Dereference::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, "pointer");
    std::string realType = "int";
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[0]->getName()) > 0)
        {
            
            realType = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->getName()].pointerType;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    
    if(realType == "int" || realType == "usnigned")
        output << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl; 
    else if(realType == "float")
        output << "l.s $f" << destReg << ", 0($" << destReg << ")" << std::endl; 
    else if(realType == "char")
        output << "lb $" << destReg << ", 0($" << destReg << ")" << std::endl; 
}
std::string Dereference::getType(Program_Data &program_data)
{
    std::string type = "int";
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[0]->getName()) > 0)
        {
            
            type = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->getName()].pointerType;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    return type;
}