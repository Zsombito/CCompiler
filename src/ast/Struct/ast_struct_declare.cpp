#include "Struct/ast_struct_declare.hpp"

StructDeclare::StructDeclare(NodePtr structname, NodePtr name)
{
    branches.push_back(structname);
    branches.push_back(name);
}

void StructDeclare::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.AddStructVariable(branches[1]->getName(), branches[0]->getName(), functionName);
    
}