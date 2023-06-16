#include "Enums/ast_enum_declare.hpp"

EnumDeclare::EnumDeclare(NodePtr name, NodePtr enumVariables)
{
    branches.push_back(name);
    branches.push_back(enumVariables);
}
void EnumDeclare::VariableParse(Program_Data &program_data, std::string functionName)
{
    program_data.CreateEnum(branches[0]->getName());
    branches[1]->EnumParse(program_data, branches[0]->getName());
}