#ifndef ast_struct_index
#define ast_struct_index

#include "ast_node.hpp"

class StructIndex : public Node
{
public:
    StructIndex(NodePtr name, NodePtr var);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    int getStructOffset(Program_Data &program_data) override;
    std::string getType(Program_Data &program_data) override;
};

#endif