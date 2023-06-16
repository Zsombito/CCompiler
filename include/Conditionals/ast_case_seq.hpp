#ifndef ast_case_seq_hpp
#define ast_case_seq_hpp

#include "ast_node.hpp"

class CaseSeq : public Node
{
public:
    CaseSeq(NodePtr seq, NodePtr cas);
    CaseSeq(NodePtr cas);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;

};

#endif