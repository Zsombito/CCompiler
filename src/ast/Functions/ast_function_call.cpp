#include "Functions/ast_function_call.hpp"

FunctionCall::FunctionCall(NodePtr name)
{
    branches.push_back(name);
}
FunctionCall::FunctionCall(NodePtr name, NodePtr args)
{
    branches.push_back(name);
    branches.push_back(args);
}
void FunctionCall::FunctionCallParse(Program_Data &program_data, std::string functionName)
{
    program_data.CreateFunctionCall(branches[0]->getName(), functionName);
    if(branches.size() == 2)
        branches[1]->FunctionCallParse(program_data, functionName);
}
void FunctionCall::VariableParse(Program_Data &program_data, std::string functionName) {}
void FunctionCall::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(branches.size() != 1)
    {
        program_data.currentFunctionCall = branches[0]->getName();
        branches[1]->CodeGen(output, program_data, destReg, type);
    }
    output << "jal " << branches[0]->getName() << std::endl;
    output << "nop" << std::endl;
    output << "move $" << destReg << ", $2" << std::endl;
}