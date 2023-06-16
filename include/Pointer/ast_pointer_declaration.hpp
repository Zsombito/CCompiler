#ifndef ast_pointer_declaration_hpp
#define ast_pointer_declaration_hpp

#include "ast_node.hpp"

class PointerDeclare : public Node
{
public:
    PointerDeclare(NodePtr pointerType, NodePtr pointerName);
     void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
     void VariableParse(Program_Data &program_data, std::string functionName) override;
    bool isPointerDeclare() override {return true;}
    
};

#endif