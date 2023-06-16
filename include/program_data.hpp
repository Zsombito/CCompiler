#ifndef program_data_hpp
#define program_data_hpp

#include <string>
#include <map>
#include <vector>

#include <iostream>

class Program_Data
{
private:
    bool registers[32]; //Storing which registers are ready for functions to use
    bool floatRegisters[16] = {true, false, false, false, false, false, true, true, false, false, false, false, false, false, false, false};
    int uniqueCounter;
public:
    std::string currentFunctionName;
    std::string currentExtern;
    std::string currentFunctionCall;
    std::string currentPointerAssignType;
    std::string currentStructDef;
    int currentScopeNumber;
    bool isFunctionCallParse = false;
    bool isStructDef = false;
    struct Variable{
        int argumentNumber = -1;
        int stack_offset;
        bool pointer = false;
        std::string pointerType;
        std::string type;
    };
    struct Enum{
        std::map<std::string, int> enumVarBindings;
        int uniqueEnumCounter;
    };
    struct StructDef{
    public:
        int stacksize = 0;
        int size = 0;
        std::map<std::string, Variable> memberBindings;
        int SearchMemberOffset(std::string name)
        {
            return memberBindings[name].stack_offset;

        };
        std::string SearchMemberType(std::string name)
        {
            return memberBindings[name].type;
        };
        void AddMember(std::string name, std::string type)
        {
            Variable v;
            v.stack_offset = stacksize;
            v.type = type;
            stacksize += 4;
            memberBindings.insert(std::pair<std::string, Variable>(name, v));
            if(type == "char")
                size += 1;
            else
                size += 4;
        };
    };
    struct StructVar{
        int offset;
        std::string structname;
    };
    struct Array{
        int startOffset;
        int memberSize;
        int memberNumber;
        std::string type;
        bool isCharArrey = false;
    };
    struct Scope
    {
        std::string startLabel, endLabel;
        int depth, parentScopeId;
        std::map<std::string, Variable> variableBindings;
        std::map<std::string, Array> arreyBindings;
        std::map<std::string, StructVar> structVars;
    };
    struct FunctionCall
    {
        std::string name;
        int uniqueArgCounter = 0;
        int stacksize;
    };
    struct Externs
    {
        std::string functionType;
        std::vector<std::string> paramTypes;
    };
    struct Function
    {
        std::string type;
        int params = 0;
        std::vector<std::string> paramTypes;
        int uniqueVarCounter = 0;
        int uniqueParamCounter = 0;
        int currentFunctionCallId = -1;
        int currentScope = 0;
        std::string currentArrey;
        std::vector<Scope> scopes;
        std::vector<FunctionCall> functionCalls;
       
        int stackSize;
        int returnAdress;
        int end;
    };
    Program_Data();
    int GetEmptyRegister();
    void SetRegisterUsed(int index);
    void SetRegisterUnused(int index);
    void EnterScope(std::string functionName);
    void ExitScope(std::string functionName);
    void CreateVariable(std::string name, std::string functionName, std::string type);
    void CreateFunction(std::string name, std::string type);
    void CreateParameter(std::string name, std::string functionName, std::string type);
    void CreateParameter(std::string name, std::string functionName, std::string type, std::string pointerType);
    void CreateFunctionCall(std::string name, std::string functionName);
    void CreateArray(std::string name, std::string functionName, std::string type);
    void CreateArray(std::string name, std::string functionName, int numberOfElements, std::string type);
    int AddArrayElement(std::string functionName);
    int FindArrayOffset(std::string name, int arreyIndex);
    int CreateArgs(std::string functionName);
    void CreateEnum(std::string enumName);
    void AddEnum(std::string enumName, std::string enumVarName);
    void AddEnum(std::string enumName, std::string enumVarName, int enumNumber);
    void AddExtern(std::string name, std::string type);
    void AddExternParameter(std::string type);
    int GetEmptyFloatRegister();
    void SetFloatRegisterUnused(int index);
    void CreatePointer(std::string functionName, std::string pointerName, std::string pointerType);
    void GenerateStringArrey(std::string name, std::string value, std::string functionName);
    void CreateStruct(std::string name);
    void AddStructVariable(std::string name, std::string structname, std::string functionName);
    std::string SearchForArgType(int argNumber);
    std::string SearchEnums(std::string enumVarName);
    std::string LabelGenerator(std::string basename);
    std::map<std::string, Function> functions;
    std::map<std::string, Enum> enums;
    std::map<std::string, std::string> globalTypes;
    std::map<std::string, Externs> externs;
    std::map<std::string, StructDef> structBindings;
    
    
    

    
    
    


};
















#endif