#ifndef ast_string_hpp
#define ast_string_hpp

#include "ast_node.hpp"

class String : public Node
{
private:
    std::string value;
public:
    String(std::string _value);
    std::string getString() override {return value;}
};

#endif