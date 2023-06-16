#ifndef ast_block_seq_hpp
#define ast_block_seq_hpp

#include "ast_node.hpp"

class BlockSeq : public Node
{
public:
    BlockSeq(NodePtr branch1, NodePtr branch2)
    {
        branches.push_back(branch1);
        branches.push_back(branch2);
    }
    void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const override
    {
        branches[0]->CodeGen(output, program_data, destReg, type);
        if(branches[1] != NULL)
            branches[1]->CodeGen(output, program_data, destReg, type);
    }
    // void DebugPrint() const override
    // {
    //     std::cout << "BlockSeq(" ;
    //     branches[0]->DebugPrint();
    //     std::cout << ", " ;
    //     branches[1]->DebugPrint() ;
    //     std::cout <<")" ;
    // }
};


#endif
