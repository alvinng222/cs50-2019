week 8 source code - SQL
==================

- froshims/
    - lecture.db
    - store/

- ~/wk8/src8/froshims/
    - [application.py](#applicationpy)
    - [froshims.db](#froshimsdb)
    - [lecture.py](#lecturepy)
    - templates/

- ~/wk8/src8/froshims/templates/ 
    - [index.html](#indexhtml)
    - [layout.html](#layouthtml)

- ~/wk8/src8/store/ 
    - [application.py](#storeapplicationpy)
    - templates/

- ~/wk8/src8/store/templates/ 
    - [cart.html](#storetemplatescarthtml)
    - [index.html](#storetemplatesindexhtml)
    - [layout.html](#storetemplateslayouthtml)


--- 
## application.py
``` python
from flask import Flask, render_template, request

from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///froshims.db")

@app.route("/")
def index():
    q = request.args.get("q")
    rows = db.execute("SELECT * FROM registrants WHERE name = :name", name=q)
    return render_template("index.html", rows=rows)
```


---
## lecture.py

``` python
from cs50 import SQL

db = SQL("sqlite:///froshims.db")

rows = db.execute("SELECT * FROM registrants")

for row in rows:
    print(f"{row['name']} registered")
```


---
## index.html
``` html
{% extends "layout.html" %}

{% block body %}

    <ul>

        {% for row in rows %}

            <li>{{ row["name"] }} registered</li>

        {% endfor %}

    </ul>

{% endblock %}
```


---
## layout.html
``` html
<!DOCTYPE html>

<html>
    <head>
        <meta content="initial-scale=1, width=device-width" name="viewport"/>
        <title>lecture</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>

```


---
## /store/application.py
``` python
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Configure sessions
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Items for sale
ITEMS = ["foo", "bar", "baz"]

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/update", methods=["POST"])
def update():
    for item in request.form:
        session[item] = int(request.form.get(item))
    return redirect("/cart")


@app.route("/cart")
def cart():
    return render_template("cart.html", cart=session)
```


---
## cart.html
``` html
{% extends "layout.html" %}

{% block body %}
<h1>Cart</h1>
{% for item in cart %}
    {{ item }} : {{ cart[item] }}
    <br/>
{% endfor %}
<p>
    <a href="/">Continue shopping</a>.
</p>
{% endblock %}
```


---
## /store/templates/index.html
``` html
{% extends "layout.html" %}

{% block body %}
<h1>Store</h1>
<form action="/update" method="post">
    <input min="0" name="foo" type="number" value="0"/> Foo
    <br/>
    <input min="0" name="bar" type="number" value="0"/> Bar
    <br/>
    <input min="0" name="baz" type="number" value="0"/> Baz
    <br/>
    <input type="submit" value="Purchase"/>
</form>
<p>
    View your <a href="/cart">shopping cart</a>.
</p>
{% endblock %}
```


---
## /store/templates/layout.html
``` html
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width"/>
        <title>store</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>
```
---
