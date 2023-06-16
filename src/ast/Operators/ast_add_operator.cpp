#include "Operators/ast_add_operator.hpp"

AddOperator::AddOperator(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}
void AddOperator::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const 
{
    
    //Executes left branch into leftReg, executes right branch into rightReg
    if(type == "int" || type == "unsigned" )
    {
        int leftReg = ExecuteLeft(output, program_data, destReg, type);
        if(branches[1]->isFunctionCall() == true)
        {
            output << "sw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        
        int rightReg = ExecuteRight(output, program_data, destReg, type);
        if(branches[1]->isFunctionCall() == true)
        {
            output << "lw $" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        //Adds them together into destReg
        if(type == "int")
            output << "add $" << destReg << ", $" << leftReg << ", $" << rightReg << std::endl;
        else if(type == "unsigned")
            output << "addu $" << destReg << ", $" << leftReg << ", $" << rightReg << std::endl;
        
        
        //Sets leftreg and rightreg unused so they can be reused
        program_data.SetRegisterUnused(leftReg);
        program_data.SetRegisterUnused(rightReg);
    }




    else if(type == "float")
    {
        
        int leftReg = ExecuteLeft(output, program_data, destReg, type);
        if(branches[1]->isFunctionCall() == true)
        {
            output << "s.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        
        int rightReg = ExecuteRight(output, program_data, destReg, type);
        if(branches[1]->isFunctionCall() == true)
        {
            output << "l.s $f" << leftReg << ", " << (program_data.functions[program_data.currentFunctionName].stackSize - 8) << "($sp)" << std::endl;
        }
        //Adds them together into destReg
    
        output << "add.s $f" << destReg << ", $f" << leftReg << ", $f" << rightReg << std::endl;
        //Sets leftreg and rightreg unused so they can be reused
        program_data.SetRegisterUnused(leftReg);
        program_data.SetRegisterUnused(rightReg);
    }
    else if(type == "pointer")
    {
        
        int pointerReg, additionReg;
        if(branches[0]->getType(program_data) == "pointer")
             pointerReg = ExecuteLeft(output, program_data, destReg, "pointer");
        else
             additionReg = ExecuteLeft(output, program_data, destReg, "int");
        if(branches[1]->getType(program_data) == "pointer")
             pointerReg = ExecuteRight(output, program_data, destReg, "pointer");
        else
             additionReg = ExecuteRight(output, program_data, destReg, "int");
        if(program_data.currentPointerAssignType != "char")
            output << "sll $" << additionReg << ", $" << additionReg << ", 2" << std::endl;
        output << "add $" << destReg << ", $" << pointerReg << ", $" << additionReg << std::endl;
        
    }
    

    
}
