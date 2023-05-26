#include <mruby.h>
#include <stdio.h>
static mrb_value
felbind_multiply_numbers(mrb_state *mrb, mrb_value self){
mrb_int felflame_var_first_input;
mrb_int felflame_var_second_input;
mrb_get_args(mrb, "ii", &felflame_var_first_input, &felflame_var_second_input);

return mrb_fixnum_value(felflame_var_first_input * felflame_var_second_input);
}
void mrb_arguments_and_return_example_gem_init(mrb_state* mrb) {
struct RClass *ArgumentsAndReturnExample_class = mrb_define_module(mrb, "ArgumentsAndReturnExample");
mrb_define_class_method(mrb, ArgumentsAndReturnExample_class, "multiply_numbers", felbind_multiply_numbers, MRB_ARGS_REQ(2));
}
void mrb_arguments_and_return_example_gem_final(mrb_state* mrb) {}
