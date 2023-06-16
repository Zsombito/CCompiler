#ifndef ast_case_hpp
#define ast_case_hpp

#include "ast_node.hpp"

class Case : public Node
{
public:
    Case(NodePtr value, NodePtr body);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;

};

#endif