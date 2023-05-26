#include <mruby.h>
#include <stdio.h>
static mrb_value
felbind_say_hello(mrb_state *mrb, mrb_value self){
printf("Hello World\n");
return mrb_nil_value();
}
void mrb_basic_example_gem_init(mrb_state* mrb) {
struct RClass *BasicExample_class = mrb_define_module(mrb, "BasicExample");
mrb_define_class_method(mrb, BasicExample_class, "say_hello", felbind_say_hello, MRB_ARGS_NONE());
}
void mrb_basic_example_gem_final(mrb_state* mrb) {}
