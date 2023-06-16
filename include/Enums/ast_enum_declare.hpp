#ifndef ast_enum_declare_hpp
#define ast_enum_declare_hpp

#include "ast_node.hpp"

class EnumDeclare : public Node
{
public:
    EnumDeclare(NodePtr name, NodePtr enumVariables);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override {}
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    void FunctionCallParse(Program_Data &program_data, std::string functionName) override {}
};

#endif