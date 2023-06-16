#ifndef ast_pointer_assign_hpp
#define ast_pointer_assign_hpp

#include "ast_node.hpp"

class PointerAssign : public Node
{
public:
    PointerAssign(NodePtr pointer, NodePtr assigment);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif