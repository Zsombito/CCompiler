#include "Pointer/ast_pointer_declaration.hpp"

PointerDeclare::PointerDeclare(NodePtr pointerType, NodePtr pointerName)
{
    branches.push_back(pointerType);
    branches.push_back(pointerName);
}

void PointerDeclare::VariableParse(Program_Data &program_data, std::string functionName) 
{
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.CreatePointer(functionName, branches[1]->getName(), branches[0]->getType(program_data));
}
void PointerDeclare::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    
}