/*
* File Name: enum.h
* contains enums for the use of certain files in the project
*/

#ifndef ENUM_H
#define ENUM_H

enum operations {E_mov = 0, E_cmp, E_add, E_sub, E_not, E_clr, E_lea, E_inc, E_dec, E_jmp, E_bne, E_get, E_prn, E_jsr, E_rts, E_hlt};

enum operands{E_src_op = -1500, E_dest_op};

enum directive_line_type{E_data = -2000, E_string, E_struct, E_ext, E_ent, E_not_directive, E_directive};

enum operand_type{ E_op_num = -2500, E_op_label, E_op_struct, E_op_register};

enum IC_or_DC{E_IC =-3000, E_DC};

enum errors{E_label_declared_twice = 0, E_ext_label_defined, E_defined_label_declared_ext, E_missing_colons_in_label, 
E_label_cannot_use_keyword, E_missing_label, E_missing_comma,
 E_illegal_comma, E_multiple_commas, E_illegal_number, E_missing_number, E_missing_number_before_comma, E_missing_number_after_comma,
  E_illegal_characters_in_label_name, E_extra_text, E_undefind_command, E_illegal_op, E_missing_string, E_illegal_string, E_illegal_lea_src_op_register,
  E_illegal_lea_src_op_number_address, E_illegal_command_dest_op_number_address, E_illegal_num_of_struct_member, E_label_used_not_defined,
   E_illegal_line_length, E_missing_op, E_file_not_exist, E_op_is_saved_word, E_label_cross_limit, E_macro_keyword, E_extra_text_macro
  , E_duplicate_macro_name, E_macro_named_macro, E_macro_named_endmacro, E_endmacro_not_found, E_duplicate_label_definitions, E_ent_label_not_defined, E_label_defined_empty_line
  , E_num_out_of_range_instruction, E_num_out_of_range_directive
  ,E_label_used_as_struct};

enum messages{E_files_created = 0, E_exiting_program, E_ext_labels_not_found, E_ent_labels_not_found, E_err_found, E_start_handeling_macro,
 E_new_line, E_macros_were_handled, E_error_pre_assembler, E_start_first_parse, E_label_defined_before_ext_ent,
 E_assembler_first_part_started, E_assembler_first_part_finished_success, E_assembler_first_part_finished_fail,
 E_assembler_second_part_started, E_assembler_second_part_finished_success, E_assembler_second_part_finished_fail};

enum signals{E_not_operation = -500, E_not_label, E_not_a_register, E_error_occured, E_success, E_label_not_yet_defined, E_not_ext_or_ent, E_label_defined
,E_label_not_defined, E_has_errors};

enum print_type{E_print_error, E_print_message, E_print_warning};

#endif