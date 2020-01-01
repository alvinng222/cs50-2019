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


""" Database name: finance.db
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
"""