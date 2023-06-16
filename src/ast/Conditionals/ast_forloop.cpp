#include "Conditionals/ast_forloop.hpp"

ForLoop::ForLoop(NodePtr assign, NodePtr condition, NodePtr stepping)
{
    branches.push_back(assign);
    branches.push_back(condition);
    branches.push_back(stepping);
    branches.push_back(NULL);

}
ForLoop::ForLoop(NodePtr assign, NodePtr condition, NodePtr stepping, NodePtr body)
{
    branches.push_back(assign);
    branches.push_back(condition);
    branches.push_back(stepping);
    branches.push_back(body);
    
}
void ForLoop::VariableParse(Program_Data &program_data, std::string functionName)
{
    program_data.EnterScope(functionName);
    scopeNumber = program_data.functions[functionName].currentScope;
    for(int i = 0; i < branches.size(); i++)
    {
        if(branches[i] != NULL)
            branches[i]->VariableParse(program_data, functionName);
    }
    program_data.ExitScope(functionName);
}
void ForLoop::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string startLabel = program_data.LabelGenerator("startlabel");
    std::string endLabel = program_data.LabelGenerator("endlabel");
    program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].startLabel = startLabel;
    program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel = endLabel;
    branches[0]->CodeGen(output, program_data, destReg,type);
    output << startLabel << ":" << std::endl;
    branches[1]->CodeGen(output, program_data, destReg, type);
    output << "beq $" << destReg << ", $0, " << endLabel << std::endl;
    output << "nop" << std::endl;
    if(branches[3] != NULL)
        branches[3]->CodeGen(output, program_data, destReg, type);
    branches[2]->CodeGen(output, program_data, destReg, type);
    output << "b " << startLabel << std::endl;
    output << "nop" << std::endl;
    output << endLabel << ":" << std::endl;
}