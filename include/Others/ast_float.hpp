#ifndef ast_float_hpp
#define ast_float_hpp

#include "ast_node.hpp"

class Float : public Node
{
private:
    float value;
public:
    Float(double _value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
    std::string getType(Program_Data &program_data) override {return "float";}
    float getFloat() override {return value; }

};

#endif