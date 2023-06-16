#include "Pointer/ast_pointer_declare_assing.hpp"

PointerDeclareAssign::PointerDeclareAssign(NodePtr pointerType, NodePtr pointerName, NodePtr assignment)
{
    branches.push_back(pointerType);
    branches.push_back(pointerName);
    branches.push_back(assignment);
}
void PointerDeclareAssign::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.CreatePointer(functionName, branches[1]->getName(), branches[0]->getType(program_data));
    branches[2]->VariableParse(program_data, functionName);
}
void PointerDeclareAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[2]->CodeGen(output, program_data, destReg, "pointer");
    if(scopeNumber != -1)
    {
        
        int variable_offset = -9;
        int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
        int currentScope = scopeNumber;
        for(int i = 0; i < currentDepth + 1; i++)
        {
            if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(branches[1]->getName()) > 0)
           {
               
                variable_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[branches[1]->getName()].stack_offset;
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