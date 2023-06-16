#ifndef ast_number_hpp
#define ast_number_hpp

#include "ast_node.hpp"

class Number : public Node 
{
private:
    int value;
public:
    Number(double number) ;
    int getValue() override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    // void DebugPrint() const override;
    std::string getType(Program_Data &program_data) override {return "int";}
};

#endif