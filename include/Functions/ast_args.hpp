#ifndef ast_args_hpp
#define ast_args_hpp

#include "ast_node.hpp"

class Arguments: public Node
{
private:
    int argNumber1 = -1;
    int argNumber2 = -1;
    bool ArreyDec = true;
    std::string ArreyName;
public:
    Arguments(NodePtr mux);
    Arguments(NodePtr seq, NodePtr mux);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override; 
    void FunctionCallParse(Program_Data &program_data, std::string functionName) override;
    void EnumParse(Program_Data &program_data, std::string enumName) override;
    bool argSeq() override {return true;}
};

#endif