#include <mruby.h>
#include <stdio.h>

// defining the function to be later bound to a ruby method
static mrb_value
multiply_numbers(mrb_state *mrb, mrb_value self)
{
  // we need to store the method arguments we recieve
  // because of that we initialize them here
  mrb_int first_input;
  mrb_int second_input;

  // We need to call a function to recieve the method arguments
  mrb_get_args(
    mrb,                        // Ruby VM state
    "ii",                       // Tell the function we expect 2 integers
    &first_input, &second_input // Pass addresses of where we want the values to be stored into
  );

  // multiply the values and then convert the result
  // into a mruby fixnum
  return mrb_fixnum_value(first_input * second_input);
}

// gem initializer
void
mrb_arguments_and_return_example_gem_init(mrb_state* mrb) {
    struct RClass *arguments_and_return_example_class = mrb_define_module(mrb, "ArgumentsAndReturnExample");

    // (!) signifies a change from the last example
    mrb_define_module_function(
      mrb,                    // Mruby VM state
      arguments_and_return_example_class,  // Class we bind method to
      "multiply_numbers",           // Name of method
      multiply_numbers,         // Function we are binding as a method
      MRB_ARGS_REQ(2)         // (!) 2 arguments are required
    );
}

// gem finalizer
void
mrb_arguments_and_return_example_gem_final(mrb_state* mrb) {

}
