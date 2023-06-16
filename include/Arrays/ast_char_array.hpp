#ifndef ast_char_array_hpp
#define ast_char_array_hpp

#include "ast_node.hpp"

class CharArrey : public Node
{
public:
    CharArrey(NodePtr name, NodePtr string);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif