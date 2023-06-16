#include "ast.hpp"

int main(int argc, char *argv[])
{
    //Tokenizing the input and bulding the pointer tree
    Node *program = parseAST(argv[2]);
    //Calculating how much variables each function needs and what stack offset should they have and in what scopes they are
    Program_Data program_data;
    program->VariableParse(program_data, "global");
    
    //Generating the actual MIPS
    std::ofstream output(argv[4], std::ofstream::out);
    if(output.is_open())
    {
        program->CodeGen(output, program_data, 2, "int");
        output.close();
    }
    delete program;
}