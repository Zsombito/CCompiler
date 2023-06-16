#ifndef ast_pointer_sub_hpp
#define ast_pointer_sub_hpp

#include "ast_node.hpp"

class PointerSub : public Node
{
public:
    PointerSub(NodePtr pointer, NodePtr sub);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif