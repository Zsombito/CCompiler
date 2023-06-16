#ifndef ast_declare_assign_hpp
#define ast_declare_assign_hpp

#include "ast_node.hpp"

class DeclareAssign : public Node
{
public:
    DeclareAssign(NodePtr type, NodePtr name, NodePtr value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    // void DebugPrint() const override;
};




#endif