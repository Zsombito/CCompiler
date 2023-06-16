#ifndef ast_block_hpp
#define ast_block_hpp

#include "ast_node.hpp"

class Block : public Node
{
public:
    Block(NodePtr block)
    {
        branches.push_back(block);
    }
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override
    {
        branches[0]->CodeGen(output, program_data, destReg, type);
    }
    // void DebugPrint() const override
    // {
    //     std::cout << "Block(";
    //     branches[0]->DebugPrint();
    //     std::cout << ")";
    // }
};


#endif
