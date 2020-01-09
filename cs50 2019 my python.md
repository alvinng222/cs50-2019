Python 3 Difference from c
========================
*`.py` file extension 
* Variable no type spec & semicolon, eg `x = 54`
* Can use double / single quote, eg `phase = ‘This is Cs50’`
* **Indent in python is important**


In c
``` c
If (y<43 || s == 15)
{ // code here }
```
In py
``` python
if y < 43 or z == 15:
   # code here
```


In C
``` c
If (y < 43 && z == 15)
{ // code 1 }
else
{ // code 2 }
```
In py 
``` py
if y < 43 and z == 15:
    # code 1
else:
    # code 2
```


In c
``` c
If (c == 50)
{ // code 1 }
else if (c != 51)
{ // code 2 }
```
In py
``` py
if c == 50:
    # code 1
elif not c == 51:
    # code 2
```


In c
``` c
char bar = get_char();
bool alphabetic = isalpha(var) ? true : false;
```
In py
``` py
letters_only = True if input().isalpha() else False
```


* In py, have two loops; while and for

In c
``` c
int counter = 0;
while ( counter < 100)
{ printf(“%i\n”, counter);
counter++; }
```
In py
``` py
counter = 0
while counter < 100:
    print(counter)
    counter += 1
```


In c
``` c
for (int x=0; x < 100; x++)
{ printf( “%i\n”, x) }
```
In py 
``` py
for x in range(100):
     print(x)
```


In c
``` c
for (int x = 0; x < 100; x += 2)
{ printf( “%i\n”, x) }
```
In py 
``` py
for x in range(0, 100, 2):
     print(x)
```


* Python arrays known as lists

  * Declaring a lists
``` py
nums = []
nums = [1, 2, 3, 4]
nums = [ x for x in range(500)]
nums = list()
```


* Tacking on to an exiting list
``` py
nums = [1, 2, 3, 4]
nums.append(5)
```
Same as
``` py
nums = [1, 2, 3, 4]
nums.insert(4, 5)
```
Same as
``` py
nums = [1, 2, 3, 4]
nums[len(nums):] = [5]

```

* Tuples

are ordered, immutable sets of data; they are great for associating collections of data, like a struct in C, but those values are unlikely to change.



* list of tuples:
``` py
presidents = [
    (“George Washington”, 1789),
    (“John Adams”, 1797),
    (“Thomas Jefferson”, 1801),
    (“James Madison”, 1809)
]
```

``` py
for prez, year in presidents:
    print(“In {1}, {0} took office”.format(prez, year))
```
 

* . Dictionaries 
``` py
pizzas = {
     “cheese”: 9,
     “pepperoni”: 10,
     “vegetable”: 11,
     “buffalo chicken”: 12,
}
```

``` py
pizzas[“cheese”] = 8
```

``` py
if pizza[“vegetables”] < 12:
     # do something
```

``` py
pizzas[“bacon”] = 14
```


* .Loops (redux)
``` py
for pie in pizzas:
     print (pie)
```

``` py
for pie, price in pizzas.items():
     print(price)
#print out not in order 
```

``` py
for pie, price in pizzas.items():
     print(“A whole {} pizza costs ${}”.format(pie, price))
```

``` py
     print(“A whole “ + pie + “ pizza costs $” + str(price))
```


* .Function def keyword


``` py
def square(x):
     return x * x
```

``` py
def square(x):
     return x ** 2
```

``` py
def square(x):
     result = 0
     for i in range(0, x):
           result += x
     result result
```


* .Objects

  * Python is an object-oriented programming language



* . C structures contain a number of fields, which we might also call properties. But the properties themselves can not ever stand on their own.

* . Objects, meanwhile, have properties but also methods, or functions that are inherent to the object, and mean nothing outside of it. You define the methods inside the object also. Thus, properties and methods don’t ever stand on their own.



In other
```
function(object)
```
In Py
``` py
object.method()
```


* define a type of object using the class keyword in Python.

* Classes require an initialization function, also known as a constructor, which are the starting values of the properties of the object.

* In defining each method of an object, s e l f should be it’s first parameter, which stipulates in what object the method is called.


``` py
class Student():
     def __init__(self, name, id):
           self.name = name
           self.id = id 
```

``` py
     def changeID(self, id):
           self.id = id 
```

``` py
     def print(self):
           print(“{} - {}”.format(self.name, self.id))
```

``` py
jane = Student(“Jane”, 10)
jane.print()
jane.changeID(11)
jane.print()
```


* .Style

* . Tab and indentation 



* .Including files



In c
``` c
#include <cs50>
```
In py
``` py
import cs50
```
``` c
cs50.get_int()

cs50.get_float()

cs50.get_string()
```


Python Syntax
``` py
python (files)
```


* To look more like c programs when execute by adding a shebang

`#!/usr/bin/env python3`



* need to change permissions of file

  * chmod a+x <file>

* —- cash —-

* “do-while” loop
``` py
while True:
     # prompt user
     if condition:
          break
```


* round

*  x // y for integer division

* x / y for floating-point division 




—-

Https://docs.python.org

—-
### work on Pset8
``` py

# dictionary
thisdict =	{
  "brand": "Ford",
  "model": "Mustang",
  "year": 1964
}
for x in thisdict.values():
  print(x)
x = thisdict["model"]
print(x)

# Sets
thisset = {"apple", "banana", "cherry"}
print(thisset)

# tuple
thistuple = ("apple", "banana", "cherry")
print(thistuple)

# List
thislist = ["apple", "banana", "cherry"]
print(thislist[1])

balCash = [{'cash': 10000}]
print(f"balCash: {balCash}")
BC = balCash[0]
print(f"BC: {BC}")
cash=BC["cash"]
print(f'BC["cash"]: {cash}')
print(f'cash * 2: {cash*2} ')

for rows in balCash:
  print(f"rows in balcash : {rows}")
print(f'rows["cash"]: {rows["cash"]}')

t1 = ("For Bebuging: Type of balCash: " + str(type(balCash)) +
      ", type of cash: " + str( type(cash) ))
print(t1)

"""
~/work8/ $ python hello.py
Ford
Mustang
1964
Mustang
{'apple', 'banana', 'cherry'}
('apple', 'banana', 'cherry')
banana
balCash: [{'cash': 10000}]
BC: {'cash': 10000}
BC["cash"]: 10000
cash * 2: 20000 
rows in balcash : {'cash': 10000}
rows["cash"]: 10000
For Bebuging: Type of balCash: <class 'list'>, type of cash: <class 'int'>
~/work8/ $ 
"""
```
``` python
   import json

   # some JSON:
   x = '{ "name":"John", "age":30, "city":"New York"}'

   # parse x:
   y = json.loads(x)

   # the result is a Python dictionary:
   print(y["age"])


# from flask import jsonify
@app.route('/testJson')
def testJson():
    return jsonify(username="ABC", email="decf@hij", id="0123")
# results send to browser: >>> {"email":"decf@hij","id":"0123","username":"ABC"}
```

### using Flask 
##### hello/ #####

##### hello/application.py
``` py
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", name=request.args.get("name", "world"))
```

##### hello/templates/index.html
``` html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        hello, {{ name }}
    </body>
</html>
```
--

