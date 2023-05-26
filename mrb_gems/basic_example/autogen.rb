require "FelBind"

mgem = FelBind::BindGem.new(gem_name: "basic_example")

mgem.add_class("BasicExample")

mgem.add_function(class_name: "BasicExample", function_name: "say_hello") do |func|
  func.content = "printf(\"Hello World\\n\");"
  func.return_call do |rc|
    rc.type = "nil"
  end
end

File.write("src/basic_example.c", mgem.build)

