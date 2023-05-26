require "FelBind"

mgem = FelBind::BindGem.new(gem_name: "arguments_and_return_example")

mgem.add_class("ArgumentsAndReturnExample")

mgem.add_function(class_name: "ArgumentsAndReturnExample", function_name: "multiply_numbers") do |func|
  func.get_args do |args|
    args.int "first_input"
    args.int "second_input"
  end

  func.return_call do |rc|
    rc.type = "int"
    rc.val = "#{func.arg("first_input")} * #{func.arg("second_input")}"
  end
end

File.write("src/arguments_and_return_example.c", mgem.build)

