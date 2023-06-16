#ifndef ast_struct_assign_hpp
#define ast_struct_assign_hpp

#include "ast_node.hpp"

class StructAssign : public Node 
{
public:
    StructAssign(NodePtr name, NodePtr assignment);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
};

#endif