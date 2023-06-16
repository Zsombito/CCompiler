#ifndef ast_struct_definition_hpp
#define ast_struct_definition_hpp

#include "ast_node.hpp"

class StructDefinition : public Node
{
public:
    StructDefinition(NodePtr name, NodePtr body);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override {}
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif