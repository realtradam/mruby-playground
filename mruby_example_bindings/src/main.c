#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/compile.h>
#include <stdio.h>

// A regular C struct 
typedef struct MyCustomStruct {
	int x;
	int y;
} MyCustomStruct;
// We will create an interface for using it with Ruby

// A struct that informs the Ruby VM what function to call
// when garbage collecting our struct wrapper. Here nothing
// special needs to be done so the default "mrb_free" function
// is used.
static const struct mrb_data_type mrb_MyCustomStruct_struct = { 
	"MyCustomStruct", // name of the class in ruby
	mrb_free // the function we want it to call when garbage collected
			 // ^ you can customize this, but remember to always call mrb_free
			 // ^ within whatever customization you make
};

static mrb_value
mrb_MyCustomStruct_initialize(mrb_state* mrb, mrb_value self) {
	//Rectangle      *wrapped_value = (Rectangle *)     mrb_malloc(mrb, sizeof(Rectangle));
	//MyCustomStruct *wrapped_value = (MyCustomStruct *)mrb_malloc(mrb, sizeof(MyCustomStruct));

	MyCustomStruct *wrapped_value = (MyCustomStruct *)DATA_PTR(self);
	if(wrapped_value) { mrb_free(mrb, wrapped_value); }
	mrb_data_init(self, NULL, &mrb_MyCustomStruct_struct);
	wrapped_value = (MyCustomStruct *)mrb_malloc(mrb, sizeof(MyCustomStruct));

	int parameter_x; // the value that will be recieved from the function call parameter

	mrb_get_args(mrb, "i", &parameter_x); // getting the value of the param and storing it.
	wrapped_value->x = parameter_x;
	//mrb_data_init(self, wrapped_value, &mrb_Rectangle_struct);
	mrb_data_init(self, wrapped_value, &mrb_MyCustomStruct_struct);
	return self;
}

// defining the function to be later bound to a ruby method
	static mrb_value
mrb_mycustomstruct_x_getter(mrb_state *mrb, mrb_value self)
{
	// Unwrap the Ruby object into a C pointer
	struct MyCustomStruct *my_struct = DATA_GET_PTR(
			mrb,						// The Ruby VM
			self,						// The Ruby object holding the struct
			&mrb_MyCustomStruct_struct,	// Address to the custom struct tag we declared above
			MyCustomStruct				// The struct tag we declared at the top
			);

	// Get the x value from the struct and convert it into a Ruby object. Return it
	return mrb_fixnum_value(my_struct->x);
}

static mrb_value
mrb_mycustomstruct_x_setter(mrb_state* mrb, mrb_value self) {
	int parameter_x; // the value that will be recieved from the function call parameter

	mrb_get_args(mrb, "i", &parameter_x); // getting the value of the param and storing it.

	// Unwrap the Ruby object into a C pointer
	// same as the function defined above does
	MyCustomStruct *my_struct = DATA_GET_PTR(mrb, self, &mrb_MyCustomStruct_struct, MyCustomStruct);

	// Set the value in the struct to the new one
	// note: we do not need to rerwap the struct or anything as we 
	// are using a pointer to change the values inside the wrapped
	// struct.
	my_struct->x = parameter_x;

	// Ruby convention is to return the value we set so we do that
	return mrb_fixnum_value(parameter_x);
}

// gem initializer
void
mrb_mruby_example_bindings_gem_init(mrb_state* mrb) {
	struct RClass *class_binding_example = mrb_define_module(mrb, "Example");

	// Defining the class that will wrap the custom struct
	// It is namespaced under the Example class
	struct RClass *mycustomstruct_class = mrb_define_class_under(
			mrb,					// Mruby VM state
			class_binding_example,	// Where the class will be namespaced under
			"MyCustomStruct",		// Name of the new class
			mrb->object_class		// What class to inherit ('mrb->object_class' is the default if you want 'none')
			);

	// This macro MUST be called and it must be after the class is defined
	MRB_SET_INSTANCE_TT(mycustomstruct_class, MRB_TT_DATA);

	// (!) signifies a change from the last example
	mrb_define_method(
			mrb,
			mycustomstruct_class,
			"initialize",
			mrb_MyCustomStruct_initialize,
			MRB_ARGS_ANY()
			);
	mrb_define_method(
			mrb,							// Mruby VM state
			mycustomstruct_class,			// Class we bind the method to
			"x",							// Name of method
			mrb_mycustomstruct_x_getter,	// Function we are binding as a method
			MRB_ARGS_NONE()					// (!) No Arguments
			);
	mrb_define_method(
			mrb,							// Mruby VM state
			mycustomstruct_class,			// Class we bind the method to
			"x=",							// Name of method
			mrb_mycustomstruct_x_setter,	// Function we are binding as a method
			MRB_ARGS_ANY()					// (!) Arguments are expected
			);
}

// gem finalizer
void
mrb_mruby_example_bindings_gem_final(mrb_state* mrb) {

}
