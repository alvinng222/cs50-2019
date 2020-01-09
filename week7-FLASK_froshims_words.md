cs50 2019 week 7

* [lecture 7 - froshims](#froshims)
* [lecture 7 - Words](#words)
* [my note](#my-note)

# lecture 7

CS50 [lecture 7](https://cs50.harvard.edu/x/notes/7/#lecture-7).
> note [https://cs50.harvard.edu/x/notes/7/] 

A simple web server program in python, serve.py

Flask is a framework for Python

## Flask
- Today, we’ll use Flask, a microframework,
- Flask is written in Python and is a set of libraries of code that we can use to write a web server in Python.
- One methodology for organizing web server code is **MVC**, or Model-View-Controller:
    - Thus far, the programs we’ve written have all been in the Controller category, whereby we have logic and algorithms that solve some problem and print output to the terminal. But with web programming, we also want to add formatting and aesthetics (the View component), and also access data in a more organized way (the Model component). When we start writing our web server’s code in Python, most of the logic will be in the controllers.

- Today, we’ll build a website where students can fill out a form to register for Frosh IMs, freshman year intramural sports.

/wk7/
 Now, if we run python serve.py, we can click CS50 IDE > Web Server,

With Flask, we can write the following in an application.py file:
```python
    from flask import Flask, render_template, request
    
    app = Flask(__name__)
      
    @app.route("/")
    def index():
        return "hello, world"
```
       
### $ flask run
we can call flask run from the terminal in the same folder as our application.py,

With `app = Flask(__name__)`, we initialize a Flask application for our application.py file.
 `@app.route("/")` syntax to indicate that the function below will respond to any requests for /,
 or the root page of our site. We call that function index by convention,
 and it will just return “hello, world” as the response, without any HTML.
Now, we can call flask run from the terminal in the same folder as our application.py.

    return render_template("index.html")

### /wk7/hello/
    ../?name=David

return render_template("index.html", name=request.args.get("name", "world"))
We use request.args.get to get a parameter from the request’s URL called name.
(The second argument, world, will be the default value that’s returned if one wasn’t set.)

    {% block body %}{% endblock %} 

 **extends**, to define blocks that will be substituted
 
## froshims
### /froshims0/
    . ~/wk7/froshims0/ $ ls -1
        . application.py
        . /templates/failure.html
        . /templates/index.html
        . /templates/layout.html
        . /templates/success.html


In froshims0, we can write an application.py that can receive and respond to a POST request from a form.
The {% block body %}{% endblock %} syntax is a placeholder block in Flask.
    `if not request.form.get("name") or not request.form.get("dorm"):`

```python
    @app.route("/register", methods=["POST"])
    def register():
        if not request.form.get("name") or not request.form.get("dorm"):
            return render_template("failure.html")
        return render_template("success.html")
```
In our register function, we’ll indicate that we’re listening for a POST request,
and inside the function, just make sure that we got a value for both name and dorm.
request.form is an abstraction provided by Flask,
such that we can access the arguments, or parameters, from the request’s POST data.
```html
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
    </form>
```    

The `{% %}` syntax is actually called Jinja,
a templating language that Flask is able to understand and put together.


### /froshims1/
create a list to store all the registered students

``` python
from flask import Flask, redirect, render_template, request

# Configure app
app = Flask(__name__)

# Registered students
students = []


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/registrants")
def registrants():
    return render_template("registered.html", students=students)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    dorm = request.form.get("dorm")
    if not name or not dorm:
        return render_template("failure.html")
    students.append(f"{name} from {dorm}")
    return redirect("/registrants")
```

We create an empty list, **students = []**,  
and when we get a name and dorm in register,  
we’ll use **students.append(f"{name} from {dorm}")** to add a formatted string with that name and dorm, to the students list.  
In the registrants function, we’ll pass in our students list to the template of registered.html:
``` html
{% extends "layout.html" %}

{% block body %}
    <ul>
        {% for student in students %}
            <li>{{ student }}</li>
        {% endfor %}
    </ul>
{% endblock %}
```

### froshims2/application.py
``` python
@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    email = request.form.get("email")
    dorm = request.form.get("dorm")
    if not name or not email or not dorm:
        return render_template("failure.html")
    message = "You are registered!"
    server = smtplib.SMTP("smtp.gmail.com", 587)
    server.starttls()
    server.login("jharvard@cs50.net", os.getenv("PASSWORD"))
    server.sendmail("jharvard@cs50.net", email, message)
    return render_template("success.html")
```
The SMTP (Simple Mail Transfer Protocol) library allows us to use abstractions for sending email, and here, every time we get a valid form, we’ll send an email. By reading the documentation for smtplib and for Gmail, we can figure out the lines of code needed to log in to Gmail’s server programmatically, and send an email to the email address from our form.


### froshims3/application.py
``` python
...
@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or not request.form.get("dorm"):
        return render_template("failure.html")
    file = open("registered.csv", "a")
    writer = csv.writer(file)
    writer.writerow((request.form.get("name"), request.form.get("dorm")))
    file.close()
    return render_template("success.html")


@app.route("/registered")
def registered():
    file = open("registered.csv", "r")
    reader = csv.reader(file)
    students = list(reader)
    return render_template("registered.html", students=students)
```

### froshims4/application.py
``` python
...
    with open("registered.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames=["name", "dorm"])
        writer.writerow({"name": request.form.get("name"), "dorm": request.form.get("dorm")})
    return render_template("success.html")


@app.route("/registered")
def registered():
    with open("registered.csv", "r") as file:
        reader = csv.DictReader(file)
        students = list(reader)
    return render_template("registered.html", students=students)
```

### froshims6/index.html
with Javascript ...
``` html
...
    </form>

    <script>

        document.querySelector('form').onsubmit = function() {
            if (!document.querySelector('input').value) {
                alert('You must provide your name!');
                return false;
            }
            else if (!document.querySelector('select').value) {
                alert('You must provide your dorm!');
                return false;
            }
            return true;
        };

    </script>
```
get feedback immediately since it runs in the browser.

## Words
Let’s create a website where someone can search for words that start with some string, much like how we might want to have autocomplete. We’ll need a file called `large` that’s a list of dictionary words, and in `words0/application.py` we’ll have:

### words0
    . ~/wk7/words0/ $ 
        . application.py
        . large
        . templates/index.html
        . templates/layout.html
        . templates/search.html

/application.py
``` python
from flask import Flask, render_template, request

app = Flask(__name__)

WORDS = []
with open("large", "r") as file:
    for line in file.readlines():
        WORDS.append(line.rstrip())

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    words = [word for word in WORDS if word.startswith(request.args.get("q"))]
    return render_template("search.html", words=words)
```
- When our server starts, we’ll create a `WORDS` list from reading in each line of the `large` file, removing the new line with `rstrip`, and storing that in our list.
- In our `index` function, we’ll render `index.html`, which is just a form:
``` html    
{% extends "layout.html" %}

{% block body %}
    <form action="/search" method="get">
        <input autocomplete="off" autofocus name="q" placeholder="Query" type="text">
        <input type="submit" value="Search">
    </form>
{% endblock %}
```
- Our form will use the `get` method, since we want the query to be in the URL.

- In our `search` route, we create a list, `words`, which is a list of every `word` in our global `WORDS` list (that we read in earlier) that start with the value of the parameter `q`. It’s equivalent to:
``` py
words = []
q = request.args.get("q")
for word in WORDS:
    if word.startswith(q):
        words.append(word)
```
- Once we have a list of words that match, we’ll pass it to our template, `search.html` that will display each one with markup.
- We can run our server with **`flask run`**, and when we visit the URL, we see a form that we can type some input into. If we type in the letter `a` or `b`, we can click submit and be taken to a page with all the words in our dictionary that start with `a` or `b`. And we notice that our route is something like `/search?q=a`, though we could have changed `q` (for query) to anything we’d like. We can even change the URL with some other value for `q`, and see our results displayed.


### words1/
    . ~/wk7/words1/ $ 
        . application.py
        . large
        . templates/index.html
        . templates/search.html

- In words1, we’ll get the results list immediately with JavaScript. 
- We can click on View Source on the page, and see that our page has a bit of JavaScript after the HTML:

application.py
``` python
...
@app.route("/search")
def search():
    q = request.args.get("q")
    words = [word for word in WORDS if q and word.startswith(q)]
    return render_template("search.html", words=words)
```

index.html
``` html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>words1</title>
    </head>
    <body>

        <input autocomplete="off" autofocus placeholder="Query" type="text">

        <ul></ul>

        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
        <script>
    
            let input = document.querySelector('input');
            input.onkeyup = function() {
                $.get('/search?q=' + input.value, function(data) {
                    document.querySelector('ul').innerHTML = data;
                });
            };

        </script>

    </body>
</html>
```
- Here, we’re using a JavaScript library called jQuery, which provides us with some abstractions. We’re selecting the `input` element, and every time the `keyup` event occurs, we want to change the page. The `keyup` event will happen when we press a key in the input box, and let go. We use jQuery’s **`$.get`** function to make a GET request to our server at the `/search?q=` route, with the value of the input box appended. When we get some `data` back, the `$.get` function will call an anonymous function (a callback) to set the `innerHTML` of the `ul` on our page to that `data`.
- And notice that we provided an empty opened and closed `<ul>` element in our template, but we’ll change the HTML inside with what our server responds with.

search.html
``` html
...
        {% for word in words %}
            <li>{{ word }}</li>
        {% endfor %}
```


### words2/
    . ~/wk7/words2/ $ 
        . application.py
        . large
        . templates/index.html

- With `words2`, we have our server return data more efficiently, in a format called JSON, JavaScript Object Notation:
- The Python code in `application.py` uses a **`jsonify`** function to return a list as a JSON object:

application.py
``` python
...
@app.route("/search")
def search():
    q = request.args.get("q")
    words = [word for word in WORDS if q and word.startswith(q)]
    return jsonify(words)
```
index.html
- And our `index.html` has the JavaScript to append each word as an `<li>` element:
``` html
        <script>
            let input = document.querySelector('input');
            input.onkeyup = function() {
                $.get('/search?q=' + input.value, function(data) {
                    let html = '';
                    for (word of data) {
                        html += '<li>' + word + '</li>';
                    }
                    document.querySelector('ul').innerHTML = html;
                });
            };
        </script>
```

### words3/
    . ~/wk7/words3/ $ ls
        . index.html
        . large.js

-  In fact, since the browser can run JavaScript that can search a list, we can write all of this in JavaScript, without making a request to a server:
``` html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>words3</title>
    </head>
    <body>

        <input autocomplete="off" autofocus placeholder="Query" type="text">

        <ul></ul>

        <script src="large.js"></script>
        <script>
    
            let input = document.querySelector('input');
            input.onkeyup = function() {
                let html = '';
                if (input.value) {
                    for (word of WORDS) {
                        if (word.startsWith(input.value)) {
                            html += '<li>' + word + '</li>';
                        }
                    }
                }
                document.querySelector('ul').innerHTML = html;
            };

        </script>

    </body>
</html>
```
- When we get input from the user, we’ll just iterate over a `WORDS` array and append any `word` string that starts with the input’s value to the page as an `<li>` element.
- We’ll also have to include a `large.js` file that creates that global variable, `WORDS`, which starts with the following:
``` js
let WORDS = [
  "a",
  "aaa",
  "aaas",
  "aachen",
  "aalborg",
  "aalesund",
  "aardvark",
  ...    
```
    
With version 0, our server sent back entire, complete pages on every search.  
With version 1, we used JavaScript to make requests without navigating to another page, getting back data with markup from the server.  
With version 2, we used JavaScript, but only got back data from the server, that we then marked up in the browser.  
Finally, with version 3, we used JavaScript and the word list to accomplish the same results, but all within the browser.

### http-server
Within CS50 IDE, navigate to your homepage directory (remember how?) and then execute
> http-server


---
# my note
### on *jinja*
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
---
### on *add item to JSON*
##### to demostrate change data on LIST
``` py
# dictionary
r = {
    'name': 'Facebook, Inc.',
    'price': 198.82,
    'symbol': 'FB'
}
print(type(r)) # <class 'dict'>

# list
stocks = [
    {'stockID': 2, 'symbol': 'goog'},
    {'stockID': 3, 'symbol': 'fb'},
    {'stockID': 9, 'symbol': 'nke'},
]
print(type(stocks)) #class 'list'>

# Adding Items for DICT of LIST
for row in stocks:
    # print(row["symbol"])
    row["name"] = r["name"]
    
# to add item to the end of LIST, append() method
stocks.append({'stockID': 10})

print(stocks) # print LIST

'''
~/work8/ $ python myJson.py
<class 'dict'>
<class 'list'>
[{'stockID': 2, 'symbol': 'goog', 'name': 'Facebook, Inc.'}, {'stockID': 3, 'symbol': 'fb', 'name': 'Facebook, Inc.'}, {'stockID': 9, 'symbol': 'nke', 'name': 'Facebook, Inc.'}]

'''
```
---
### Message Flashing
> https://flask.palletsprojects.com/en/1.1.x/patterns/flashing/

#### layout.html
``` html
       {% if get_flashed_messages() %}
            <header>
                <div class="alert alert-primary border text-center" role="alert">
                    {{ get_flashed_messages() | join(" ") }}
                </div>
            </header>
        {% endif %}
```

#### application.py
``` py

        flash('SOLD!')
```


---
## Troubleshooting

### on python, flask

#### application.py
``` py
    return hello("Json: ", f"{str(stocks)}" )  ##### TEST - use str

    return hello(Symbol, f": JSON: {str(rows)}!" )  ##### TEST - use str

    return render_template("hello.html", name=str(stocks) )  ##### TEST - use str
```

``` py
@app.route("/hello")
def hello(Name="Hello, ", Text="!"):
    return render_template("hello.html", name=Name, name2=Text)
```

#### hello.html
``` html
{% extends "layout.html" %}

{% block title %}
    hello
{% endblock %}

{% block main %}
        <p>
            Hello, {{ name }} {{ name2 }}!
        </p>
{% endblock %}
```

---
### on flask, html

> use Javascript on html, eg alert('You must provide your house!');

### on flask, not application.py
let say the application is hello.py
```
~ wk7/ $ export FLASK_APP=hello.py
~/wk7/ $ flask run
 * Serving Flask app "hello.py" (lazy loading)
```
---
### jQuery $.get() Method
https://www.w3schools.com/jquery/jquery_ajax_get_post.asp
- Syntax: `$.get(URL,callback);`
- The required URL parameter specifies the URL you wish to request.
- The optional callback parameter is the name of a function to be executed if the request succeeds.

---
