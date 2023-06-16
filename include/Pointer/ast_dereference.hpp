#ifndef ast_dereference_hpp
#define ast_dereference_hpp

#include "ast_node.hpp"

class Dereference : public Node
{
public:
    Dereference(NodePtr pointer);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    std::string getType(Program_Data &program_data) override;
};

#endif