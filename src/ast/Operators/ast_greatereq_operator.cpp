#include "Operators/ast_greatereq_operator.hpp"

GreaterEqOperator::GreaterEqOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void GreaterEqOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
{
    std::string realType = branches[0]->getType(program_data);
    if(realType != "float")
    {
    //Executes left branch into leftReg, executes right branch into rightReg
        int leftReg = ExecuteLeft(output, program_data, destReg, branches[0]->getType(program_data));
        if(branches[1]->isFunctionCall() == true)
        {
            output << "sw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        int rightReg = ExecuteRight(output, program_data, destReg, branches[1]->getType(program_data));
        if(branches[1]->isFunctionCall() == true)
        {
            output << "lw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        //Adds them together into destReg
        output << "sub $" << destReg << ", $" << rightReg << ", $" << leftReg << std::endl;
        output << "slti $" << destReg << ", $" << destReg << ", 1" << std::endl;
        //Sets leftreg and rightreg unused so they can be reused
        program_data.SetRegisterUnused(leftReg);
        program_data.SetRegisterUnused(rightReg);
    }
    else
    {
        int leftReg = ExecuteLeft(output, program_data, destReg, branches[0]->getType(program_data));
        if(branches[1]->isFunctionCall() == true)
        {
            output << "s.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        int rightReg = ExecuteRight(output, program_data, destReg, branches[1]->getType(program_data));
        if(branches[1]->isFunctionCall() == true)
        {
            output << "l.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        //Adds them together into destReg
        std::string label_zero = program_data.LabelGenerator("label_zero");
        std::string label_end = program_data.LabelGenerator("label_end");
        
        output << "c.le.s"  << " $f" << rightReg << ", $f" << leftReg << std::endl;
        output << "bc1t " << label_zero << std::endl;
        output << "nop" << std::endl;
        output << "addiu $" << destReg << ", $0, 0" << std::endl;
        output << "b " << label_end << std::endl;
        output << "nop" << std::endl;
        output << label_zero << ":" << std::endl;
        output << "addiu $" << destReg << ", $0, 1" << std::endl;
        output << label_end << ":" << std::endl;
        //Sets leftreg and rightreg unused so they can be reused
        program_data.SetRegisterUnused(leftReg);
        program_data.SetRegisterUnused(rightReg);
    }
}
