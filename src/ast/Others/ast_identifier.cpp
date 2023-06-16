#include "Others/ast_identifier.hpp"

void Identifier::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
{
    std::string enumName = program_data.SearchEnums(name);
    std::string realtype ;
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings.count(name) > 0)
        {
            if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings[name].isCharArrey)
            {
                realtype =  "char";
            }
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    
    if(enumName == "")
    {
    std::string varType = "none";
    currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(name) > 0)
        {
            varType = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[name].type;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    if(varType != "none")
    {
        realtype =  varType;
    }
    else
    {
        realtype =  program_data.globalTypes[name];
    }
    }
    else
    {
        realtype =  "int";
    }
    enumName = program_data.SearchEnums(name);
    if(enumName == "")
    {
        int variable_offset = -9;
        int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
        int currentScope = scopeNumber;
        for(int i = 0; i < currentDepth + 1; i++)
        {
            if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(name) > 0)
            {
                variable_offset = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[name].stack_offset;
                break;
            }
            if(i != currentDepth)
                currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
        }
        if(variable_offset != -9)
        {
            
            if(realtype == "int" || realtype == "unsigned" || realtype == "pointer")
            {
                
                output << "lw $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
            }
            else if(realtype == "float")
                output << "l.s $f"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
            else if(realtype == "char")
                output << "lb $"<< destReg << ", " << variable_offset << "($sp)" << std::endl;
        }
        else
        {
            output << "lw $" << destReg << ", " << name << std::endl;
        }
    }
    else
    {
        output << "li $" << destReg << ", " <<program_data.enums[enumName].enumVarBindings[name] << std::endl;
    }
}
void Identifier::VariableParse(Program_Data &program_data, std::string functionName)
{
    
    if(functionName != "global")
    {
        
        scopeNumber = program_data.functions[functionName].currentScope;
        
    }
    else
        scopeNumber = -1;
    
}
std::string Identifier::getType(Program_Data &program_data)
{
    
    std::string enumName = program_data.SearchEnums(name);
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings.count(name) > 0)
        {
            if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings[name].isCharArrey)
            {
                return "char";
            }
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    
    if(enumName == "")
    {
            std::string varType = "none";
            currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
            currentScope = scopeNumber;
            for(int i = 0; i < currentDepth + 1; i++)
            {
                if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(name) > 0)
                {
                    varType = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[name].type;
                    break;
                }
                if(i != currentDepth)
                    currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
            }
            if(varType != "none")
            {
                return varType;
            }
            else
            {
                currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
                currentScope = scopeNumber;
                for(int i = 0; i < currentDepth + 1; i++)
                {
                    if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings.count(name) > 0)
                    {
                        return program_data.functions[program_data.currentFunctionName].scopes[currentScope].arreyBindings[name].type;
                        break;
                    }
                    if(i != currentDepth)
                        currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
                }
                return program_data.globalTypes[name];
            }
    }
    else
    {
        return "int";
    }
}
std::string Identifier::getPointerType(Program_Data &program_data)
{
    std::string varType = "none";
    int currentDepth = program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].depth;
    int currentScope = scopeNumber;
    for(int i = 0; i < currentDepth + 1; i++)
    {
        if(program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings.count(name) > 0)
        {
            varType = program_data.functions[program_data.currentFunctionName].scopes[currentScope].variableBindings[name].pointerType;
            break;
        }
        if(i != currentDepth)
            currentScope = program_data.functions[program_data.currentFunctionName].scopes[currentScope].parentScopeId;
    }
    
    return varType;
}
