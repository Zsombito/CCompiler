#ifndef unary_master_hpp
#define unary_master_hpp

#include "ast_node.hpp"

class Unary : public Node
{
public:
    int ExecuteOperand(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const;
    // void DebugPrint() const override;
    
};




#endif