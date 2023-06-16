#ifndef ast_struct_declare
#define ast_struct_declare

#include "ast_node.hpp"

class StructDeclare : public Node
{
public: 
    StructDeclare(NodePtr structname, NodePtr name);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override {}
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif