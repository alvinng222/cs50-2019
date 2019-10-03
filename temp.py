print("a :", ord("a"))
print("A :", ord("A"))
print("a - A :", ord("a") - ord("A"))

p = "Hello's"
k = 1
for i in p:
    if i.isupper():
        # print(i, end="")
        print(chr(((ord(i) - 65 + k) % 26) + 65))   # 65 is 'A'
    elif i.islower():
        print(chr(((ord(i) - 97 + k) % 26) + 97))   # 97 is 'a'
    else:
        print(i)



