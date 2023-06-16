#include "program_data.hpp"

Program_Data::Program_Data()
{
    //Loading all values with true which are not temporary ones
    for(int i = 0; i < 32; i++)
        registers[i] = false;
    for(int i = 8; i < 16; i++)
        registers[i] = true;
    registers[24] = false;
    registers[25] = false;
    uniqueCounter = 0;
    
    
}
int Program_Data::GetEmptyRegister()
{
    for(int i = 0; i < 32; i++)
    {
        if(registers[i] == true)
        {
            registers[i] = false;
            return i;
        }
    }
}
void Program_Data::SetRegisterUsed(int index){registers[index] = false;}
void Program_Data::SetRegisterUnused(int index){registers[index] = true;}
std::string Program_Data::LabelGenerator(std::string basename)
{
    uniqueCounter++;
    return basename + std::to_string(uniqueCounter);
}
void Program_Data:: CreateVariable(std::string name, std::string functionName, std::string type)
{
    if(type == "int" || type == "unsigned" || type == "float" || type == "char")
    {
        Variable v;
        v.type = type;
        v.stack_offset = functions[functionName].uniqueVarCounter;
        functions[functionName].uniqueVarCounter += 4;
        functions[functionName].stackSize += 4;
        functions[functionName].scopes[functions[functionName].currentScope].variableBindings.insert(std::pair<std::string, Variable>(name, v));
    }
    
}
void Program_Data::CreateFunction(std::string name, std::string type)
{
    Function f;
    Scope s;
    s.depth = 0;
    f.scopes.push_back(s);
    f.type = type;
    functions.insert(std::pair<std::string, Function>(name, f));
    functions[name].stackSize = 8;
    
}
void Program_Data::EnterScope(std::string functionName)
{
    Scope s;
    s.parentScopeId = functions[functionName].currentScope;
    s.depth = functions[functionName].scopes[functions[functionName].currentScope].depth + 1;
    functions[functionName].scopes.push_back(s);
    functions[functionName].currentScope = functions[functionName].scopes.size() - 1;

}
void Program_Data::ExitScope(std::string functionName)
{
    functions[functionName].currentScope = functions[functionName].scopes[functions[functionName].currentScope].parentScopeId;
}
void Program_Data::CreateParameter(std::string name, std::string functionName, std::string type)
{
    
    Variable v;
    v.type = type;
    v.stack_offset = functions[functionName].stackSize + functions[functionName].uniqueParamCounter;
    v.argumentNumber = functions[functionName].params;
    functions[functionName].uniqueParamCounter += 4;
    functions[functionName].params += 1;
    functions[functionName].scopes[0].variableBindings.insert(std::pair<std::string, Variable>(name, v));
    functions[functionName].paramTypes.push_back(type);
    
}
void Program_Data::CreateParameter(std::string name, std::string functionName, std::string type, std::string pointerType)
{
    
    Variable v;
    v.type = type;
    v.pointerType = pointerType;
    v.stack_offset = functions[functionName].stackSize + functions[functionName].uniqueParamCounter;
    v.argumentNumber = functions[functionName].params;
    functions[functionName].uniqueParamCounter += 4;
    functions[functionName].params += 1;
    functions[functionName].scopes[0].variableBindings.insert(std::pair<std::string, Variable>(name, v));
    functions[functionName].paramTypes.push_back(type);
    
}
void Program_Data::CreateFunctionCall(std::string name, std::string functionName)
{
    FunctionCall fc;
    fc.name = name;
    fc.stacksize  =0;
    functions[functionName].functionCalls.push_back(fc);
    functions[functionName].currentFunctionCallId = functions[functionName].functionCalls.size() -1;
}
int Program_Data::CreateArgs(std::string functionName)
{
    functions[functionName].functionCalls[functions[functionName].currentFunctionCallId].stacksize += 4;
    functions[functionName].functionCalls[functions[functionName].currentFunctionCallId].uniqueArgCounter++;
    return functions[functionName].functionCalls[functions[functionName].currentFunctionCallId].uniqueArgCounter;
}

void Program_Data::CreateArray(std::string name, std::string functionName, int numberOfElements, std::string type)
{
    Array a;
    a.memberNumber = numberOfElements;
    a.startOffset = functions[functionName].uniqueVarCounter;
    if(type == "char")
    {
        a.memberSize = 1;
        functions[functionName].uniqueVarCounter += ((a.memberNumber * a.memberSize) / 4 + 1)*4 ;
        functions[functionName].stackSize += ((a.memberNumber * a.memberSize) / 4 + 1)*4 ;
    }
    else
    {
        a.memberSize = 4;
        functions[functionName].uniqueVarCounter += a.memberNumber * a.memberSize;
        functions[functionName].stackSize += a.memberNumber * a.memberSize;
        
    }
    
    
    a.type = type;
    functions[functionName].scopes[functions[functionName].currentScope].arreyBindings.insert(std::pair<std::string, Array>(name, a));
    
}
void Program_Data::CreateArray(std::string name, std::string functionName, std::string type)
{
    Array a;
    a.startOffset = functions[functionName].uniqueVarCounter;
    a.memberSize = 4;
    a.memberNumber = 0;
    a.type;
    functions[functionName].scopes[functions[functionName].currentScope].arreyBindings.insert(std::pair<std::string, Array>(name, a));
    functions[functionName].currentArrey = name;
}
int Program_Data::AddArrayElement(std::string functionName)
{
    functions[functionName].scopes[functions[functionName].currentScope].arreyBindings[functions[functionName].currentArrey].memberNumber += 1;
    functions[functionName].uniqueVarCounter += functions[functionName].scopes[functions[functionName].currentScope].arreyBindings[functions[functionName].currentArrey].memberSize;
    functions[functionName].stackSize += functions[functionName].scopes[functions[functionName].currentScope].arreyBindings[functions[functionName].currentArrey].memberSize;
    return functions[functionName].scopes[functions[functionName].currentScope].arreyBindings[functions[functionName].currentArrey].memberNumber - 1;
}
void Program_Data::CreateEnum(std::string enumName)
{
    Enum e;
    e.uniqueEnumCounter = -1;
    enums.insert(std::pair<std::string, Enum>(enumName, e));
}
void Program_Data::AddEnum(std::string enumName, std::string enumVarName)
{
    enums[enumName].uniqueEnumCounter++;
    enums[enumName].enumVarBindings.insert(std::pair<std::string, int>(enumVarName, enums[enumName].uniqueEnumCounter));
}
void Program_Data::AddEnum(std::string enumName, std::string enumVarName, int enumNumber)
{
    enums[enumName].uniqueEnumCounter = enumNumber;
    enums[enumName].enumVarBindings.insert(std::pair<std::string, int>(enumVarName, enums[enumName].uniqueEnumCounter));
}
std::string Program_Data::SearchEnums(std::string enumVarName)
{
    std::map<std::string, Enum>::iterator it;
    std::string enumName = "";
    for(it = enums.begin(); it != enums.end(); it++)
    {
        if(enums[it->first].enumVarBindings.count(enumVarName) >= 0)
        {
            enumName = it->first;
            break;
        }
    }
    return enumName;
}
void Program_Data::AddExtern(std::string name, std::string type)
{
    Externs e;
    e.functionType = type;
    externs.insert(std::pair<std::string , Externs>(name, e));
    currentExtern = name;
}
void Program_Data::AddExternParameter(std::string type)
{
    externs[currentExtern].paramTypes.push_back(type);
}
std::string Program_Data::SearchForArgType(int argNumber)
{
    
    if(externs.count(currentFunctionCall) != 0)
        return externs[currentFunctionCall].paramTypes[argNumber-1];
    else
        return functions[currentFunctionCall].paramTypes[argNumber-1];
}
int Program_Data::GetEmptyFloatRegister()
{
    for(int i = 0; i < 16; i++)
    {
        if(floatRegisters[i] == false)
        {
            floatRegisters[i] = true;
            return i*2;
        }
    }
}
void Program_Data::SetFloatRegisterUnused(int index)
{
    floatRegisters[index/2] = false;
}
void Program_Data::CreatePointer(std::string functionName, std::string pointerName, std::string pointerType)
{
    Variable v;
    v.pointer = true;
    v.pointerType = pointerType;
    v.type = "pointer";
    v.stack_offset = functions[functionName].uniqueVarCounter;
    functions[functionName].uniqueVarCounter += 4;
    functions[functionName].stackSize += 4;
    functions[functionName].scopes[functions[functionName].currentScope].variableBindings.insert(std::pair<std::string, Variable>(pointerName, v));
}
void Program_Data::GenerateStringArrey(std::string name, std::string value, std::string functionName)
{
    Array a;
    a.startOffset = functions[functionName].uniqueVarCounter;
    a.memberSize = 1;
    a.memberNumber = value.length() + 1;
    a.isCharArrey = true;
    int size = ((value.length() + 1 / 4) + 1) * 4;
    functions[functionName].uniqueVarCounter += size;
    functions[functionName].stackSize += size;
    functions[functionName].scopes[functions[functionName].currentScope].arreyBindings.insert(std::pair<std::string, Array>(name, a));
}
void Program_Data::CreateStruct(std::string name)
{
    StructDef d;
    structBindings.insert(std::pair<std::string, StructDef>(name, d));
}
void Program_Data::AddStructVariable(std::string name, std::string structname, std::string functionName)
{
    StructVar s;
    s.offset = functions[functionName].uniqueVarCounter;
    s.structname = structname;
    functions[functionName].uniqueVarCounter += structBindings[structname].stacksize;
    functions[functionName].stackSize += structBindings[structname].stacksize;
    functions[functionName].scopes[currentScopeNumber].structVars.insert(std::pair<std::string, StructVar>(name, s));
    
}