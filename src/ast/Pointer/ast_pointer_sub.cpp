#include "Pointer/ast_pointer_sub.hpp"


PointerSub::PointerSub(NodePtr pointer, NodePtr sub)
{
    branches.push_back(pointer);
    branches.push_back(sub);
}
void PointerSub::VariableParse(Program_Data &program_data, std::string functionName)
{
    branches[0]->VariableParse(program_data, functionName);
    branches[1]->VariableParse(program_data, functionName);
}
void PointerSub::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, "pointer");
    int freeReg = program_data.GetEmptyRegister();
    output << "move $" << freeReg << ", $" << destReg << std::endl;
    branches[1]->CodeGen(output, program_data, destReg, "pointer");
    output << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
    output << "sub $" << destReg << ", $" << freeReg << ", $" << destReg << std::endl;
    program_data.SetRegisterUnused(freeReg); 
}