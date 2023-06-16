#ifndef ast_type_hpp
#define ast_type_hpp

#include "ast_node.hpp"

class Type : public Node
{

private:
    std::string value;
public:
    Type(std::string type);
    // void DebugPrint() const override;
    std::string getType(Program_Data &program_data) override {return value;}

};

#endif