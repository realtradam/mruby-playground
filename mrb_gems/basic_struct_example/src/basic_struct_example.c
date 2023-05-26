typedef struct Color
{
	char r;
	char g;
	char b;
} Color;
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/compile.h>
#include <stdio.h>
static const struct mrb_data_type felbind_struct_Color = { "Color", mrb_free };
static mrb_value felbind_struct_init_Color(mrb_state* mrb, mrb_value self) {
	Color *felbind_struct_wrapped_Color = (Color *)DATA_PTR(self);
	if(felbind_struct_wrapped_Color) { mrb_free(mrb, felbind_struct_wrapped_Color); }
	mrb_data_init(self, NULL, &felbind_struct_Color);
	felbind_struct_wrapped_Color = (Color *)mrb_malloc(mrb, sizeof(Color));
	mrb_int felbind_param_r;
	mrb_int felbind_param_g;
	mrb_int felbind_param_b;
	mrb_get_args(mrb, "iii", &felbind_param_r, &felbind_param_g, &felbind_param_b);
	felbind_struct_wrapped_Color->r = (char)felbind_param_r;
	felbind_struct_wrapped_Color->g = (char)felbind_param_g;
	felbind_struct_wrapped_Color->b = (char)felbind_param_b;
	mrb_data_init(self, felbind_struct_wrapped_Color, &felbind_struct_Color);
	return self;
}
static mrb_value felbind_getter_Color_r(mrb_state *mrb, mrb_value self) {
	struct Color *felbind_struct_get = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	return mrb_fixnum_value(felbind_struct_get->r);
}
static mrb_value felbind_setter_Color_r(mrb_state *mrb, mrb_value self) {
	mrb_int felbind_param_r;
	mrb_get_args(mrb, "i", &felbind_param_r);
	struct Color *felbind_struct_set = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	felbind_struct_set->r = (char)felbind_param_r;
	return mrb_fixnum_value(felbind_struct_set->r);
}
static mrb_value felbind_getter_Color_g(mrb_state *mrb, mrb_value self) {
	struct Color *felbind_struct_get = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	return mrb_fixnum_value(felbind_struct_get->g);
}
static mrb_value felbind_setter_Color_g(mrb_state *mrb, mrb_value self) {
	mrb_int felbind_param_g;
	mrb_get_args(mrb, "i", &felbind_param_g);
	struct Color *felbind_struct_set = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	felbind_struct_set->g = (char)felbind_param_g;
	return mrb_fixnum_value(felbind_struct_set->g);
}
static mrb_value felbind_getter_Color_b(mrb_state *mrb, mrb_value self) {
	struct Color *felbind_struct_get = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	return mrb_fixnum_value(felbind_struct_get->b);
}
static mrb_value felbind_setter_Color_b(mrb_state *mrb, mrb_value self) {
	mrb_int felbind_param_b;
	mrb_get_args(mrb, "i", &felbind_param_b);
	struct Color *felbind_struct_set = DATA_GET_PTR(mrb, self, &felbind_struct_Color, Color);
	felbind_struct_set->b = (char)felbind_param_b;
	return mrb_fixnum_value(felbind_struct_set->b);
}
void mrb_basic_struct_example_gem_init(mrb_state* mrb) {
	struct RClass *Color_class = mrb_define_module(mrb, "Color");
	MRB_SET_INSTANCE_TT(Color_class, MRB_TT_DATA);
	mrb_define_method(mrb, Color_class, "initialize", felbind_struct_init_Color, MRB_ARGS_ANY());
	mrb_define_method(mrb, Color_class, "r", felbind_getter_Color_r, MRB_ARGS_NONE());
	mrb_define_method(mrb, Color_class, "r=", felbind_setter_Color_r, MRB_ARGS_ANY());
	mrb_define_method(mrb, Color_class, "g", felbind_getter_Color_g, MRB_ARGS_NONE());
	mrb_define_method(mrb, Color_class, "g=", felbind_setter_Color_g, MRB_ARGS_ANY());
	mrb_define_method(mrb, Color_class, "b", felbind_getter_Color_b, MRB_ARGS_NONE());
	mrb_define_method(mrb, Color_class, "b=", felbind_setter_Color_b, MRB_ARGS_ANY());
}
void mrb_basic_struct_example_gem_final(mrb_state* mrb) {}
