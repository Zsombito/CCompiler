#include "Operators/ast_mux_operator.hpp"


MuxOperator::MuxOperator(NodePtr condition, NodePtr trueExecutant, NodePtr falseExecutant)
{
    branches.push_back(condition);
    branches.push_back(trueExecutant);
    branches.push_back(falseExecutant);
}
void MuxOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    //Condition execution:
    branches[0]->CodeGen(output, program_data, destReg, type);
    std::string endLabel = program_data.LabelGenerator("endmux");
    std::string elseLabel = program_data.LabelGenerator("elseLabel");

    //Jump to else if false
    output << "beq $0, $" << destReg << ", " << elseLabel << std::endl;
    output << "nop" << std::endl;

    //Execute if it was true and then jump to end
    branches[1]->CodeGen(output, program_data, destReg, type);
    output << "b " << endLabel << std::endl;
    output << "nop";
    
    //Execute else if it was false
    output << elseLabel << ":" << std::endl;
    branches[2]->CodeGen(output, program_data, destReg, type);
    
    output << endLabel << ":" << std::endl;
}
