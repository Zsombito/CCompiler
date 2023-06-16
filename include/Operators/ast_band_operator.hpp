#ifndef ast_band_operator_hpp
#define ast_band_operator_hpp

#include "ast_operator_master.hpp"

class BAndOperator : public Operator
{
public:
    // void DebugPrint() const override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    BAndOperator(NodePtr left, NodePtr right);
    // void DebugPrint() const override;
};















#endif