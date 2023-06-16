#ifndef ast_post_increment_hpp
#define ast_post_increment_hpp

#include "ast_node.hpp"

class PostIncrement : public Node
{
public: 
    PostIncrement(NodePtr variable);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};
#endif