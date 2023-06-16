#include "Struct/ast_struct_index.hpp"

StructIndex::StructIndex(NodePtr name, NodePtr var)
{
    branches.push_back(name);
    branches.push_back(var);
}

void StructIndex::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string structname;
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
    int var_offset = program_data.structBindings[structname].SearchMemberOffset(branches[1]->getName()) + startoffset;
    std::string realType = program_data.structBindings[structname].SearchMemberType(branches[1]->getName());
    if(realType == "int" || realType == "float")
        output << "lw $" << destReg << ", " << var_offset << "($sp)" << std::endl;
    else if(realType == "float")
        output << "l.s $f" << destReg << ", " << var_offset << "($sp)" << std::endl;
    else if(realType == "char")
        output << "lb $" << destReg << ", " << var_offset << "($sp)" << std::endl; 
}
int StructIndex::getStructOffset(Program_Data &program_data)
{
    std::string structname;
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
    return program_data.structBindings[structname].SearchMemberOffset(branches[1]->getName()) + startoffset;
}
std::string StructIndex::getType(Program_Data &program_data)
{
    std::string structname;
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
    return program_data.structBindings[structname].SearchMemberType(branches[1]->getName());
}