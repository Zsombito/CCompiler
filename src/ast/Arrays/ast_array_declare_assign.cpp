#include "Arrays/ast_array_declare_assign.hpp"

ArrayDeclareAssign::ArrayDeclareAssign(NodePtr type, NodePtr name, NodePtr args)
{
    branches.push_back(type);
    branches.push_back(name);
    branches.push_back(args);

}
void ArrayDeclareAssign::VariableParse(Program_Data &program_data, std::string functionName) 
{
    if(functionName != "global")
    {
        if(branches[0]->getType(program_data) != "char")
            program_data.CreateArray(branches[1]->getName(), functionName, branches[0]->getType(program_data));
        else
            program_data.CreateArray(branches[1]->getName(), functionName, branches[2]->getString().length() + 1, "char");
        branches[2]->VariableParse(program_data, functionName);
    }
    else 
    {
        scopeNumber = -1;
    }
}
void ArrayDeclareAssign::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(scopeNumber != -1)
    {   
        if(branches[0]->getType(program_data) != "char")
            branches[2]->CodeGen(output, program_data, destReg, branches[0]->getType(program_data));
        else
        {
            std::string value = branches[2]->getString();
            int offset = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[branches[0]->getName()].startOffset;
            for(int i = 0; i < value.size(); i++)
            {
                char c = value[i];
                output << "li $" << destReg << ", " << int(c) << std::endl;
                output << "sb $" << destReg << ", " << offset << "($sp)" << std::endl;
                offset++;
            }
            output << "sb $0, " << offset << "($sp)" << std::endl;
        }
    }
    else
    {
        output << ".data" << std::endl;
        output << branches[1]->getName() << ":"<< std::endl;
        branches[2]->CodeGen(output, program_data, destReg, type);
    }
}
void ArrayDeclareAssign::FunctionCallParse(Program_Data &program_data, std::string functionName)
{

}