#ifndef ast_pre_decrement_hpp
#define ast_pre_decrement_hpp

#include "ast_node.hpp"

class PreDecrement : public Node
{
public: 
    PreDecrement(NodePtr variable);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};
#endif