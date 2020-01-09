cs50 2019 week 8 lecture
========================

week8.md

## session & cookies

Then, Gmail’s server will reply with the login page. After we successfully log in, Gmail’s server will then reply with headers like this:
```    HTTP/1.1 200 OK
    Content-Type: text/html
    Set-Cookie: session=value
    ...
```
The Set-Cookie header asks our browser to save the session and value key-value pair to our computer; value will be a long random string or number that identifies us to the server.

With cookies, we can implement sessions on our server. A session is an abstraction of saved state for each user’s visit to our website; our server might give me a cookie with session=12345 and you a cookie with session=78910, and store some data for each user who visits, based on that session value.
With Flask, we only need a few lines of code to use this abstraction:

``` python
    ...
    from flask_session import Session
    ...
    app.config["SESSION_PERMANENT"] = False
    app.config["SESSION_TYPE"] = "filesystem"
    Session(app)
    ...
    @app.route("/update", methods=["POST"])
    def update():
        for item in request.form:
            session[item] = int(request.form.get(item))
        return redirect("/cart")
```    
---
## database, SQL


## SQLite

* We’ll start by typing **`sqlite3 froshims3.db`**, and we’ll be able to create a table in that database with a command like 
`CREATE TABLE 'registrants' ('id' integer, 'name' varchar(255), 'dorm' varchar(255));`. We specify the name of our new table, and for each column or field, the type of data. And by convention, we use 255 for our varchar fields, since that used to be the maximum for many older databases, and are probably enough for all realistic possibilities, without being too excessive.

* Nothing happens at our command line after, but we can type **`.schema`** and see the schema, or description, of our table:
`.schema` command in sqlite in command line, showing our original `CREATE TABLE` command
* We can add a row to our table with `INSERT INTO registrants (id, name, dorm) VALUES(1, 'Brian', 'Pennypacker');`, 
and conventionally the uppercased words are SQL keywords, while the rest are words specific to our data.
* We can see our table with `SELECT * FROM registrants;`, and see our table printed out.
* And we can easily filter our data with `SELECT * FROM registrants WHERE dorm = 'Matthews';`. 
We can specify just the fields we want to get back, too, with something 
like `SELECT name FROM registrants WHERE dorm = 'Matthews';`
* We can change rows with something like `UPDATE registrants SET dorm = 'Canaday' WHERE id = 1;`.
* We can delete rows with something like `DELETE FROM registrants WHERE id = 1;`.

mynote: `.quit`                  to Exit this program, SQLite

---
## phpLiteAdmin
The CS50 IDE also has a graphical program, phpLiteAdmin, which can open SQLite files too. 
We can double-click froshims3 in our files list on the IDE, and be able to browse rows. 

To search, add percent, like wildcards...
```
SELECT * FROM Album WHERE Title LIKE  '%Rock%';
```


---
## SQL python, flask
* We can import the CS50 SQL library to execute queries easily, with `lecture.py`:
``` python
    from cs50 import SQL

    db = SQL("sqlite:///froshims.db")

    rows = db.execute("SELECT * FROM registrants)

    for row in rows:
        print(f"{row['name']} registered")
```
* Since we can query a database in Python, we can also integrate that into a Flask application. 
We can create a Flask `application.py` file:
``` python
    from flask import Flask, render_template, request

    from cs50 import SQL

    app = Flask(__name__)

    db = SQL("sqlite:///lecture.db")

    @app.route("/")
    def index():
        rows = db.execute("SELECT * FROM registrants")
        return render_template("index.html", rows=rows)
```
* We select everything from the `registrants` table and store that in a variable called `rows`.
* Then, we pass the results, `rows`, to the template.
* In our template, `templates/index.html`, we’ll iterate over a list of rows that are passed in, 
displaying each one’s `name` field:
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
* We can implement a search functionality too, by adding a q URL parameter:
``` python
    ...
    @app.route("/")
    def index():
        q = request.args.get("q")
        rows = db.execute(f"SELECT * FROM registrants WHERE name = '{q}'")
        return render_template("index.html", rows=rows)
    Now, only rows that have a matching name will be returned to our template to display.
```
ex:
`https://06d9fcd2-fba2-4977-860c-45505570ac8d-ide.cs50.xyz:8080/?q=Allan`

---
## lecture.db
* A sample database of music metadata, `lecture.db`,... 
It demonstrates how we can relate data in different tables.
* We can use phpLiteAdmin in the CS50 IDE, as before, to look at the tables and rows in `lecture.db`, 
and run a query like `SELECT * FROM Album WHERE ArtistId = 1`; 
to see all the albums by the artist with ID 1. 
We can use SQL to join tables, getting the artist’s name too, 
with `SELECT * FROM Album, Artist WHERE Album.ArtistId = Artist.ArtistId;`. 
The `name` from the Artist table will also be selected (since we said `SELECT *`), 
and matched to each row in Album where the `ArtistId` field is the same. 
Another way to express the same idea would be 
`SELECT * FROM Artist JOIN Album ON Artist.ArtistId = Album.ArtistId;`.

---
## Problems
* One problem with databases is race conditions, ...
* Another problem in SQL is called a **SQL injection attack**, ...
* To guard against this, we can sanitize user data, or escape characters like semicolons and single quotes, 
such that they are interpreted as part of the string, rather than special characters that end strings or commands.
* The CS50 SQL Library allows us to escape user input with the execute function, and we can write 
`rows = db.execute("SELECT * FROM registrants WHERE name = :name", name=q)` 
where we use a special placeholder, `:name`, that will be escaped before it is substituted into the string.
* Another example would be typing in `' OR '1' = '1` in a password field; ...


---



