#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/compile.h>
#include <stdio.h>

// a regular C struct
typedef struct Color
{
	char r;
	char g;
	char b;
} Color;
// we will later be building an interface for it

// A struct that informs the Ruby VM what function to call
// when garbage collecting our struct wrapper. Here nothing
// special needs to be done so the default "mrb_free" function
// is used.
// Ending the struct name with 'mrb_struct' is a
// convention I like to use for these mruby 'internal'
// structs
static const struct mrb_data_type Color_mrb_struct = { 
	"Color", // name of the class in ruby
	mrb_free // the function we want it to call when garbage collected
			 // ^ you can customize this, but remember to always call mrb_free
			 // ^ within whatever customization you make
};

static mrb_value
Color_initialize(mrb_state* mrb, mrb_value self) {
	//Rectangle      *wrapped_value = (Rectangle *)     mrb_malloc(mrb, sizeof(Rectangle));
	//MyCustomStruct *wrapped_value = (MyCustomStruct *)mrb_malloc(mrb, sizeof(MyCustomStruct));

	Color *wrapped_value = (Color *)DATA_PTR(self);
	if(wrapped_value) { mrb_free(mrb, wrapped_value); }
	mrb_data_init(self, NULL, &Color_mrb_struct);
	wrapped_value = (Color *)mrb_malloc(mrb, sizeof(Color));

	mrb_int parameter_r; // the value that will be recieved from the function call parameter
	mrb_int parameter_g; // the value that will be recieved from the function call parameter
	mrb_int parameter_b; // the value that will be recieved from the function call parameter

	mrb_get_args(mrb, "iii", &parameter_r, &parameter_g, &parameter_b); // getting the value of the param and storing it.
	wrapped_value->r = (char)parameter_r;
	wrapped_value->g = (char)parameter_g;
	wrapped_value->b = (char)parameter_b;
	//mrb_data_init(self, wrapped_value, &mrb_Rectangle_struct);
	mrb_data_init(self, wrapped_value, &Color_mrb_struct);
	return self;
}

// defining the function to be later bound to a ruby method
static mrb_value
Color_r_getter(mrb_state *mrb, mrb_value self)
{
	// Unwrap the Ruby object into a C pointer
	struct Color *my_struct = DATA_GET_PTR(
			mrb,						// The Ruby VM
			self,						// The Ruby object holding the struct
			&Color_mrb_struct,	// Address to the custom struct tag we declared above
			Color				// The struct tag we declared at the top
			);

	// Get the x value from the struct and convert it into a Ruby object. Return it
	return mrb_fixnum_value(my_struct->r);
}

static mrb_value
Color_r_setter(mrb_state* mrb, mrb_value self) {
	mrb_int parameter_r; // the value that will be recieved from the function call parameter

	mrb_get_args(mrb, "i", &parameter_r); // getting the value of the param and storing it.

	// Unwrap the Ruby object into a C pointer
	// same as the function defined above does
	Color *my_struct = DATA_GET_PTR(mrb, self, &Color_mrb_struct, Color);

	// Set the value in the struct to the new one
	// note: we do not need to rerwap the struct or anything as we 
	// are using a pointer to change the values inside the wrapped
	// struct.
	my_struct->r = (char)parameter_r;

	// Ruby convention is to return the value we set so we do that
	return mrb_fixnum_value((char)parameter_r);
}

// gem initializer
void
mrb_basic_struct_example_gem_init(mrb_state* mrb) {
    struct RClass *basic_struct_example_class = mrb_define_module(mrb, "BasicStructExample");
	struct RClass *color_class = mrb_define_class_under(
			mrb,
			basic_struct_example_class,
			"Color",
			mrb->object_class
			);
	// This macro MUST be called and it must be after the class is defined
	MRB_SET_INSTANCE_TT(color_class, MRB_TT_DATA);

    mrb_define_method(
      mrb,                    // Mruby VM state
      color_class,  // Class we bind method to
      "initialize",            // Name of method
      Color_initialize,        // Function we are binding as a method
      MRB_ARGS_ANY()         // How many arguments are optional/required
    );
    mrb_define_method(
      mrb,                    // Mruby VM state
      color_class,  // Class we bind method to
      "r",            // Name of method
      Color_r_getter,        // Function we are binding as a method
      MRB_ARGS_NONE()         // How many arguments are optional/required
    );
    mrb_define_method(
      mrb,                    // Mruby VM state
      color_class,  // Class we bind method to
      "r=",            // Name of method
      Color_r_setter,        // Function we are binding as a method
      MRB_ARGS_ANY()         // How many arguments are optional/required
    );
}

// gem finalizer
void
mrb_basic_struct_example_gem_final(mrb_state* mrb) {

}
