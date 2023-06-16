#ifndef ast_not_unary_hpp
#define ast_not_unary_hpp

#include "ast_unary_master.hpp"


class NotOperator : public Unary
{
public:
    NotOperator(NodePtr operand);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    // void DebugPrint() const override;
};



#endif