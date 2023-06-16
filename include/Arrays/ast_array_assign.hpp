#ifndef ast_array_assign_hpp
#define ast_array_assign_hpp

#include "ast_node.hpp"

class ArrayAssign : public Node
{
public:
    ArrayAssign(NodePtr name, NodePtr index, NodePtr value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    
};

#endif