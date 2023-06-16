#ifndef ast_post_decrement_hpp
#define ast_post_decrement_hpp

#include "ast_node.hpp"

class PostDecrement : public Node
{
public: 
    PostDecrement(NodePtr variable);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};
#endif