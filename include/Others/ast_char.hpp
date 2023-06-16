#ifndef ast_char_hpp
#define ast_char_hpp

#include "ast_node.hpp"

class Char : public Node
{
private:
    char value;
public:
    Char(std::string _value);
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override;
};

#endif