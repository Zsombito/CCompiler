#ifndef ast_hpp
#define ast_hpp

//Include main folder:
#include "program_data.hpp"
#include "ast_node.hpp"

//Include Arrays:
#include "Arrays/ast_array_assign.hpp"
#include "Arrays/ast_array_call.hpp"
#include "Arrays/ast_array_declare.hpp"
#include "Arrays/ast_array_declare_assign.hpp"
#include "Arrays/ast_char_array.hpp"

//Inlcude Blocks and Lines:
#include "Blocks_and_Lines/ast_block.hpp"
#include "Blocks_and_Lines/ast_block_seq.hpp"
#include "Blocks_and_Lines/ast_line.hpp"
#include "Blocks_and_Lines/ast_line_seq.hpp"

//Include Conditionals:
#include "Conditionals/ast_ifstatements.hpp"
#include "Conditionals/ast_whileloop.hpp"
#include "Conditionals/ast_forloop.hpp"
#include "Conditionals/ast_case.hpp"
#include "Conditionals/ast_case_seq.hpp"
#include "Conditionals/ast_switch.hpp"
#include "Conditionals/ast_else.hpp"

//Include Declarations:
#include "Declarations_and_Assigns/ast_assign.hpp"
#include "Declarations_and_Assigns/ast_declaration.hpp"
#include "Declarations_and_Assigns/ast_declara_assign.hpp"

//Functions:
#include "Functions/ast_function_declare.hpp"
#include "Functions/ast_params.hpp"
#include "Functions/ast_args.hpp"
#include "Functions/ast_function_call.hpp"
#include "Functions/ast_external.hpp"

//Operator
#include "Operators/ast_add_operator.hpp"
#include "Operators/ast_and_operator.hpp"
#include "Operators/ast_band_operator.hpp"
#include "Operators/ast_bor_operator.hpp"
#include "Operators/ast_bxor_operator.hpp"
#include "Operators/ast_div_operator.hpp"
#include "Operators/ast_equal_operator.hpp"
#include "Operators/ast_greater_operator.hpp"
#include "Operators/ast_greatereq_operator.hpp"
#include "Operators/ast_lesser_operator.hpp"
#include "Operators/ast_lessereq_operator.hpp"
#include "Operators/ast_lshift_operator.hpp"
#include "Operators/ast_mod_operator.hpp"
#include "Operators/ast_mul_operator.hpp"
#include "Operators/ast_notequal_operator.hpp"
#include "Operators/ast_mux_operator.hpp"
#include "Operators/ast_operator_master.hpp"
#include "Operators/ast_or_operator.hpp"
#include "Operators/ast_rshift_operator.hpp"
#include "Operators/ast_sub_operator.hpp"

//Others
#include "Others/ast_identifier.hpp"
#include "Others/ast_number.hpp"
#include "Others/ast_return.hpp"
#include "Others/ast_type.hpp"
#include "Others/ast_break.hpp"
#include "Others/ast_continue.hpp"
#include "Others/ast_post_increment.hpp"
#include "Others/ast_pre_increment.hpp"
#include "Others/ast_empty_scope.hpp"
#include "Others/ast_post_decrement.hpp"
#include "Others/ast_pre_decrement.hpp"
#include "Others/ast_float.hpp"
#include "Others/ast_size_of.hpp"
#include "Others/ast_char.hpp"
#include "Others/ast_string.hpp"

//Unaries
#include "Unaries/ast_inv_unary.hpp"
#include "Unaries/ast_neg_unary.hpp"
#include "Unaries/ast_not_unary.hpp"
#include "Unaries/ast_unary_master.hpp"

//Pointers
#include "Pointer/ast_address_of.hpp"
#include "Pointer/ast_dereference.hpp"
#include "Pointer/ast_pointer_add.hpp"
#include "Pointer/ast_pointer_assign.hpp"
#include "Pointer/ast_pointer_declaration.hpp"
#include "Pointer/ast_pointer_declare_assing.hpp"
#include "Pointer/ast_pointer_sub.hpp"
#include "Pointer/ast_dereference_assign.hpp"

//Enums
#include "Enums/ast_enum_declare.hpp"

//Struct
#include "Struct/ast_struct_definition.hpp"
#include "Struct/ast_struct_declare.hpp"
#include "Struct/ast_struct_index.hpp"
#include "Struct/ast_struct_assign.hpp"

extern Node *parseAST(std::string filename);

#endif