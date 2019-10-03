# /more/mario.py
# Oct 3, 2019

from cs50 import get_int

# prompt user for positive number
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# print out the column and rows
for i in range(height):
    for j in range(height):
        # print the space follow by #
        if j < (height - i - 1):
            print(" ", end='')
        else:
            print("#", end='')
        # print return to prompt
    print("  ", end='')

    # print the other half of row
    for k in range(i + 1):
        print("#", end='')
    print("")

# $ python mario.py
# Height: -5
# Height: five
# Height: 24
# Height: 4
#    #  #
#   ##  ##
#  ###  ###
# ####  ####
