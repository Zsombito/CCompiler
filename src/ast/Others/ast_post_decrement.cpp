#include "Others/ast_post_decrement.hpp"


PostDecrement::PostDecrement(NodePtr variable)
{
    branches.push_back(variable);
}
void PostDecrement::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
}
void PostDecrement::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
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
    if(variable_offset != -9)
    {
        output << "lw $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        int freeReg = program_data.GetEmptyRegister();
        output << "addiu $" << freeReg << ", $0"  << ", 1" << std::endl;
        output << "sub $" << freeReg << ", $" << destReg << ", $" << freeReg << std::endl;
        output << "sw $"<< freeReg << ", " << variable_offset << "($sp)" << std::endl;
        program_data.SetRegisterUnused(freeReg);
    }
    else
    {   
        int offsetReg = program_data.GetEmptyRegister();
        int freeReg = program_data.GetEmptyRegister();
        output << "lui $" << offsetReg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
        output << "lw $" << destReg  << ", %lo(" << branches[0]->getName() << ")($" << offsetReg << ")" << std::endl;
        output << "addiu $" << freeReg << ", $0"  << ", 1" << std::endl;
        output << "sub $" << freeReg << ", $" << destReg << ", $" << freeReg << std::endl;
        output << "sw $"<< freeReg << ", %lo(" << branches[0]->getName() << ")($" << offsetReg << ")" << std::endl;
        program_data.SetRegisterUnused(freeReg);
        program_data.SetRegisterUnused(offsetReg);
    }

}