#include "Functions/ast_external.hpp"

External::External(NodePtr type, NodePtr name)
{
    branches.push_back(type);
    branches.push_back(name);
}
External::External(NodePtr type, NodePtr name, NodePtr params)
{
    branches.push_back(type);
    branches.push_back(name);
    branches.push_back(params);
}

void External::VariableParse(Program_Data &program_data, std::string functionName) 
{
    program_data.AddExtern(branches[1]->getName(), branches[0]->getType(program_data));
    if(branches.size() == 3)
        branches[2]->ExternParse(program_data, functionName);
}