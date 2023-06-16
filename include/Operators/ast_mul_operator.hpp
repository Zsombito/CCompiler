#ifndef ast_mul_operator_hpp
#define ast_mul_operator_hpp

#include "ast_operator_master.hpp"

class MulOperator : public Operator
{
public:
    // void DebugPrint() const override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    MulOperator(NodePtr left, NodePtr right);
    // void DebugPrint() const override;
};















#endif