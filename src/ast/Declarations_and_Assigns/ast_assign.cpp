#include "Declarations_and_Assigns/ast_assign.hpp"

Assign::Assign(NodePtr varName, NodePtr value)
{
    branches.push_back(varName);
    branches.push_back(value);
}
void Assign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
     
    
    std::string realType = branches[0]->getType(program_data);
    if(branches[0]->getType(program_data) == "pointer")
        program_data.currentPointerAssignType = branches[0]->getPointerType(program_data);

    branches[1]->CodeGen(output, program_data, destReg, branches[0]->getType(program_data));
    
    
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
        if(realType == "unsigned" || realType == "int" || realType == "pointer")
        {
            output << "sw $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
        else if(realType == "char")
        {
            output << "sb $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
        else if(realType == "float")
        {
            output << "s.s $f"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
        else if(realType == "double")
        {
            output << "s.d $f" << destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
    
    }
    else
    {   
        if(realType == "unsigned" || realType == "int")
        {
        int offsetReg = program_data.GetEmptyRegister();
        output << "lui $" << offsetReg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
        output << "sw $" << destReg  << ", %lo(" << branches[0]->getName() << ")($" << offsetReg << ")" << std::endl;
        program_data.SetRegisterUnused(offsetReg);
        }
        else if(realType == "float")
        {
            int offsetReg = program_data.GetEmptyRegister();
            output << "lui $" << offsetReg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
            output << "addui $" << offsetReg  << ", %lo(" << branches[0]->getName() << ")($" << offsetReg << ")" << std::endl;
            output << "s.s $f" << destReg << "0($" << offsetReg << ")" << std::endl;
            program_data.SetRegisterUnused(offsetReg);
        }
        else if(realType == "double")
        {
            int offsetReg = program_data.GetEmptyRegister();
            output << "lui $" << offsetReg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
            output << "addui $" << offsetReg  << ", %lo(" << branches[0]->getName() << ")($" << offsetReg << ")" << std::endl;
            output << "s.d $f" << destReg << "0($" << offsetReg << ")" << std::endl;
            program_data.SetRegisterUnused(offsetReg);
        }
    }
    
}
void Assign::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    branches[1]->VariableParse(program_data, functionName);
}