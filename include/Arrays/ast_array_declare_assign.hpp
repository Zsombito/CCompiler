#ifndef ast_array_declare_assign_hpp
#define ast_array_declare_assign_hpp

#include "ast_node.hpp"

class ArrayDeclareAssign : public Node
{ 
public: 
    ArrayDeclareAssign(NodePtr type, NodePtr name, NodePtr args);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    void FunctionCallParse(Program_Data &program_data, std::string functionName) override;
};
#endif