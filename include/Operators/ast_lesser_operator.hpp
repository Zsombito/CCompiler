#ifndef ast_lesser_operator_hpp
#define ast_lesser_operator_hpp

#include "ast_operator_master.hpp"

class LesserOperator : public Operator
{
public:
    // void DebugPrint() const override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    LesserOperator(NodePtr left, NodePtr right);
    // void DebugPrint() const override;
};















#endif