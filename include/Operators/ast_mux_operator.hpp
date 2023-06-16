#ifndef ast_mux_operator_hpp
#define ast_mux_operator_hpp

#include "ast_node.hpp"

class MuxOperator : public Node 
{
public:
    MuxOperator(NodePtr condition, NodePtr trueExecutant, NodePtr falseExecutant);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    // void DebugPrint() const override;
};




#endif