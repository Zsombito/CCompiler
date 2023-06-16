#ifndef ast_empty_scope_hpp
#define ast_empty_scope_hpp

#include "ast_node.hpp"

class EmptyScope : public Node
{
public:
    EmptyScope(NodePtr body);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};
#endif