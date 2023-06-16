#include "Arrays/ast_array_declare.hpp"

ArrayDeclare::ArrayDeclare(NodePtr type, NodePtr name, NodePtr elementNumber)
{
    branches.push_back(type);
    branches.push_back(name);
    branches.push_back(elementNumber);
}
void ArrayDeclare::VariableParse(Program_Data &program_data, std::string functionName)
{
    if(functionName != "global")
        program_data.CreateArray(branches[1]->getName(), functionName, branches[2]->getValue(), branches[0]->getType(program_data));
    else
        scopeNumber = -1;
}
void ArrayDeclare::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    if(scopeNumber == -1)
    {
        output << ".data" << std::endl;
        output << branches[1]->getName() << ":" << std::endl;
        for(int i = 0; i < branches[2]->getValue(); i++)
        {
            output << ".word 0" << std::endl;
        }
    }

}