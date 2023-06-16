#include "Functions/ast_params.hpp"

Params::Params(NodePtr declaration)
{
    branches.push_back(declaration);
    
    
}
Params::Params(NodePtr argSeq, NodePtr declaration)
{
    branches.push_back(argSeq);
    branches.push_back(declaration);
    
}
void Params::VariableParse(Program_Data &program_data, std::string functionName) 
{
   
    if(branches.size() == 1)
    {
        if(branches[0]->isPointerDeclare())
            program_data.CreateParameter(branches[0]->branches[1]->getName(), functionName, "pointer", branches[0]->branches[0]->getType(program_data));
        else
            program_data.CreateParameter(branches[0]->branches[1]->getName(), functionName, branches[0]->branches[0]->getType(program_data));
    }
    else
    {
        if(branches[0]->paramSeq() == false)
        {
            if(branches[0]->isPointerDeclare())
                program_data.CreateParameter(branches[0]->branches[1]->getName(), functionName, "pointer", branches[0]->branches[0]->getType(program_data));
            else
                program_data.CreateParameter(branches[0]->branches[1]->getName(), functionName, branches[0]->branches[0]->getType(program_data));
            if(branches[1]->isPointerDeclare())
                program_data.CreateParameter(branches[1]->branches[1]->getName(), functionName, "pointer", branches[0]->branches[0]->getType(program_data));
            else
                program_data.CreateParameter(branches[1]->branches[1]->getName(), functionName, branches[1]->branches[0]->getType(program_data));
        }
        else
        {
            branches[0]->VariableParse(program_data, functionName);
            if(branches[1]->isPointerDeclare())
                program_data.CreateParameter(branches[1]->branches[1]->getName(), functionName, "pointer", branches[0]->branches[0]->getType(program_data));
            else
                program_data.CreateParameter(branches[1]->branches[1]->getName(), functionName, branches[1]->branches[0]->getType(program_data));
        }
    }
}
void Params::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{

    if(branches.size() == 1)
    {
        if(branches[0]->branches[0]->getType(program_data) == "int" || branches[0]->branches[0]->getType(program_data) == "unsigned" || branches[0]->isPointerDeclare())
            output << "sw $4, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
        else if(branches[0]->branches[0]->getType(program_data) == "float" )
            output << "s.s $f12, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
        else if(branches[0]->branches[0]->getType(program_data) == "char")
            output << "sb $4, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
    }
    else
    {
        if(branches[0]->paramSeq() == false)
        {
            if(branches[0]->branches[0]->getType(program_data) == "int" || branches[0]->branches[0]->getType(program_data) == "unsigned" || branches[0]->isPointerDeclare())
                output << "sw $4, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            else if(branches[0]->branches[0]->getType(program_data) == "float" )
                output << "s.s $f12, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            else if(branches[0]->branches[0]->getType(program_data) == "char" )
                output << "sb $4, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[0]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            if(branches[1]->branches[0]->getType(program_data) == "int" || branches[1]->branches[0]->getType(program_data) == "unsigned" || branches[1]->isPointerDeclare())
                output << "sw $5, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            else if(branches[1]->branches[0]->getType(program_data) == "float" )
                output << "s.s $f14, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            else if(branches[1]->branches[0]->getType(program_data) == "char" )
                output << "sb $5, " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
            
        }
        else
        {
            branches[0]->CodeGen(output, program_data, destReg, type);
            if(program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset <= program_data.functions[program_data.currentFunctionName].stackSize + 12)
            {
                if(branches[1]->branches[0]->getType(program_data) == "char" )
                {
                    output << "sb $" << (4 +program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].argumentNumber) 
                    <<", " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
                }
                else
                {
                output << "sw $" << (4 +program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].argumentNumber) 
                <<", " << program_data.functions[program_data.currentFunctionName].scopes[0].variableBindings[branches[1]->branches[1]->getName()].stack_offset << "($sp)" << std::endl;
                }
            }
    
        }
    }
}
void Params::ExternParse(Program_Data &program_data, std::string functionName) 
{
    if(branches.size() == 1)
    {
        if(branches[0]->isPointerDeclare())
            program_data.AddExternParameter("pointer");
        else
            program_data.AddExternParameter(branches[0]->branches[0]->getType(program_data));
    }
    else
    {
        if(branches[0]->paramSeq())
        {
            branches[0]->ExternParse(program_data, functionName);
            if(branches[1]->isPointerDeclare())
                program_data.AddExternParameter("pointer");
            else
                program_data.AddExternParameter(branches[1]->branches[0]->getType(program_data));
        }
        else
        {
            if(branches[0]->isPointerDeclare())
                program_data.AddExternParameter("pointer");
            else
                program_data.AddExternParameter(branches[0]->branches[0]->getType(program_data));
            if(branches[1]->isPointerDeclare())
                program_data.AddExternParameter("pointer");
            else
                program_data.AddExternParameter(branches[1]->branches[0]->getType(program_data));
        }
    }
}