#include "Functions/ast_args.hpp"

Arguments::Arguments(NodePtr mux)
{
     
    branches.push_back(mux);
     
    
}
Arguments::Arguments(NodePtr seq, NodePtr mux)
{
   
    
    branches.push_back(seq);
    branches.push_back(mux);
    
}
void Arguments::FunctionCallParse(Program_Data &program_data, std::string functionName)
{
    ArreyDec=false;
    if(branches.size() == 1)
    {
        argNumber1 = program_data.CreateArgs(functionName);
    }
    else
    {
        if(branches[0]->argSeq())
        {
            branches[0]->FunctionCallParse(program_data,functionName);
            argNumber1 = program_data.CreateArgs(functionName);
        }
        else
        {
            argNumber1 = program_data.CreateArgs(functionName);
            argNumber2 = program_data.CreateArgs(functionName);
        }
    }

    
}
void Arguments::VariableParse(Program_Data &program_data, std::string functionName)
{
    if(functionName != "global")
    {
    scopeNumber = program_data.functions[functionName].currentScope;
    ArreyName = program_data.functions[functionName].currentArrey;
    if(branches.size() == 1)
    {
          
        argNumber1 = program_data.AddArrayElement(functionName);
    }
    else
    {
        if(branches[0]->argSeq())
        {
            
            branches[0]->VariableParse(program_data,functionName);
            
            argNumber1 = program_data.AddArrayElement(functionName);
            
        }
        else
        {
            
            argNumber1 = program_data.AddArrayElement(functionName);
            
            argNumber2 = program_data.AddArrayElement(functionName);
            
        }
    }
    }
    else
    {
        scopeNumber = -1;
    }
    
}
void Arguments::CodeGen(std::ostream &output, Program_Data &program_data, int destReg, std::string type) const
 {
    //Finding the type of the first parameter:
    
    if(ArreyDec == false)
    {
        
        if(branches.size() == 1)
        {
            std::string type1 = program_data.SearchForArgType(argNumber1);
            branches[0]->CodeGen(output, program_data, destReg, type1);
            if(type1 == "unsigned" || type1 == "int")
            {
            
            output << "move $4, $" << destReg << std::endl;
            }
            else if(type1 == "float")
            {
                output << "mov.s $f12, $f" << destReg << std::endl;
            }
        }
        else
        {
            if(branches[0]->argSeq())
            {
                std::string type1 = program_data.SearchForArgType(argNumber1);
                branches[0]->CodeGen(output, program_data, destReg, type);
                branches[1]->CodeGen(output, program_data, destReg, type1);
                if(argNumber1 > 4 )
                {
                    if(type1 == "int" | type1 == "unsigned")
                        output << "sw $" << destReg << ", " << ((argNumber1 - 1) * 4) << "($sp)" << std::endl;
                    else if(type1 == "float")
                        output << "s.s $f" << destReg << ", " << ((argNumber1 - 1) * 4) << "($sp)" << std::endl;
                }
                else
                {
                    if(type1 == "int" | type1 == "unsigned")
                        output << "move $" << (3 + argNumber1) << ", $" << destReg << std::endl;
                    else if(type1 == "float")
                    {
                        output << "s.s $f" << destReg << ", " << ((argNumber1 - 1) * 4) << "($sp)" << std::endl;
                        output << "lw $"<< (3 + argNumber1)<< ", " << ((argNumber1 - 1) * 4) << "($sp)" << std::endl;
                    }
                }
            }
            else
            {
                std::string type1 = program_data.SearchForArgType(argNumber1);
                std::string type2 = program_data.SearchForArgType(argNumber2);
                branches[0]->CodeGen(output, program_data, destReg, type1);
                if(type1 == "int" || type1 == "unsigned")
                    output << "move $4, $" << destReg << std::endl;
                else if(type1 == "float")
                    output << "mov.s $F12, $f" << destReg << std::endl;
                branches[1]->CodeGen(output, program_data, destReg, type2);
                if(type2 == "int" || type2 == "unsigned")
                    output << "move $5, $" << destReg << std::endl;
                else if(type2 == "float")
                    output << "mov.s $f14, $f" << destReg << std::endl;
            
            }
        }
        }
        else
        {
            if(scopeNumber != -1)
            {
            if(branches.size() == 1)
            {
                branches[0]->CodeGen(output, program_data, destReg, type);
                if(type == "int" || type == "unsigned")
                    output << "sw $" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                    + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
                else if(type == "float")
                    output << "s.s $f" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                    + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
            }
            else
            {
                if(branches[0]->argSeq())
                {
                    branches[0]->CodeGen(output, program_data, destReg, type);
                    branches[1]->CodeGen(output, program_data, destReg, type);
                    if(type == "int" || type == "unsigned")
                        output << "sw $" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
                    else if(type == "float")
                        output << "s.s $f" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
                }
                else
                {
                    branches[0]->CodeGen(output, program_data, destReg, type);
                    if(type == "int" || type == "unsigned")
                    {
                        output << "sw $" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
                        branches[1]->CodeGen(output, program_data, destReg, type);
                        output << "sw $" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber2) << "($sp)" << std::endl;
                    }
                    else if(type == "float")
                    {
                        output << "s.s $f" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber1) << "($sp)" << std::endl;
                        branches[1]->CodeGen(output, program_data, destReg, type);
                        output << "s.s $f" << destReg << ", " << (program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].startOffset 
                        + program_data.functions[program_data.currentFunctionName].scopes[scopeNumber].arreyBindings[ArreyName].memberSize * argNumber2) << "($sp)" << std::endl;
                    }
                }

            }
        }
        else
        {
            if(branches.size() == 1)
                output << ".word" <<  branches[0]->getValue() << std::endl;
            else
            {
                if(branches[0]->argSeq())
                {
                branches[0]->CodeGen(output, program_data, destReg, type);
                output << ".word" <<  branches[1]->getValue() << std::endl;
                }
                else
                {
                    output << ".word" <<  branches[0]->getValue() << std::endl;
                    output << ".word" <<  branches[1]->getValue() << std::endl;
                }
            }
        }
    }
 }
 void Arguments::EnumParse(Program_Data &program_data, std::string enumName)
 {
    if(branches.size() == 1)
    {
        if(branches[0]->branches.size() == 0)
        {
            program_data.AddEnum(enumName, branches[0]->getName());
        }
        else
        {
            program_data.AddEnum(enumName, branches[0]->branches[0]->getName(), branches[0]->branches[1]->getValue());
        }
    }
    else
    {
        if(branches[0]->argSeq())
        {
            branches[0]->EnumParse(program_data, enumName);
            if(branches[1]->branches.size() == 0)
            {
                program_data.AddEnum(enumName, branches[1]->getName());
            }
            else
            {
                program_data.AddEnum(enumName, branches[1]->branches[0]->getName(), branches[1]->branches[1]->getValue());
            }
        }
        else
        {
            if(branches[0]->branches.size() == 0)
            {
                program_data.AddEnum(enumName, branches[0]->getName());
            }
            else
            {
                program_data.AddEnum(enumName, branches[0]->branches[0]->getName(), branches[0]->branches[1]->getValue());
            }
            if(branches[1]->branches.size() == 0)
            {
                program_data.AddEnum(enumName, branches[1]->getName());
            }
            else
            {
                program_data.AddEnum(enumName, branches[1]->branches[0]->getName(), branches[1]->branches[1]->getValue());
            }

        }
    }
 }