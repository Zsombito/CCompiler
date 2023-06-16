#ifndef ast_else_hpp
#define ast_else_hpp

#include "ast_node.hpp"

class IfElse : public Node
{
public:
    IfElse(NodePtr ifstat, NodePtr body);
    IfElse(NodePtr ifstat);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif