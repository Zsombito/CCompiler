#include "Struct/ast_struct_assign.hpp"

StructAssign::StructAssign(NodePtr name, NodePtr assignment)
{
    branches.push_back(name);
    branches.push_back(assignment);
}

void StructAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int offset = branches[0]->getStructOffset(program_data);
    std::string realType = branches[0]->getType(program_data);
    branches[1]->CodeGen(output, program_data, destReg, realType);
    if(realType == "int" || realType == "unsigned")
        output << "sw $" << destReg << ", " << offset << "($sp)" << std::endl;
    else if(realType == "float")
        output << "s.s $f" << destReg << ", " << offset << "($sp)" << std::endl;
    else if(realType == "char")
        output << "sb $" << destReg << ", " << offset << "($sp)" << std::endl;
}