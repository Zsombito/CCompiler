#include "Pointer/ast_pointer_assign.hpp"

PointerAssign::PointerAssign(NodePtr pointer, NodePtr assigment)
{
    branches.push_back(pointer);
    branches.push_back(assigment);
}

void PointerAssign::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    branches[0]->VariableParse(program_data, functionName);
    branches[1]->VariableParse(program_data, functionName);
}
void PointerAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[2]->CodeGen(output, program_data, destReg, "pointer");
    if(scopeNumber != -1)
    {
        
        int variable_offset = -9;
        int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
        int currentScope = scopeNumber;
        for(int i = 0; i < currentDepth + 1; i++)
        {
            if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[0]->getName()) > 0)
           {
               
                variable_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[0]->getName()].stack_offset;
               break;
           }
           if(i != currentDepth)
               currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
        }
        if(variable_offset != 9)
            output << "sw $" << destReg << ", " << variable_offset << "($sp)" << std::endl;
        else
        {
            output << "sw $" << destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
    }
}