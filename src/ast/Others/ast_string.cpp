#include "Others/ast_string.hpp"

String::String(std::string _value)
{
    value = _value;
    value.erase(0, 1);
    value.erase(value.size()-1, 1);

}
