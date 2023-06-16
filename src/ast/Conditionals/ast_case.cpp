#include "Conditionals/ast_case.hpp"

Case::Case(NodePtr value, NodePtr body)
{
    branches.push_back(value);
    branches.push_back(body);
}

void Case::VariableParse(Program_Data &program_data, std::string functionName)
{
    program_data.EnterScope(functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
    if(branches[1] != NULL)
        branches[1]->VariableParse(program_data, functionName);
    program_data.ExitScope(functionName);
    
}
void Case::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    
    if(branches[0] != NULL)
    {
        if(type == "unsigned" || type == "int")
        {
        int valueReg = program_data.GetEmptyRegister();
        branches[0]->CodeGen(output, program_data, valueReg, type);
        program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel = program_data.functions[program_data.currentFunctionName].scopes[program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].parentScopeId].endLabel;
        std::string caseEndLabel = program_data.LabelGenerator("caseEndLabel");
        output << "bne $" << destReg << ", $" << valueReg << ", " << caseEndLabel << std::endl;
        output << "nop" << std::endl;
        branches[1]->CodeGen(output, program_data, valueReg, type) ;
        program_data.SetRegisterUnused(valueReg);
        output << caseEndLabel << ":" << std::endl;
        }
        else if (type == "float")
        {
        int valueReg = program_data.GetEmptyRegister();
        branches[0]->CodeGen(output, program_data, valueReg, type);
        program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel = program_data.functions[program_data.currentFunctionName].scopes[program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].parentScopeId].endLabel;
        std::string caseEndLabel = program_data.LabelGenerator("caseEndLabel");
        output << "bne $f" << destReg << ", $f" << valueReg << ", " << caseEndLabel << std::endl;
        output << "nop" << std::endl;
        branches[1]->CodeGen(output, program_data, valueReg, type) ;
        program_data.SetRegisterUnused(valueReg);
        output << caseEndLabel << ":" << std::endl;
        }
    }
    else
    {
        branches[1]->CodeGen(output, program_data, destReg, type);
    }
}