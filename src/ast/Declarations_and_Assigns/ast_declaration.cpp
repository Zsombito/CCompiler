#include "Declarations_and_Assigns/ast_declaration.hpp"

Declaration::Declaration(NodePtr var_type, NodePtr name)
{
    branches.push_back(var_type);
    branches.push_back(name);
    
}
void Declaration::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{  
    if(scopeNumber == -1)
    {
        output << ".data" << std::endl;
        output << branches[1]->getName() << ":"<< std::endl;
        program_data.globalTypes.insert(std::pair<std::string, std::string>(branches[1]->getName(), branches[0]->getType(program_data)));
    }
}
void Declaration::VariableParse(Program_Data &program_data, std::string functionName)
{
    if(functionName != "global" && program_data.isStructDef == false)
    {
       scopeNumber = program_data.functions[functionName].currentScope;
       program_data.CreateVariable(branches[1]->getName(), functionName, branches[0]->getType(program_data));
        
    }
    else if(program_data.isStructDef == true)
    {
        program_data.structBindings[program_data.currentStructDef].AddMember(branches[1]->getName(), branches[0]->getType(program_data));
    }
    else
    {
        scopeNumber = -1;
    }
    
}