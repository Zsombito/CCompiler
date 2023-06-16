#include "Declarations_and_Assigns/ast_declara_assign.hpp"

DeclareAssign::DeclareAssign(NodePtr type, NodePtr name, NodePtr value)
{
    
    branches.push_back(type);
    branches.push_back(name);
    branches.push_back(value);
}
void DeclareAssign::VariableParse(Program_Data &program_data, std::string functionName)
{
    if(functionName != "global")
    {
        scopeNumber = program_data.functions[functionName].currentScope;
        program_data.CreateVariable(branches[1]->getName(), functionName, branches[0]->getType(program_data));
        branches[2]->VariableParse(program_data, functionName);
    }
    else
    {
        scopeNumber = -1;
    }
}
void DeclareAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(scopeNumber != -1)
    {
        branches[2]->CodeGen(output, program_data, destReg, branches[0]->getType(program_data));
        std::string realType = branches[0]->getType(program_data);
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
        if(realType == "unsigned" || realType == "int" || realType == "pointer")
            output << "sw $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        else if(realType == "float")
            output << "s.s $f"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        else if(realType == "char")
            output << "sb $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        else if(realType == "double")
            output << "s.d $f"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
}
    else
    {
        std::string realType = branches[0]->getType(program_data);
        if(realType == "unsigned" || realType == "int" || realType == "float")
        {
            output << ".data" << std::endl;
            output << branches[1]->getName() << ":" <<  " .word "<< branches[2]->getValue() << std::endl;
            program_data.globalTypes.insert(std::pair<std::string, std::string>(branches[1]->getName(), branches[0]->getType(program_data)));
        }
        else if(realType == "float")
        {
            output << ".data" << std::endl;
            output << branches[1]->getName() << ":" <<  " .word "<< branches[2]->getFloat() << std::endl;
            program_data.globalTypes.insert(std::pair<std::string, std::string>(branches[1]->getName(), branches[0]->getType(program_data)));
        }
    }
}