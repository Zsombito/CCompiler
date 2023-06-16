#include "Arrays/ast_array_call.hpp"

ArrayCall::ArrayCall(NodePtr name, NodePtr index)
{
    branches.push_back(name);
    branches.push_back(index);
}
void ArrayCall::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[program_data.currentFunctionName].currentScope;
}
void ArrayCall::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(branches[0]->getType(program_data) == "pointer")
    {
        if(branches[0]->getPointerType(program_data) != "char")
        {
            int offset_reg = program_data.GetEmptyRegister();
            branches[1]->CodeGen(output, program_data, destReg, type);
            output << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
            output << "move $" << offset_reg << ", $" << destReg << std::endl;
            branches[0]->CodeGen(output, program_data, destReg, type);
            output << "addu $" << destReg << ", $" << offset_reg << ", $" << destReg << std::endl;
            
            if(branches[0]->getPointerType(program_data) == "int" || branches[0]->getPointerType(program_data) == "unsigned")
                output << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl; 
            else if(branches[0]->getPointerType(program_data) == "float")
                output << "l.s $f" << destReg << ", 0($" << destReg << ")" << std::endl;
            program_data.SetRegisterUnused(offset_reg);
        }
        else
        {
            int offset_reg = program_data.GetEmptyRegister();
            branches[1]->CodeGen(output, program_data, destReg, type);
            output << "move $" << offset_reg << ", $" << destReg << std::endl;
            branches[0]->CodeGen(output, program_data, destReg, type);
            output << "addu $" << destReg << ", $" << offset_reg << ", $" << destReg << std::endl;
            output << "lb $" << destReg << ", 0($" << destReg << ")" << std::endl; 
             program_data.SetRegisterUnused(offset_reg);
        }
         

    }
    else if(branches[0]->getType(program_data) == "char")
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
        output << "addiu $" << offset_reg << ", $sp, " << start_offset << std::endl;
        branches[1]->CodeGen(output, program_data, destReg, "int");
        output << "add $" << offset_reg << ", $" << offset_reg << ", $" << destReg << std::endl;
        if(branches[0]->getType(program_data) == "int" || branches[0]->getType(program_data) == "unsigned")
            output << "lw $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        else if(branches[0]->getType(program_data) == "float" )
            output << "l.s $f" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
        else if(branches[0]->getType(program_data) == "char" )
            output << "lb $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
         program_data.SetRegisterUnused(offset_reg);
    }
    else
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
            output << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
            output << "addu $" << offset_reg << ", $" << offset_reg << ", $" << destReg << std::endl;
            if(branches[0]->getType(program_data) == "int" || branches[0]->getType(program_data) == "unsigned")
                output << "lw $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
            else if(branches[0]->getType(program_data) == "float" )
                output << "l.s $f" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
            else if(branches[0]->getType(program_data) == "char" )
                 output << "lb $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
            program_data.SetRegisterUnused(offset_reg);
            
            
        }
        else
        {
            output << "lui $" << offset_reg << ", %hi(" << branches[0]->getName() << ")" << std::endl;
            output << "addiu $" << offset_reg << ", $" << offset_reg << ", %lo(" << branches[0]->getName() << ")" << std::endl;
            output << "addu $" << offset_reg << ", $" << offset_reg << ", $" << destReg << std::endl;
            output << "lw $" << destReg << ", 0($" << offset_reg << ")" <<std::endl;
            program_data.SetRegisterUnused(offset_reg);
        }
    }
    
} 