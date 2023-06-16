#ifndef ast_pointer_declare_assing_hpp
#define ast_pointer_declare_assing_hpp

#include "ast_node.hpp"

class PointerDeclareAssign : public Node
{
public:
    PointerDeclareAssign(NodePtr pointerType, NodePtr pointerName, NodePtr assignment);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif