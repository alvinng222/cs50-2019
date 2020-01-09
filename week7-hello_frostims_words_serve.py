# week7.py

# hello/
# frostims0/
# frostims1/
# frostims2/
# frostims3/
# frostims4/
# frostims5/
# frostims6/
# words0/
# words1/
# words2/
# words3/
# serve.py



##### hello/ #####

##### hello/application.py
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html", name=request.args.get("name", "world"))



##### hello/templates/index.html
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




##### frostims0/ #####

##### frostims0/application.py
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or not request.form.get("dorm"):
        return render_template("failure.html")
    return render_template("success.html")



##### frostims0/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims0/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
    </form>
{% endblock %}



##### frostims0/templates/layout.html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims0</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims0/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are registered! (Well, not really.)
{% endblock %}




##### frostims1/ #####

##### frostims1/application.py
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



##### frostims1/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims1/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
    </form>
{% endblock %}



##### frostims1/templates/layout.html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta content="initial-scale=1, width=device-width" name="viewport">
        <title>froshims1</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims1/templates/registered.html
{% extends "layout.html" %}

{% block body %}
    <ul>
        {% for student in students %}
            <li>{{ student }}</li>
        {% endfor %}
    </ul>
{% endblock %}




##### frostims2/ #####

##### frostims2/application.py
import os
import smtplib
from flask import Flask, render_template, request

# Configure app
app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


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



##### frostims2/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims2/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <input autocomplete="off" name="email" placeholder="Email" type="email">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
    </form>
{% endblock %}



##### frostims2/templates/layout.html
<!DOCTYPE html>

<html>
    <head>
        <meta content="initial-scale=1, width=device-width" name="viewport">
        <title>froshims2</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims2/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are registered! (Really.)
{% endblock %}




##### frostims3/ #####

##### frostims3/application.py
from flask import Flask, render_template, request
import csv

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


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
    file.close()
    return render_template("registered.html", students=students)



##### frostims3/registered.csv



##### frostims3/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims3/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register"> or see <a href="/registered">see who else is registered</a>
    </form>
{% endblock %}



##### frostims3/templates/layout.html
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims3</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims3/templates/registered.html
{% extends "layout.html" %}

{% block body %}
    <h1>Registered</h1>
    <ul>
        {% for student in students %}
            <li>{{ student[0] }} from {{ student[1] }}</li>
        {% endfor %}
    </ul>
{% endblock %}



##### frostims3/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are <a href="/registered">registered</a>! (Really.)
{% endblock %}




##### frostims4/ #####

##### frostims4/application.py
from flask import Flask, render_template, request
import csv

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or not request.form.get("dorm"):
        return render_template("failure.html")
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



##### frostims4/registered.csv
name,dorm



##### frostims4/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims4/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register"> or see <a href="/registered">see who else is registered</a>
    </form>
{% endblock %}



##### frostims4/templates/layout.html
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims4</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims4/templates/registered.html
{% extends "layout.html" %}

{% block body %}
    <h1>Registered</h1>
    <ul>
        {% for student in students %}
            <li>{{ student["name"] }} from {{ student["dorm"] }}</li>
        {% endfor %}
    </ul>
{% endblock %}



##### frostims4/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are <a href="/registered">registered</a>! (Really.)
{% endblock %}



##### frostims5/ #####

##### frostims5/application.py
from flask import Flask, render_template, request
import csv

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or not request.form.get("dorm"):
        return render_template("failure.html")
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



##### frostims5/registered.csv
name,dorm



##### frostims5/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims5/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
    </form>
{% endblock %}



##### frostims5/templates/layout.html
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims5</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims5/templates/registered.html
{% extends "layout.html" %}

{% block body %}
    <h1>Registered</h1>
    <ul>
        {% for student in students %}
            <li>{{ student["name"] }} from {{ student["dorm"] }}</li>
        {% endfor %}
    </ul>
{% endblock %}



##### frostims5/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are <a href="/registered">registered</a>! (Really.)
{% endblock %}




##### frostims6/ #####

##### frostims6/application.py
from flask import Flask, render_template, request
import csv

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or not request.form.get("dorm"):
        return render_template("failure.html")
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



##### frostims6/registered.csv
name,dorm



##### frostims6/templates/failure.html
{% extends "layout.html" %}

{% block body %}
    You must provide your name and dorm!
{% endblock %}



##### frostims6/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <h1>Register for Frosh IMs</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="dorm">
            <option disabled selected value="">Dorm</option>
            <option value="Apley Court">Apley Court</option>
            <option value="Canaday">Canaday</option>
            <option value="Grays">Grays</option>
            <option value="Greenough">Greenough</option>

            <option value="Wigglesworth">Wigglesworth</option>
        </select>
        <input type="submit" value="Register">
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

{% endblock %}



##### frostims6/templates/layout.html
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>froshims6</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### frostims6/templates/registered.html
{% extends "layout.html" %}

{% block body %}
    <h1>Registered</h1>
    <ul>
        {% for student in students %}
            <li>{{ student["name"] }} from {{ student["dorm"] }}</li>
        {% endfor %}
    </ul>
{% endblock %}



##### frostims6/templates/success.html
{% extends "layout.html" %}

{% block body %}
    You are <a href="/registered">registered</a>! (Really.)
{% endblock %}




##### words0/ #####

##### words0/application.py
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



##### words0/large
" dictionary - 143kbytes of data "


##### words0/templates/index.html
{% extends "layout.html" %}

{% block body %}
    <form action="/search" method="get">
        <input autocomplete="off" autofocus name="q" placeholder="Query" type="text">
        <input type="submit" value="Search">
    </form>
{% endblock %}



##### words0/templates/layout.html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>words0</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>



##### words0/templates/search.html
{% extends "layout.html" %}

{% block body %}
    <ul>
        {% for word in words %}
            <li>{{ word }}</li>
        {% endfor %}
    </ul>
{% endblock %}




##### words1/ #####

##### words1/application.py
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
    q = request.args.get("q")
    words = [word for word in WORDS if q and word.startswith(q)]
    return render_template("search.html", words=words)



##### words1/large
' text file -  dictionary of words'

##### words1/templates/index.html
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
'''
on websites:
[dictiona   ]
    . dictionally
    . dictionaries
    . dictionary
    . dictionary's
'''


##### words1/templates/search.html
{% for word in words %}
    <li>{{ word }}</li>
{% endfor %}




##### words2/ #####

##### words2/application.py
from flask import Flask, jsonify, render_template, request

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
    q = request.args.get("q")
    words = [word for word in WORDS if q and word.startswith(q)]
    return jsonify(words)



##### words2/large
##### words2/templates/index.html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>words2</title>
    </head>
    <body>

        <input autocomplete="off" autofocus placeholder="Query" type="text">

        <ul></ul>

        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
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

    </body>
</html>




##### words3/ #####

##### words3/large.js
'''
let WORDS = [
  "a", 
  "aaa", 
  "aaas", 
  "aachen", 
  "aalborg", 
  "aalesund", 
  "aardvark", 
  ...
'''
##### words3/templates/index.html
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

'''
~/wk7/words3/ $ http-server
Starting up http-server, serving ./

on websites:
[dictiona    ]
    . dictionally
    . dictionaries
    . dictionary
    . dictionary's

'''


##### serve.py
# Implements a web server

from http.server import BaseHTTPRequestHandler, HTTPServer


# HTTPRequestHandler class
class HTTPServer_RequestHandler(BaseHTTPRequestHandler):

    # GET
    def do_GET(self):

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header("Content-type", "text/html")
        self.end_headers()

        # Send body
        self.wfile.write(b"<!DOCTYPE html>")
        self.wfile.write(b"<html lang='en'>")
        self.wfile.write(b"<head>")
        self.wfile.write(b"<title>hello, title</title>")
        self.wfile.write(b"</head>")
        self.wfile.write(b"<body>")
        self.wfile.write(b"hello, body")
        self.wfile.write(b"</body>")
        self.wfile.write(b"</html>")


# Configure server
port = 8080
server_address = ("0.0.0.0", port)
httpd = HTTPServer(server_address, HTTPServer_RequestHandler)

# Run server
httpd.serve_forever()




##### #####
