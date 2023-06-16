#include "Arrays/ast_array_assign.hpp"

ArrayAssign::ArrayAssign(NodePtr name, NodePtr index, NodePtr value)
{
    branches.push_back(name);
    branches.push_back(index);
    branches.push_back(value);
}

void ArrayAssign::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[program_data.currentFunctionName].currentScope;
    branches[2]->VariableParse(program_data, functionName);
}
void ArrayAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    int start_offset = -9;
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings.count(branches[0]->getName()) > 0)
        {
            start_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings[branches[0]->getName()].startOffset;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    
    int offset_reg = program_data.GetEmptyRegister();
    branches[1]->CodeGen(output, program_data, destReg, type);
    if(scopeNumber != -9)
    {
        output << "addiu $" << offset_reg << ", $sp, " << start_offset << std::endl;
        if(branches[0]->getType(program_data) != "char")
            output << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
        output << "addu $" << offset_reg << ", $" << offset_reg << ", $" << destReg << std::endl;
        branches[2]->CodeGen(output, program_data, destReg, type);
        if(branches[0]->getType(program_data) == "int" || branches[0]->getType(program_data) == "unsigned")
            output << "sw $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        else if(branches[0]->getType(program_data) == "float" )
            output << "s.s $f" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        else if(branches[0]->getType(program_data) == "char" )
            output << "sb $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        program_data.SetRegisterUnused(offset_reg);
    }
    else
    {
        output << "lui $" << offset_reg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
        output << "addiu $" << offset_reg << ", $" << offset_reg << ", %lo(" << branches[0]->getName() << ")" << std::endl;
        output << "addu $" << offset_reg << ", $" << offset_reg << ", $" << destReg << std::endl;
        branches[2]->CodeGen(output, program_data, destReg, type);
        output << "sw $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        program_data.SetRegisterUnused(offset_reg);
    }
    
} 