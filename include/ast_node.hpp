#ifndef node_hpp
#define node_hpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "program_data.hpp"

class Node;

typedef Node *NodePtr;
class Node
{
protected:
    
    int scopeNumber = 0;
public:
    std::vector<NodePtr> branches;
    Node();
    Node(std::vector<NodePtr> _branches);
    ~Node() ;
    // virtual void DebugPrint() const{};

    virtual void CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const;
    virtual void VariableParse(Program_Data &program_data, std::string functionName);
    virtual void FunctionCallParse(Program_Data &program_data, std::string functionName);
    virtual void EnumParse(Program_Data &program_data, std::string enumName){}
    virtual void ExternParse(Program_Data &program_data, std::string functionName){}

    //For identifiers
    virtual std::string getName() const;
    virtual bool argSeq(){return false;}
    virtual bool paramSeq(){return false;}
    virtual bool isFunctionCall(){return false;}
    virtual int getValue(){return -1;}
    virtual std::string getType(Program_Data &program_data) {return "";}
    virtual float getFloat(){return -1.0f;}
    virtual bool isPointerDeclare(){return false;}
    virtual std::string getPointerType(Program_Data &program_data){return "int";}
    virtual std::string getString(){return "";}
    virtual int getStructOffset(Program_Data &program_data) {return -1;}
    
   

};


#endif