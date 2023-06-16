#ifndef ast_switch_hpp
#define ast_switch_hpp

#include "ast_node.hpp"

class Switch : public Node
{
public:
    Switch(NodePtr variable, NodePtr body);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};
#endif