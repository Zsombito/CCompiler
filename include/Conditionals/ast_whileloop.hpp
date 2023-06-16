#ifndef ast_whileloop_hpp
#define ast_whileloop_hpp

#include "ast_node.hpp"

class WhileLoop : public Node
{
public:
    WhileLoop(NodePtr condition, NodePtr executant);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    // void DebugPrint() const override;
};












#endif