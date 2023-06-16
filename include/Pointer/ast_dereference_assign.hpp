#ifndef ast_dereference_assgin_hpp
#define ast_dereference_assign_hpp

#include "ast_node.hpp"

class DereferenceAssign : public Node
{
public:
    DereferenceAssign(NodePtr dereference, NodePtr assignment);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif