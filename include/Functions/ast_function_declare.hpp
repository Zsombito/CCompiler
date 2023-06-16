#ifndef ast_function_declare_hpp
#define ast_function_declare_hpp

#include "ast_node.hpp"

class FunctionDeclaration : public  Node
{
public:
    FunctionDeclaration(NodePtr fun_type, NodePtr name, NodePtr body);
    FunctionDeclaration(NodePtr fun_type, NodePtr name, NodePtr body, NodePtr args);

    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override; //removed override
    // void DebugPrint() const override;

};


#endif