#include "ast_node.hpp"

Node::Node(std::vector<NodePtr> _branches) : branches(_branches){}
Node::Node(){}
Node::~Node()
{
    
    for(int i = 0; i < branches.size(); i++)
        delete branches[i];
}

void Node::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::cerr << "Not implemented a Codegen yet";
}
void Node::VariableParse(Program_Data &program_data, std::string functionName) 
{
    scopeNumber = program_data.functions[functionName].currentScope;
    for(int i = 0; i < branches.size(); i++)
    {
        if(branches[i] != NULL)
            branches[i]->VariableParse(program_data, functionName);
    }
    
}
void Node::FunctionCallParse(Program_Data &program_data, std::string functionName) 
{
    for(int i = 0; i < branches.size(); i++)
    {
        if(branches[i] != NULL)
            branches[i]->FunctionCallParse(program_data, functionName);
    }
}
std::string Node::getName()const{return "";}
