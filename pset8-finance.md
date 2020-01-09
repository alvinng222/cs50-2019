pset8 - finance; python flask on html 
====
dated: Nov 02, 2019

assignment from https://docs.cs50.net/2019/x/psets/8/finance/finance.html

* ## submission:
   * /finance/
       * application.py
       * finance.db
       * [helpers.py](#helperspy)
       * requirements.txt
   * /finance/static/
       * favicon.ico
       * styles.css
   * /finance/templates/
       * [apology.html](#apologyhtml)
       * [buy.html](#buyhtml)
       * [chgPwd.html](#chgPwdhtml)
       * [hello.html](#hellohtml)
       * [history.html](#historyhtml)
       * [index.html](#indexhtml)
       * [layout.html](#layouthtml)
       * [login.html](#loginhtml)
       * [quote.html](#quotehtml)
       * [quoted.html](#quotedhtml)
       * [register.html](#registerhtml)
       * [sell.html](#sellhtml)
* [terminals](terminals)


---
### Configuring
Before getting started on this assignment, we’ll need to register for an API key in order to be able to query IEX’s data. To do so, follow these steps:
* Visit iexcloud.io/cloud-login#/register/.
* Enter your email address and a password, and click "Create account".
* Once you’ve confirmed your account via a confirmation email, sign in to iexcloud.io.
* Click API Tokens.
* Copy the key that appears under the Token column (it should begin with pk_).
* In a terminal window within CS50 IDE, execute:
  * export API_KEY=value
  * where value is that (pasted) value, without any space immediately before or after the =. You also may wish to paste that value in a text document somewhere, in case you need it again later.


---
## application.py
``` python
""" application.py cs50 20191231
    refer to index.html for API and flask run to start
    & check50 status """

import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # call stocks LIST, sorted, ORDER BY symbol
    stocks = db.execute("SELECT * FROM stock WHERE userID= :userID AND shares !=0 ORDER By symbol",
                        userID=session["user_id"])

    balTotal = 0
    # add in name into 'list'
    for row in stocks:
        Symbol = row["symbol"]
        symJson = lookup(Symbol)        # lookup() from helpers.py
        row["name"] = symJson["name"]   # Adding name into dict
        price = symJson["price"]          # usd() from helpers.py
        row["price"] = usd(price)       # Adding price into dict
        total = row["shares"] * price
        row["total"] = usd(total)
        balTotal = balTotal + total
        row["balTotal"] = usd(balTotal)

    # SELECT cash FROM users WHERE id = 6
    userC = db.execute("SELECT cash FROM users WHERE id= :userID", userID=session["user_id"])
    for row in userC:
        cash = row["cash"]
    balTotal = balTotal + cash

    return render_template("index.html", stocks=stocks, cash=usd(cash), balTotal=usd(balTotal))

    """ # to add item to the end of LIST, append() method
    stocks.append({'symbol': 'CASH', 'total': usd(cash), 'balTotal': usd(balTotal) })
    """


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # example Symbol = "GOOG"
        Sym = request.form.get("symbol")

        # Ensure Symbol was submitted
        if not Sym:
            return apology("missing symbol", 400)

        # lookup() from helpers.py
        r = lookup(Sym)

        # Check if Sym was invalid
        if not r:
            return apology("invalid symbol")

        symbol = r["symbol"]    # for upper case, original symbol

        shares = request.form.get("shares")

        # Ensure shares was submitted
        if not shares:
            return apology("missing shares", 400)

        # stock’s current price
        price = r["price"]    # pp=usd(price)

        # total cost, convert string shares to integer
        tCost = int(shares)*price

        # SELECT cash FROM users WHERE id = 6
        userID = session["user_id"]
        userC = db.execute("SELECT cash FROM users WHERE id= :userID", userID=userID)
        for row in userC:
            balanceC = row["cash"]

        ''' # Query database for user balace Cash rows[0]["id"]
        userID=session["user_id"]
        balCash = db.execute("SELECT cash FROM users WHERE id = :userID", userID=userID)
        BC=balCash[0]       # convert list to .dict
        balanceC=BC["cash"] # "cash" out from .dict . '''

        # compare users balance against buying price for affordability
        if balanceC > tCost:
            # check table/stock if symbol available, else create new
            # SELECT * FROM stock WHERE symbol = "aapl" AND userID=1
            rows = db.execute("SELECT * FROM stock WHERE symbol = :symbol AND userID = :userID",
                              symbol=symbol, userID=userID)
            if len(rows) != 1:
                result = db.execute("INSERT INTO stock (symbol, userID ) VALUES(:symbol, :userID)",
                                    symbol=symbol, userID=userID)
                if not result:
                    return apology("symbol unavailable", 400)

            # call existing stockID, insert new transaction to history
            rows = db.execute("SELECT * FROM stock WHERE symbol = :symbol AND userID = :userID",
                              symbol=symbol, userID=userID)
            row = rows[0]
            stockID = row["stockID"]

            result1 = db.execute("INSERT INTO history (userID, symbol, shares, price) VALUES(:userID, :symbol, :shares, :price)",
                                 userID=userID, symbol=symbol, shares=shares, price=price)

            # update table/stock
            result2 = db.execute("UPDATE stock SET shares = shares + :shares WHERE stockID = :stockID",
                                 shares=shares, stockID=stockID)

            # update user's balance
            result3 = db.execute("UPDATE users SET cash = cash - :tCost WHERE id = :userID",
                                 tCost=tCost, userID=userID)

            if not result1 or not result2 or not result3:
                return apology("transaction error", 400)

            # Message Flashing, get_flashed_messages() from layout.html
            # https://flask.palletsprojects.com/en/1.1.x/patterns/flashing/
            flash('BROUGHT!')

            # Redirect user to home page, after transacted
            return redirect("/")
            # return hello("Brought! ", f"Now tCost {usd(tCost)}" ) # redirect("/")  ##### TEST
        else:
            # if user cannot afford
            return apology("can't afford", 400)

    return render_template("buy.html")
    # return apology("TODO")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    """
    The implementation of check in such a way that it checks whether a
    username is available.

    The route should accept, via GET, an HTTP parameter called username.

    If the value of username is of length at least 1 and does not already
    belong to a user in the database, the route return, in JSON
    format, true, signifying that the username is (as of that moment)
    available. Else it should return, in JSON format, false. Jsonify in
    Flask can return a value in JSON format.    """

    # use request.args.get to get a parameter from the request’s URL called q.
    username = request.args.get("username")   # via GET, an HTTP parameter

    # call users LIST
    rows = db.execute("SELECT * FROM users WHERE username= :username", username=username)
    if len(rows) > 0:
        return jsonify("true")      # if there are any data form
    else:
        return jsonify("false")

    # test by http ...  /check?username=JJLin


@app.route("/chgPwd", methods=["GET", "POST"])
@login_required
def chgPwd():
    """ 20191222 Change Password """

    userID = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("oldPwd"):
            return apology("must provide orginal password", 403)

        # Ensure new password was submitted
        newPwd = request.form.get("newPwd")
        if not newPwd:
            return apology("must provide NEW password", 400)

        # Ensure password and confirmation was matchded
        confirmation = request.form.get("confirmation")
        if newPwd != confirmation:
            return apology("passwords don't match", 400)

        # Ensure old password is correct
        rows = db.execute("SELECT * FROM users WHERE ID = :userID", userID=userID)

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("oldPwd")):
            return apology("invalid original password", 403)

        # Hash the new password
        newHash = generate_password_hash(newPwd)

        # update new hash into database
        result = db.execute("UPDATE users SET hash = :newHash WHERE rowid = :userID",
                            newHash=newHash, userID=userID)
        if not result:
            return apology("new  pasword error", 400)

        # Redirect user to home page
        return redirect("/")

    # to place username to html, so as Google will not store wrong username
    # work only outside the above 'if' loop
    rows = db.execute("SELECT username FROM users WHERE ID = :userID", userID=userID)
    for row in rows:
        username = row["username"]

    return render_template("chgPwd.html", username=username)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""  # return apology("TODO")

    # call history LIST
    rows = db.execute("SELECT * FROM history WHERE userID= :userID", userID=session["user_id"])

    for row in rows:
        row["price"] = usd(row["price"])    # convert integer to string with unit

    return render_template("history.html", rows=rows)
    # return render_template("hello.html", name=str(rows) )  ##### TEST - use str


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username true and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote. TODO"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # example Symbol = "GOOG"
        Symbol = request.form.get("symbol")

        # Ensure Symbol was submitted
        if not Symbol:
            return apology("missing symbol", 400)

        # lookup() from helpers.py
        quote = lookup(Symbol)

        # Check if Symbol was invalid
        if not quote:
            return apology("invalid symbol", 400)

        # redirect to quoteD page, usd() from hellpers.py
        pp = usd(quote["price"])
        return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=pp)

        # return hello(rJson, Symbol)       ##### TEST

    return render_template("quote.html")
    # return apology("TODO")    # was "to do"


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user - TODO """

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted. # not required since will route to /check
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure password and confirmation was matchded
        confirmation = request.form.get("confirmation")
        if password != confirmation:
            return apology("passwords don't match", 400)

        # Hash the password
        hash = generate_password_hash(password)

        # insert username and hash into database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username=request.form.get("username"), hash=hash)
        if not result:
            return apology("username unavailable", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    return render_template("register.html")
    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""  # was return apology("TODO")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # input from sell.html, example Symbol = "GOOG"
        symbol = request.form.get("symbol")

        # Ensure Symbol was submitted
        if not symbol:
            return apology("symbol not selected", 400)

        # input from sell.html
        getShares = request.form.get("shares")

        # Ensure shares was submitted
        if not getShares:
            return apology("missing shares")

        # convert string shares to integer
        getShares = int(getShares)

        # Ensure shares is positive
        if getShares < 1:
            return apology("shares must be positive")

        # lookup() from helpers.py
        quote = lookup(symbol)

        userID = session["user_id"]

        # recall existing stockID, and shares from stock
        rows = db.execute("SELECT * FROM stock WHERE symbol = :symbol AND userID = :userID",
                          symbol=symbol, userID=userID)
        for row in rows:
            stockShares = row["shares"]
            stockID = row["stockID"]

        # Ensure if shares not more than stock, convert string shares to integer
        if getShares > stockShares:
            return apology("too many shares")
        elif getShares < stockShares:
            stockShares -= getShares    # now shares from stock less input
            # eg. UPDATE stock SET shares = 80 WHERE stockID = 10;
            result = db.execute("UPDATE stock SET shares = :stockShares WHERE stockID = :stockID",
                                stockShares=stockShares, stockID=stockID)
        else:   # getShares == stockShares
            # eg. DELETE FROM stock WHERE stockID = 13
            result = db.execute("DELETE FROM stock WHERE stockID = :stockID", stockID=stockID)

        # total sell price
        tSell = getShares*quote["price"]

        # update users cash. eg. UPDATE users SET cash = cash + 1000 WHERE id = 6;
        result = db.execute("UPDATE users SET cash = cash + :tSell WHERE id = :userID",
                            tSell=tSell, userID=userID)

        # update transaction history
        # eg. INSERT INTO history (stockID, shares, price) VALUES(2, -1, 100)
        result = db.execute("INSERT INTO history (userID, symbol, shares, price) VALUES(:userID, :symbol, :shares, :tSell)",
                            userID=userID, symbol=symbol, shares=-getShares, tSell=tSell)

        # Message Flashing, get_flashed_messages() from layout.html
        # https://flask.palletsprojects.com/en/1.1.x/patterns/flashing/
        flash('SOLD!')

        # Redirect user to home page
        return redirect("/")

    # for template sell.html
    # call stocks LIST, sorted, ORDER BY symbol
    stocks = db.execute("SELECT symbol FROM stock WHERE userID= :userID AND shares !=0 ORDER By symbol",
                        userID=session["user_id"])

    return render_template("sell.html", stocks=stocks)
    # return hello(symbol, f": JSON: {str(rows)}! shares: {type(shares)}." )  ##### TEST


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


@app.route("/hello")
def hello(Name="Hello, ", Text="!"):
    return render_template("hello.html", name=Name, name2=Text)
    """ how it use:
    return hello(Symbol, f": JSON: {str(rows)}!" )  ##### TEST - use str
    return render_template("hello.html", name=str(stocks) )  ##### TEST - use str
    or
    use Javascript on html, eg alert('You must provide your house!');
    """
```


---
## finance.db
``` sql
CREATE TABLE 'users' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'username' TEXT NOT NULL,
    'hash' TEXT NOT NULL,
    'cash' NUMERIC NOT NULL DEFAULT 10000.00 )

CREATE TABLE 'stock' (
    'stockID' integer PRIMARY KEY AUTOINCREMENT NOT NULL,
    'symbol' char(4) NOT NULL,
    'userID' integer NOT NULL,
    'shares' INTEGER DEFAULT 0)

CREATE TABLE 'history' (
    'histID' integer PRIMARY KEY AUTOINCREMENT NOT NULL,
    'userID' integer NOT NULL,
    'symbol' char(4) NOT NULL,
    'shares' integer NOT NULL,
    'price' numeric(5,2) NOT NULL,
    'dateTime' datetime DEFAULT CURRENT_TIMESTAMP)
```

---
## helpers.py
``` python
import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"
```


---
## requirements.txt
```
    cs50
    Flask
    Flask-Session
    requests
```

---
## styles.css
``` css
nav .navbar-brand
{
    /* size for brand */
    font-size: xx-large;
}

/* colors for brand */
nav .navbar-brand .blue
{
    color: #537fbe;
}
nav .navbar-brand .red
{
    color: #ea433b;
}
nav .navbar-brand .yellow
{
    color: #f5b82e;
}
nav .navbar-brand .green
{
    color: #2e944b;
}

main .form-control
{
    /* center form controls */
    display: inline-block;

    /* override Bootstrap's 100% width for form controls */
    width: auto;
}

main
{
    /* scroll horizontally as needed */
    overflow-x: auto;

    /* center contents */
    text-align: center;
}

main img
{
    /* constrain images on small screens */
    max-width: 100%;
}

/* alvin dtd 191125 */
table
{
    /* center contents */
    text-align: left;
}
```


---
## apology.html
``` html
{% extends "layout.html" %}

{% block title %}
    Apology
{% endblock %}

{% block main %}
    <img alt="{{ top }}" class="border" src="http://memegen.link/custom/{{ top | urlencode }}/{{ bottom | urlencode }}.jpg?alt=https://i.imgur.com/CsCgN7Ll.png" title="{{ top }}">
{% endblock %}
```

---
## buy.html
``` html 
<!-- buy.html dtd Nov 15, 2019 -->
{% extends "layout.html" %}

{% block title %}
    Buy
{% endblock %}

{% block main %}
    <form action="/buy" method="post">
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text">
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="shares" placeholder="Shares" min="1" type="number">
        </div>
        <button class="btn btn-primary" type="submit">Buy</button>
    </form>
{% endblock %}

```


---
## chgPwd.html
``` html 
<!-- chgPwd.html dtd Dec 22, 2019 -->
{% extends "layout.html" %}

{% block title %}
    register
{% endblock %}

{% block main %}
    <form action="/chgPwd" method="post">
        <div class="form-group">
            <input class="form-control" name="username" value="{{username}}" type="text" readonly>
        </div>
        <div class="form-group">
            <input class="form-control" name="oldPwd" placeholder="Old password" type="password">
        </div>
        <div class="form-group">
            <input class="form-control" name="newPwd" placeholder="New password" type="password">
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Confirm new password" type="password">
        </div>
        <button class="btn btn-primary" type="submit">Update password</button>
    </form>

{% endblock %}

<!--
Auto Sign-in
Automatically sign in to websites using stored credentials. If disabled, you will be
asked for confirmation every time before signing in to a website.
View

<div class="form-group">
    <input autocomplete="off" autofocus class="form-control" name="username" placeholder="{{username}}" type="text">
</div>
// comments, unable to kick the alert with this username
->
```


---
## hello.html
``` html 
<!-- hello.html dtd Nov 14, 2019 -->
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
## history.html
``` html 
<!-- history.html dtd Nov 28, 2019 -->
{% extends "layout.html" %}

{% block title %}
    History
{% endblock %}

{% block main %}

<!-- from bootstraps, table -->
<table class="table table-striped">
    <thead>
        <tr>
            <th scope="col">Symbol</th>
            <th scope="col">Shares</th>
            <th scope="col">Price</th>
            <th scope="col">Transacted</th>
        </tr>
    </thead>
    <tbody>
        {% for row in rows %}
            <tr>
                <td> {{ row["symbol"] }} </td>
                <td> {{ row["shares"] }} </td>
                <td> {{ row["price"] }} </td>
                <td> {{ row["dateTime"] }} </td>
            </tr>
        {% endfor %}
    </tbody>
</table>

{% endblock %}

```


---
## index.html
``` html 
<!-- index.html dtd Nov 22, 2019 -->
{% extends "layout.html" %}

{% block title %}
    Portfolio
{% endblock %}

{% block main %}

<!-- from bootstraps, table -->
<table class="table table-striped">
    <thead>
        <tr>
            <th scope="col">Symbol</th>
            <th scope="col">Name</th>
            <th scope="col">Shares</th>
            <th scope="col">Price</th>
            <th scope="col">TOTAL</th>
        </tr>
    </thead>
    <tbody>
        {% for stock in stocks %}
            <tr>
                <td> {{ stock.symbol }} </td>
                <td> {{ stock.name }} </td>
                <td> {{ stock.shares }} </td>
                <td> {{ stock.price }} </td>
                <td> {{ stock.total }} </td>
            </tr>
        {% endfor %}
        <tr>
            <td> CASH </td>
            <td colspan="3"> <!-- create merged empty spaces --> </td>
            <td> {{ cash }} </td>
        </tr>
    </tbody>
    <tfoot>
        <tr>
            <td colspan='4'> <!-- create merged empty spaces --> </td>
            <td> <b>{{ balTotal }}</b> </td>
        </tr>
    </tfoot>
</table>

{% endblock %}
```


---
## layout.html
``` html 
<!DOCTYPE html>

<html lang="en">

    <head>

        <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- documentation at http://getbootstrap.com/docs/4.1/, alternative themes at https://bootswatch.com/ -->
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">

        <!-- https://favicon.io/emoji-favicons/money-mouth-face/ -->
        <link href="/static/favicon.ico" rel="icon">

        <link href="/static/styles.css" rel="stylesheet">

        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

        <title>C$50 Finance: {% block title %}{% endblock %}</title>

    </head>

    <body>

        <nav class="navbar navbar-expand-md navbar-light bg-light border">
            <a class="navbar-brand" href="/"><span class="blue">C</span><span class="red">$</span><span class="yellow">5</span><span class="green">0</span> <span class="red">Finance</span></a>
            <button aria-controls="navbar" aria-expanded="false" aria-label="Toggle navigation" class="navbar-toggler" data-target="#navbar" data-toggle="collapse" type="button">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbar">
                {% if session.user_id %}
                    <ul class="navbar-nav mr-auto mt-2">
                        <li class="nav-item"><a class="nav-link" href="/quote">Quote</a></li>
                        <li class="nav-item"><a class="nav-link" href="/buy">Buy</a></li>
                        <li class="nav-item"><a class="nav-link" href="/sell">Sell</a></li>
                        <li class="nav-item"><a class="nav-link" href="/history">History</a></li>

                        <!-- 20191222 change pwd -->
                        <li class="nav-item"><a class="nav-link" href="/chgPwd">Chg_Pwd</a></li>
                    </ul>
                    <ul class="navbar-nav ml-auto mt-2">
                        <li class="nav-item"><a class="nav-link" href="/logout">Log Out</a></li>
                    </ul>
                {% else %}
                    <ul class="navbar-nav ml-auto mt-2">
                        <li class="nav-item"><a class="nav-link" href="/register">Register</a></li>
                        <li class="nav-item"><a class="nav-link" href="/login">Log In</a></li>
                    </ul>
                {% endif %}
            </div>
        </nav>

        {% if get_flashed_messages() %}
            <header>
                <div class="alert alert-primary border text-center" role="alert">
                    {{ get_flashed_messages() | join(" ") }}
                </div>
            </header>
        {% endif %}

        <main class="container p-5">
            {% block main %}{% endblock %}
        </main>

        <footer class="small text-center text-muted">
            Data provided for free by <a href="https://iextrading.com/developer">IEX</a>. View <a href="https://iextrading.com/api-exhibit-a/">IEX’s Terms of Use</a>.
        </footer>

    </body>

</html>

```


---
## login.html
``` html 
{% extends "layout.html" %}

{% block title %}
    Log In
{% endblock %}

{% block main %}
    <form action="/login" method="post">
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="username" placeholder="Username" type="text">
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="Password" type="password">
        </div>
        <button class="btn btn-primary" type="submit">Log In</button>
    </form>
{% endblock %}
```


---
## quote.html
``` html 
<!-- quote.html dtd Nov 14, 2019 -->
{% extends "layout.html" %}

{% block title %}
    quote
{% endblock %}

{% block main %}
    <form action="/quote" method="post">
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text">
        </div>

        <button class="btn btn-primary" type="submit">Quote</button>
    </form>
{% endblock %}

```


---
## quoted.html
``` html 
<!-- quoted.html dtd Nov 14, 2019 -->
{% extends "layout.html" %}

{% block title %}
    Quoted
{% endblock %}

{% block main %}

        <!-- A share of Alphabet, Inc. (GOOG) costs $1,298.00. -->
        <p>
            A share of {{ name }} ({{ symbol }}) costs {{ price }}.

        </p>

{% endblock %}

<!-- script >
var txt = '{"name":"John", "age":30, "city":"New York"}'
var obj = JSON.parse(result);
document.getElementById("demo").innerHTML = obj.name + ", " + obj.age;
script>  -->
```


---
## register.html
``` html 
<!-- register.html dtd Nov 11, 2019 -->
{% extends "layout.html" %}

{% block title %}
    register
{% endblock %}

{% block main %}
    <form action="/register" method="post">
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="username" placeholder="Username" type="text">
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="Password" type="password">
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Password (again)" type="password">
        </div>
        <button class="btn btn-primary" type="submit">Register</button>
    </form>

     <script>
        /*  Aims: It prevents submission of your registration form if the inputted
            username is already taken, letting the user know, as via alert      */

        /*  jQuery $.get() Method
            Description: Load data from the server using a HTTP GET request.
            jQuery.get( url [, data ] [, success ] [, dataType ] )
            https://api.jquery.com/jQuery.get/#jqxhr-object     */

        /*  ##$.get## dont work on querySelector('form').onsubmit, because
            after the browser loaded all, it didnt update 'status' at
            the beginning.      */

        var status;
        let input = document.querySelector('input');

        // constantly get reflesh from any key press with .onkeyup
        input.onkeyup = function() {
            $.get('/check?username=' + input.value, function(data) {
                    status = data;
            }, "json");
            console.log("onkeyup status: " + status);
        };

        // call output after .onsubmit
        document.querySelector('form').onsubmit = function(event) {
            if (!input.value) {
                alert('You must provide your username!');
                return false;
            }
            console.log("form status: " + status);

            if (status === "true"){
                alert("Username is not available");
                event.preventDefault();
            }
        };
        //myFunction(event);

        //Click the button to find out if the onclick event is a cancelable event./
        //<button onclick="myFunction(event)">Try it</button>
        function myFunction(event) {
            var x = event.cancelable;
            //document.getElementById("demo").innerHTML = "Cancelable: " + x;
            console.log("Cancelable: " + x);
        }

    </script>

{% endblock %}
```


---
## sell.html
``` html 
<!-- sell.html dtd Nov 25, 2019 -->
{% extends "layout.html" %}

{% block title %}
    Sell
{% endblock %}

{% block main %}
    <form action="/sell" method="post">
        <div class="form-group">
            <!-- select, drop down form -->
            <select class="form-control" name="symbol">
                <option disable select value="">Symbol</option> <!-- from https://finance.cs50.net/sell -->
                {% for stock in stocks %}
                    <!-- value=" {{ stock.symbol }} "  the SPACING caused the issues -->
                    <option value="{{ stock.symbol }}"> {{ stock.symbol }} </option>
                {% endfor %}
            </select -->
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="shares" placeholder="Shares" min="0" type="number">
        </div>
        <button class="btn btn-primary" type="submit">Sell</button>
    </form>
{% endblock %}

<!--
        can also input not from the list, good use in buy.html
        <div class="form-group">
            <input list="symbols" class="form-control" name="symbol" placeholder="Symbol">
            <datalist id="symbols">
                {% for stock in stocks %}
                    <option value="{{ stock.symbol }}">
                {% endfor %}
            </datalist>
        </div>
-->
```


---
## terminals
```
<!--
~/pset8/ $ cd finance
~/pset8/finance/ $ export API_KEY=pk_4ae54105aac94b909dab2c48b16a875d
~/pset8/finance/ $ flask run

~/pset8/finance/ $ check50 cs50/problems/2019/x/finance
Connecting.....
:) application.py exists
:) application starts up
:) register page has all required elements
:) registering user succeeds
:) registration with an empty field fails
:) registration with password mismatch fails
:( /check route confirms whether username is available
    route did not return true when username is available
:) registration rejects duplicate username
:) login page has all required elements
:) logging in as registered user succceeds
:) quote page has all required elements
:) quote handles invalid ticker symbol
:) quote handles blank ticker symbol
:) quote handles valid ticker symbol
:) buy page has all required elements
:) buy handles invalid ticker symbol
:( buy handles fractional, negative, and non-numeric shares
    expected status code 400, but got 200
:) buy handles valid purchase
:) sell page has all required elements
:) sell handles invalid number of shares
:) sell handles valid sale
To see the results in your browser go to https://submit.cs50.io/check50/e4a34b06f9d6eec21eb601769df1e6dd71309504
~/pset8/finance/ $

-->
```
---
---
