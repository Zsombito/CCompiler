#ifndef ast_size_of_hpp
#define ast_size_of_hpp

#include "ast_node.hpp"

class Sizeof : public Node
{
public:
    Sizeof(NodePtr variable);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
};

#endif