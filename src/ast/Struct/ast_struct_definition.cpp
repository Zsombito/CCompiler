#include "Struct/ast_struct_definition.hpp"

StructDefinition::StructDefinition(NodePtr name, NodePtr body)
{
    branches.push_back(name);
    branches.push_back(body);
}

void StructDefinition::VariableParse(Program_Data &program_data, std::string functionName) 
{
    if(branches[1] != NULL)
    {
        program_data.CreateStruct(branches[0]->getName());
        program_data.isStructDef = true;
        program_data.currentStructDef = branches[0]->getName();
        branches[1]->VariableParse(program_data, functionName);
        program_data.isStructDef = false;
    }
}