#ifndef ast_params_hpp
#define ast_params_hpp

#include "ast_node.hpp"

class Params : public Node
{
public:
    Params(NodePtr declaration);
    Params(NodePtr argSeq, NodePtr declaration);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override; 
    void ExternParse(Program_Data &program_data, std::string functionName) override;
    bool paramSeq() override {return true;} 

};
#endif