require "FelBind"

mgem = FelBind::BindGem.new(gem_name: "basic_struct_example")

mgem.add_class("Color")

mgem.add_struct(class_name: "Color", cstruct_name: "Color") do |struct|
  struct.initializer = true
  struct.member(
    name: "r",
    ctype: "char",
    rtype: "int",
    accessor: true
  )
  struct.member(
    name: "g",
    ctype: "char",
    rtype: "int",
    accessor: true
  )
  struct.member(
    name: "b",
    ctype: "char",
    rtype: "int",
    accessor: true
  )
end

result = "typedef struct Color
{
	char r;
	char g;
	char b;
} Color;\n"

result += mgem.build

File.write("src/basic_struct_example.c", result)

