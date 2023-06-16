#ifndef ast_forloop_hpp
#define ast_forloop_hpp

#include "ast_node.hpp"

class ForLoop : public Node
{
public:
    ForLoop(NodePtr assign, NodePtr condition, NodePtr stepping);
    ForLoop(NodePtr assign, NodePtr condition, NodePtr stepping, NodePtr body);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;

};

#endif