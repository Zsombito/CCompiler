#include "Pointer/ast_pointer_add.hpp"

PointerAdd::PointerAdd(NodePtr pointer, NodePtr additional)
{
    branches.push_back(pointer);
    branches.push_back(additional);
}

void PointerAdd::VariableParse(Program_Data &program_data, std::string functionName) 
{
    branches[0]->VariableParse(program_data, functionName);
    branches[1]->VariableParse(program_data, functionName);
}
void PointerAdd::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, "pointer");
    int freeReg = program_data.GetEmptyRegister();
    output << "move $" << freeReg << ", $" << destReg << std::endl;
    branches[1]->CodeGen(output, program_data, destReg, "pointer");
    if(branches[0]->getPointerType(program_data) != "char")
        output << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
    output << "add $" << destReg << ", $" << destReg << ", $" << freeReg << std::endl;
    program_data.SetRegisterUnused(freeReg); 
}