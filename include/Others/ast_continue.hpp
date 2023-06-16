#ifndef ast_continue_hpp
#define ast_continue_hpp

#include "ast_node.hpp"

class Continue : public Node
{
public:
    Continue();
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif