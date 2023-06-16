#ifndef ast_root_hpp
#define ast_root_hpp

#include "ast_node.hpp"

class Root : public Node
{
public:
    Root(NodePtr program);
    
};

#endif