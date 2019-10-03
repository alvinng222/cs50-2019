# cash.py
# Oct 03, 2019

from cs50 import get_float

# Prompt user for input, and convert to cents
while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        cents = round(dollars * 100)
        break

cashbal = cents

# using double // to round down for integer
# quarter, 25 cents
qtr_count = cashbal // 25
cashbal = cashbal - (qtr_count * 25)

# dimes 10 cents
dim_count = cashbal // 10
cashbal = cashbal - (dim_count * 10)

# nickels, 5 cents
nic_count = cashbal // 5
cashbal = cashbal - (nic_count * 5)

# pennies, 1 cent
pen_count = cashbal // 1
cashbal = cashbal - (pen_count * 1)

# total cash change
print(qtr_count + dim_count + nic_count + pen_count)

# $ python cash.py
# Change owed: 0.41
# 4

