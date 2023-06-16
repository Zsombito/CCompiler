#ifndef ast_lshift_operator_hpp
#define ast_lshift_operator_hpp

#include "ast_operator_master.hpp"

class LShiftOperator : public Operator
{
public:
    // void DebugPrint() const override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    LShiftOperator(NodePtr left, NodePtr right);
    // void DebugPrint() const override;
};















#endif