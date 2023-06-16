#ifndef ast_function_call_hpp
#define ast_function_call_hpp

#include "ast_node.hpp"

class FunctionCall : public Node
{
public: 
    FunctionCall(NodePtr name);
    FunctionCall(NodePtr name, NodePtr args);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override; 
    void FunctionCallParse(Program_Data &program_data, std::string functionName) override;
    bool isFunctionCall() override {return true;}
    
};

#endif