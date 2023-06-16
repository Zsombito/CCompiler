#ifndef ast_address_of_hpp
#define ast_address_of_hpp

#include "ast_node.hpp"

class Address : public Node
{
public:
    Address(NodePtr varialbe);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
};

#endif