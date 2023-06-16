#include "Pointer/ast_dereference_assign.hpp"

DereferenceAssign::DereferenceAssign(NodePtr dereference, NodePtr assignment)
{
    branches.push_back(dereference);
    branches.push_back(assignment);
}
void DereferenceAssign::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    
}
void DereferenceAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int variable_offset = -9;
    std::string realType;
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[0]->branches[0]->getName()) > 0)
        {
            realType = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->branches[0]->getName()].pointerType;
            variable_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->branches[0]->getName()].stack_offset;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    int offsetReg = program_data.GetEmptyRegister();
    output << "lw $" << offsetReg << ", " << variable_offset << "($sp)" << std::endl;
    branches[1]->CodeGen(output, program_data, destReg, realType);
    if(realType == "unsigned" || realType == "int")
        output << "sw $" << destReg  << ", 0($" << offsetReg <<")" << std::endl;
    else if(realType == "float")
        output << "s.s $f" << destReg  << ", 0($" << offsetReg <<")" << std::endl;
    else if(realType == "char")
        output << "sb $" << destReg  << ", 0($" << offsetReg <<")" << std::endl;

}