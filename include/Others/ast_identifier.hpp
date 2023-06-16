#ifndef ast_identifier_hpp
#define ast_identifier_hpp

#include "ast_node.hpp"

class Identifier : public Node
{
private:
    std::string name;
public: 
    Identifier(std::string _name): name(_name){}
    std::string getName() const override {return name;}
    std::string getType(Program_Data &program_data) override;
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    void VariableParse(Program_Data &program_data, std::string functionName) override;
    std::string getPointerType(Program_Data &program_data) override;
    // void DebugPrint() const override;
};











#endif