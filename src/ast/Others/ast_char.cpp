#include "Others/ast_char.hpp"


Char::Char(std::string _value)
{
    value = _value[1];
}

void Char::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    output << "li $" << destReg << ", " << int(value) << std::endl;
}