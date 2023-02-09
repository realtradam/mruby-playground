#include <mruby.h>
#include <stdio.h>

// defining the function to be later bound to a ruby method
static mrb_value
multiply_numbers(mrb_state *mrb, mrb_value self)
{
	// the number of keyword arguments we expect
	uint32_t kw_num = 2;

	const mrb_sym kw_names[] = {	// the array where we specify what we expect the keyword arguments to be named
		mrb_intern_lit(mrb, "x"),	// we will expect an 'x' keyword
		mrb_intern_lit(mrb, "y"),	// we will expect a 'y' keyword
	};

	// initialize the array where the values of they kwargs will be temporarily stored
	mrb_value kw_values[kw_num];

	// When getting arguments, the function expects all the data we
	// created above to be formatted into a specific struct. So we
	// create this struct here.
	const mrb_kwargs kwargs = {
		kw_num,		// number of kwargs
		0,			// number of required kwargs
		kw_names,	// names of kwargs
		kw_values,	// values of kwargs(will be filled out)
		NULL		// remaining kwargs(NULL specifies to error if other kwargs or args are given)
	};

	mrb_get_args(mrb, "|:", &kwargs); // get the arguments

	if (mrb_undef_p(kw_values[0])){ // check if we actually recieved the first kwarg
		kw_values[0] = mrb_fixnum_value(5); // set a default  value if we didnt
		// notice that because kw_values only holds ruby objects
		// we must convert the number "5" into a ruby object by
		// using the 'mrb_fixnum_value' function
	}

	if (mrb_undef_p(kw_values[1])){ // ditto with second kwarg
		kw_values[1] = mrb_fixnum_value(5);
	}

	// we convert the ruby objects back into C
	// ints, mutiply them and then return the
	// value as a ruby object
	return mrb_fixnum_value(mrb_as_int(mrb,kw_values[0]) * mrb_as_int(mrb,kw_values[1]));
}

// gem initializer
void
mrb_keyword_arguments_example_gem_init(mrb_state* mrb) {
	struct RClass *keyword_arguments_example_class = mrb_define_module(mrb, "KeywordArgumentsExample");
	mrb_define_class_method(
			mrb,                    // Mruby VM state
			keyword_arguments_example_class,  // Class we bind method to
			"multiply_numbers",            // Name of method
			multiply_numbers,        // Function we are binding as a method
			MRB_ARGS_ANY()	         // How many arguments are optional/required
			);
}

// gem finalizer
void
mrb_keyword_arguments_example_gem_final(mrb_state* mrb) {

}
