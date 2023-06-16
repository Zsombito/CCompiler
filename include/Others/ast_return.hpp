#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast_node.hpp"

class Return : public Node
{
public:
    Return(NodePtr value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    // void DebugPrint() const override;
};


#endif