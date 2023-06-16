#include "Functions/ast_function_declare.hpp"

FunctionDeclaration::FunctionDeclaration(NodePtr fun_type, NodePtr name, NodePtr body)
{
    branches.push_back(fun_type);
    branches.push_back(name);
    branches.push_back(body);
}
FunctionDeclaration::FunctionDeclaration(NodePtr fun_type, NodePtr name, NodePtr body, NodePtr args)
{
    branches.push_back(fun_type);
    branches.push_back(name);
    branches.push_back(body);
    branches.push_back(args);

}

void FunctionDeclaration::VariableParse(Program_Data &program_data, std::string functionName) 
{
    
    program_data.CreateFunction(branches[1]->getName(), branches[0]->getType(program_data));
    program_data.isFunctionCallParse = true;
    branches[2]->FunctionCallParse(program_data, branches[1]->getName());
    program_data.isFunctionCallParse = false;
    int max = -1;
    int id = -1;
    for(int i = 0; i < program_data.functions[branches[1]->getName()].functionCalls.size(); i++)
    {
        if(program_data.functions[branches[1]->getName()].functionCalls[i].uniqueArgCounter > max)
        {
            max = program_data.functions[branches[1]->getName()].functionCalls[i].uniqueArgCounter;
            id = i;
        }
    }
    if(max != -1)
    {
        program_data.functions[branches[1]->getName()].stackSize +=  program_data.functions[branches[1]->getName()].functionCalls[id].stacksize + 4;
        program_data.functions[branches[1]->getName()].uniqueVarCounter += program_data.functions[branches[1]->getName()].functionCalls[id].uniqueArgCounter * 4;
    }
    branches[2]->VariableParse(program_data, branches[1]->getName());
    if(branches.size() == 4)
    {
        branches[3]->VariableParse(program_data, branches[1]->getName());
    }
    // for(int i = 0; i < numberOfArguments; i++)
    // {
    //     program_data.CreateArguments(branches[i*2 + 4]->getName(), branches[1]->getName());
    // }


}
void FunctionDeclaration::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    //Has no parameters and doesn't save return value for now, will add later
    output << ".text" << std::endl;
    program_data.currentFunctionName = branches[1]->getName();
    output << program_data.currentFunctionName << ":" << std::endl;
    output << "#Function Declare called" << std::endl;
    output << "addiu $sp, $sp, -" << program_data.functions[program_data.currentFunctionName].stackSize << std::endl;
    output << "sw $fp, " << (program_data.functions[program_data.currentFunctionName].stackSize-4) << "($sp)" << std::endl;
    if(program_data.functions[branches[1]->getName()].functionCalls.size() > 0)
        output << "sw $ra, " << (program_data.functions[program_data.currentFunctionName].stackSize-12) << "($sp)" << std::endl;
    output << "move $fp, $sp" << std::endl;
    if(branches.size() == 4)
    {
        branches[3]->CodeGen(output, program_data, destReg, "int");
    }

    branches[2]->CodeGen(output, program_data, destReg, "int");
    if(program_data.functions[branches[1]->getName()].type == "void")
    {
        output << "move $sp, $fp" << std::endl;
        output << "lw $fp, " << (program_data.functions[program_data.currentFunctionName].stackSize-4) << "($sp)" << std::endl;
        if(program_data.functions[program_data.currentFunctionName].functionCalls.size() > 0)
        {
            output << "lw $ra, " << (program_data.functions[program_data.currentFunctionName].stackSize-12) << "($sp)" << std::endl;
        }
        output << "addiu $sp, $sp, " << program_data.functions[program_data.currentFunctionName].stackSize << std::endl;
        
        output << "j $31" << std::endl;
        output << "nop" << std::endl;
    }
    output << ".global " << branches[1]->getName() << std::endl;


    
}