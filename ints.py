# Integer arithmetic

from cs50 import get_int

# Prompt user for x
x = get_int("x: ")

# Prompt user for y
y = get_int("y: ")

# Perform arithmetic
print(f"x + y = {x + y}")
print(f"x - y = {x - y}")
print(f"x * y = {x * y}")
print(f"x / y = {x / y}")
print(f"x // y = {x // y}")
print(f"x mod y = {x % y}")

# ./ints.c
# x: 13
# y: 10
# x + y = 23
# x - y = 3
# x * y = 130
# x / y = 1
# x // y = {x // y}
# x mod y = 3
