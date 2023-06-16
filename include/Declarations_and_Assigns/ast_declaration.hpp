#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "ast_node.hpp"

class Declaration : public Node
{
public:
    Declaration(NodePtr var_type, NodePtr name);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    // void DebugPrint() const override;
    bool paramSeq() override {return false;} 
};







#endif