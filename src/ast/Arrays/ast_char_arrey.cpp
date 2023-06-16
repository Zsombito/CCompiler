#include "Arrays/ast_char_array.hpp"


CharArrey::CharArrey(NodePtr name, NodePtr string)
{
    branches.push_back(name);
    branches.push_back(string);
}

void CharArrey::VariableParse(Program_Data &program_data, std::string functionName)
{
    scopeNumber = program_data.functions[functionName].currentScope;
    program_data.GenerateStringArrey(branches[0]->getName(), branches[1]->getString(), functionName);
}
void CharArrey::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string value = branches[1]->getString();
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