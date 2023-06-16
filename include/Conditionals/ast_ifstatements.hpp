#ifndef ast_ifstatements_hpp
#define ast_ifstatements_hpp

#include "ast_node.hpp"

class IfStatment : public Node
{
public:
    IfStatment(NodePtr condition, NodePtr executant);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    // void DebugPrint() const override;
};












#endif