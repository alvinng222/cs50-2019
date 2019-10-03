# credit.py
# Oct 03, 2019

from cs50 import get_int

digit13 = 1000000000000     # visa 13 digits number
digit16 = 1000000000000000  # visa or Master 16 digits number
digit15 = 100000000000000   # Amx 15 digits number


def main():
    # prompt for number between 13 to 17 digits
    while True:
        number = get_int("Number: ")
        if number < (digit16 * 10):
            break

    # if function Luhn valid, check type
    if luhn(number) == 0:
        # Visa uses 13-digit numbers, start with 4. Or
        if number > digit13 and number < (digit13 * 10):
            lastdigit = number // digit13
            if lastdigit == 4:
                print("VISA")
            else:
                print("INVALID")

        # Visa uses 16-digit numbers, start with 4;
        # Master uses 16-digit numbers, start with 51,52,53,54, or 55.
        elif number > digit16 and number < (digit16 * 10):
            lastdigit = number // (digit16 // 10)
            if lastdigit // 10 == 4:
                print("VISA")
            elif lastdigit > 50 and lastdigit < 56:
                print("MASTERCARD")
            else:
                print("INVALID")

        # Amex uses 15-digit numbers, start with 34 or 37
        elif number > digit15 and number < (digit15 * 10):
            lastdigit = number // (digit15 // 10)
            if lastdigit == 37 or lastdigit == 34:
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def luhn(Num):  # LUHN ALGORITHM, input long number, return with 0 for valid
    counter = 0
    checksum = 0

    # loop and get the remainder by divide by 10, till variable become 0
    while True:
        counter += 1    # start with counter = 1

        # get the first digit by modular 10
        digit1 = Num % 10

        # perform a check for Odd digit or Even digit
        if parity(counter) == 1:
            # if counter is odd, add the 1st digit to checksum
            checksum += digit1
        else:
            # if counter is even, double the digit
            # if more than 9, split digit and add into checksum
            digit2 = digit1 * 2
            if digit2 > 9:
                checksum += (digit2 % 10)   # add 1st digit
                checksum += (digit2 // 10)   # and 2nd digit
            else:
                checksum += digit2

        Num = Num // 10      # next digit
        # print("num", Num)                 # for test

        if Num <= 0:
            # checksum modulus 10
            return checksum % 10


def parity(counter):
    # Check parity of integer
    if counter % 2 == 0:
        return 0
    else:
        return 1


if __name__ == "__main__":
    main()

# $ python credit.py
#
# 378282246310005 as AMEX
# 371449635398431 as AMEX
# 5555555555554444 as MASTERCARD
# 5105105105105100 as MASTERCARD
# 4111111111111111 as VISA
# 4012888888881881 as VISA
# 1234567890 as INVALID
# :) rejects a non-numeric input of "foo"
# :) rejects a non-numeric input of ""
