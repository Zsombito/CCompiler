#ifndef ast_line_hpp
#define ast_line_hpp

#include "ast_node.hpp"

class Line : public Node
{
public:
    Line(NodePtr line)
    {
        branches.push_back(line);
    }
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override
    {
        branches[0]->CodeGen(output, program_data, destReg, type);
    }
    /*void DebugPrint() const override
    {
        std::cout << "Block(";
        branches[0]->DebugPrint();
        std::cout << ")";
    } */
};


#endif
