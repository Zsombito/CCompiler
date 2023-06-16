#ifndef ast_assign_hpp
#define ast_assign_hpp

#include "ast_node.hpp"

class Assign : public Node
{
public:
    Assign(NodePtr varName, NodePtr value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    // void DebugPrint() const override;
};




#endif