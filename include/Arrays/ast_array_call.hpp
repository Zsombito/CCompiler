#ifndef ast_array_call_hpp
#define ast_array_call_hpp

#include "ast_node.hpp"

class ArrayCall : public Node
{
public:
    ArrayCall(NodePtr name, NodePtr index);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif