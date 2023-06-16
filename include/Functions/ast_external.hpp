#ifndef ast_extarnal_hpp
#define ast_extarnal_hpp

#include "ast_node.hpp"

class External: public Node
{
public:
    External(NodePtr type,NodePtr name);
    External(NodePtr type,NodePtr name, NodePtr params);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override {}
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif