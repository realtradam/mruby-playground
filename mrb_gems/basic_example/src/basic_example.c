#include <mruby.h>
#include <stdio.h>

// defining the function to be later bound to a ruby method
static mrb_value
hello_world(mrb_state *mrb, mrb_value self)
{
    printf("Hello World\n");

    return mrb_nil_value(); // return null
}

// gem initializer
void
mrb_basic_example_gem_init(mrb_state* mrb) {
    struct RClass *basic_example_class = mrb_define_module(mrb, "BasicExample");
    mrb_define_class_method(
      mrb,                    // Mruby VM state
      basic_example_class,  // Class we bind method to
      "say_hello",            // Name of method
      hello_world,        // Function we are binding as a method
      MRB_ARGS_NONE()         // How many arguments are optional/required
    );
}

// gem finalizer
void
mrb_basic_example_gem_final(mrb_state* mrb) {

}
