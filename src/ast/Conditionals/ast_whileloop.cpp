#include "Conditionals/ast_whileloop.hpp"

WhileLoop::WhileLoop(NodePtr condition, NodePtr executant)
{
    branches.push_back(condition);
    branches.push_back(executant);
}

void WhileLoop::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    //Condition execution:
    
    std::string endLabel = program_data.LabelGenerator("endLabel");
    std::string startLabel = program_data.LabelGenerator("startLabel");
    program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].startLabel = startLabel;
    program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].endLabel = endLabel;
    //Jump to else if false
    output << startLabel << ":" << std::endl;
    branches[0]->CodeGen(output, program_data, destReg, type);
    output << "beq $0, $" << destReg << ", " << endLabel << std::endl;
    output << "nop" << std::endl;

    //Execute if it was true and then jump to end
    if(branches[1] != NULL)
        branches[1]->CodeGen(output, program_data, destReg, type);
    output << "b " << startLabel << std::endl;
    output << "nop" << std::endl;
    
    //Execute else if it was false
    output << endLabel << ":" << std::endl;
}
void WhileLoop::VariableParse(Program_Data &program_data, std::string functionName) 
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