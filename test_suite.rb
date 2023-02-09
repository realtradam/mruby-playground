puts "Beginning Test Suite..."
puts

puts " - Basic Example - "
BasicExample.say_hello
BasicExample.say_goodbye
puts

puts " - Arguments And Return Example - "
print "3 * 10 = "
puts ArgumentsAndReturnExample.multiply_numbers(3, 10)
puts

puts " - Keyword Arguments Example - "
print "(x: 4) * (y: 6) = "
puts KeywordArgumentsExample.multiply_numbers(x: 4, y: 6)
puts

puts "Reached end of test suite."
