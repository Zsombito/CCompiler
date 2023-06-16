#ifndef ast_break_hpp
#define ast_break_hpp

#include "ast_node.hpp"

class Break : public Node
{
public:
    Break();
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif