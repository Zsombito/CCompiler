#include "Others/ast_number.hpp"

void Number::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    output << "li $" << destReg << ", " << value << std::endl;
}
Number::Number(double number)
    {
        value = (int)number;
    }
int Number::getValue()
{
    return value;
}
