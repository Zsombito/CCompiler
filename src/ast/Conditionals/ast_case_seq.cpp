#include "Conditionals/ast_case_seq.hpp"

CaseSeq::CaseSeq(NodePtr cas)
{
    branches.push_back(cas);
}
CaseSeq::CaseSeq(NodePtr seq, NodePtr cas)
{
    branches.push_back(seq);
    branches.push_back(cas);
}
void CaseSeq::VariableParse(Program_Data &program_data, std::string functionName)
{
    if(branches.size() == 1)
    {
        branches[0]->VariableParse(program_data, functionName);
    }
    else
    {
        branches[0]->VariableParse(program_data, functionName);
        branches[1]->VariableParse(program_data, functionName);
    }
}
void CaseSeq::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    branches[0]->CodeGen(output, program_data, destReg, type);
    if(branches.size() == 2)
        branches[1]->CodeGen(output, program_data, destReg, type);
}