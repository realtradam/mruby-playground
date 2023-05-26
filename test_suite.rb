puts "Beginning Test Suite..."
puts

if Object.const_defined? 'BasicExample'
  puts " - Basic Example - "
  BasicExample.say_hello
  BasicExample.say_goodbye
  puts
else
  puts "Basic Example const not found, skipping test..."
end

if Object.const_defined? 'ArgumentsAndReturnExample'
  puts " - Arguments And Return Example - "
  print "3 * 10 = "
  puts ArgumentsAndReturnExample.multiply_numbers(3, 10)
  puts
else
  puts "Arguments And Return Example const not found, skipping test..."
end

if Object.const_defined? 'KeywordArgumentsExample'
  puts " - Keyword Arguments Example - "
  print "(x: 4) * (y: 6) = "
  puts KeywordArgumentsExample.multiply_numbers(x: 4, y: 6)
  puts
else
  puts "Keyword Arguments Example const not found, skipping test..."
end

if Object.const_defined? 'BasicStructExample'
  puts " - Basic Struct Example - "
  puts "Making a new rgb struct with:"
  puts " r: 10, g: 20, b: 30"
  color = Color.new(10,20,30)
  puts "Red is #{color.r}"
  puts "Set red to 60: #{color.r = 60}"
  puts "Red is #{color.r}"
  puts
else
  puts "Basic Struct Example const not found, skipping test..."
end

puts "Reached end of test suite."
