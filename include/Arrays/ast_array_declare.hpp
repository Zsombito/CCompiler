#ifndef ast_array_declare_hpp
#define ast_array_declare_hpp

#include "ast_node.hpp"

class ArrayDeclare : public Node
{
public:
    ArrayDeclare(NodePtr type, NodePtr name, NodePtr elementNumber);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif