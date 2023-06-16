#include "Others/ast_float.hpp"

Float::Float(double _value)
{
    value = (float)_value;
}
void Float::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    output << "li.s $f" << destReg << ", " << value << std::endl;
}