#ifndef ast_operator_hpp
#define ast_operator_hpp

#include "ast_node.hpp"


class Operator : public Node 
{
public:
    int ExecuteLeft(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const;
    int ExecuteRight(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const;
    std::string getType(Program_Data &program_data) override {return branches[0]->getType(program_data);}
    // void DebugPrint() const override;
};







#endif