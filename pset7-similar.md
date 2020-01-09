pset7/similarities/
===================
### Similarities

Implement a program that compares two files for similarities.
Implement a website that highlights similarities across files.

Determining whether two files are identical is (relatively!) trivial: iterate over the characters in each, checking whether each and every one is identical. But determining whether two files are similar is non-trivial. After all, what does it mean to be similar? Perhaps the files have lines in common. Perhaps the files have sentences in common. Perhaps the files have only substrings in common.

Suffice it to say, the challenge ahead is to determine if two files are similar!

    * application.py
    * compare*
    * helpers.py
    * /inputs/
        * requirements.txt
        * static/
        * templates/
    * /template/
        * compare.html
        * error.html
        * index.html
        * layout.html

---
## application.py
``` python
import cs50
import re
from flask import Flask, abort, redirect, render_template, request
from html import escape
from werkzeug.exceptions import default_exceptions, HTTPException

from helpers import lines, sentences, substrings

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Handle requests for / via GET (and POST)"""
    return render_template("index.html")


@app.route("/compare", methods=["POST"])
def compare():
    """Handle requests for /compare via POST"""

    # Read files
    if not request.files["file1"] or not request.files["file2"]:
        abort(400, "missing file")
    try:
        file1 = request.files["file1"].read().decode("utf-8")
        file2 = request.files["file2"].read().decode("utf-8")
    except Exception:
        abort(400, "invalid file")

    # Compare files
    if not request.form.get("algorithm"):
        abort(400, "missing algorithm")
    elif request.form.get("algorithm") == "lines":
        regexes = [f"^{re.escape(match)}$" for match in lines(file1, file2)]
    elif request.form.get("algorithm") == "sentences":
        regexes = [re.escape(match) for match in sentences(file1, file2)]
    elif request.form.get("algorithm") == "substrings":
        if not request.form.get("length"):
            abort(400, "missing length")
        elif not int(request.form.get("length")) > 0:
            abort(400, "invalid length")
        regexes = [re.escape(match) for match in substrings(
            file1, file2, int(request.form.get("length")))]
    else:
        abort(400, "invalid algorithm")

    # Highlight files
    highlights1 = highlight(file1, regexes)
    highlights2 = highlight(file2, regexes)

    # Output comparison
    return render_template("compare.html", file1=highlights1, file2=highlights2)


def highlight(s, regexes):
    """Highlight all instances of regexes in s."""

    # Get intervals for which strings match
    intervals = []
    for regex in regexes:
        if not regex:
            continue
        matches = re.finditer(regex, s, re.MULTILINE)
        for match in matches:
            intervals.append((match.start(), match.end()))
    intervals.sort(key=lambda x: x[0])

    # Combine intervals to get highlighted areas
    highlights = []
    for interval in intervals:
        if not highlights:
            highlights.append(interval)
            continue
        last = highlights[-1]

        # If intervals overlap, then merge them
        if interval[0] <= last[1]:
            new_interval = (last[0], interval[1])
            highlights[-1] = new_interval

        # Else, start a new highlight
        else:
            highlights.append(interval)

    # Maintain list of regions: each is a start index, end index, highlight
    regions = []

    # If no highlights at all, then keep nothing highlighted
    if not highlights:
        regions = [(0, len(s), False)]

    # If first region is not highlighted, designate it as such
    elif highlights[0][0] != 0:
        regions = [(0, highlights[0][0], False)]

    # Loop through all highlights and add regions
    for start, end in highlights:
        if start != 0:
            prev_end = regions[-1][1]
            if start != prev_end:
                regions.append((prev_end, start, False))
        regions.append((start, end, True))

    # Add final unhighlighted region if necessary
    if regions[-1][1] != len(s):
        regions.append((regions[-1][1], len(s), False))

    # Combine regions into final result
    result = ""
    for start, end, highlighted in regions:
        escaped = escape(s[start:end])
        if highlighted:
            result += f"<span>{escaped}</span>"
        else:
            result += escaped
    return result


@app.errorhandler(HTTPException)
def errorhandler(error):
    """Handle errors"""
    return render_template("error.html", error=error), error.code


# https://github.com/pallets/flask/pull/2314
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
```


---
## compare*
``` python
#!/usr/bin/env python3

import argparse
import re
import sys

from helpers import lines, sentences, substrings


def main():

    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--lines", action="store_true", help="compare lines")
    group.add_argument("--sentences", action="store_true", help="compare sentences")
    group.add_argument("--substrings", metavar="N", type=positive,
                       help="compare substrings of length N")
    parser.add_argument("FILE1", help="file to compare")
    parser.add_argument("FILE2", help="file to compare")
    args = vars(parser.parse_args())

    # Read files
    try:
        with open(args["FILE1"], "r") as file:
            file1 = file.read()
    except IOError:
        sys.exit(f"Could not read {args['FILE1']}")
    try:
        with open(args["FILE2"], "r") as file:
            file2 = file.read()
    except IOError:
        sys.exit(f"Could not read {args['FILE2']}")

    # Compare files
    if args["lines"]:
        matches = lines(file1, file2)
    elif args["sentences"]:
        matches = sentences(file1, file2)
    elif args["substrings"]:
        matches = substrings(file1, file2, args["substrings"])

    # Output matches, sorted from longest to shortest, with line endings escaped
    for match in sorted(matches, key=len, reverse=True):
        print(match.replace("\n", "\\n").replace("\r", "\\r"))


def positive(string):
    """Convert string to a positive integer."""
    value = int(string)
    if value <= 0:
        raise argparse.ArgumentTypeError("invalid length")
    return value


if __name__ == "__main__":
    main()
```

---
## helpers.py
``` python
# cs50-2019 helper.py
# Oct 14, 2019


def lines(a, b):
    """Return lines in both a and b"""
    # TODO

    # Python strings support methods
    # https://docs.python.org/3/library/stdtypes.html#string-methods
    m = a.splitlines()
    n = b.splitlines()
    matched = []    # Space for matched

    for x in m:
        for y in n:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched
    # https://docs.python.org/3/tutorial/datastructures.html


def sentences(a, b):
    """Return sentences in both a and b"""
    # TODO

    from nltk.tokenize import sent_tokenize
    m = sent_tokenize(a)
    n = sent_tokenize(b)
    matched = []    # Space for matched

    for x in m:
        for y in n:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched
    # https://www.nltk.org/api/nltk.tokenize.html


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # TODO

    ms = []
    for u in range(len(a)-n+1):
        ms.append(a[u:u + n])

    ns = []
    for u in range(len(b)-n+1):
        ns.append(b[u:u + n])

    matched = []
    for x in ms:
        for y in ns:
            if x == y:
                if x not in matched:
                    matched.append(x)
    return matched


# ./compare --sentences inputs/LittlePrince_HowardTranslation.txt inputs/LittlePrince_WoodsTranslation.txt
# "Goodbye," said the fox.

# ./compare --substrings 3 a1.txt a2.txt
```

---
## requirements.txt
    flask
    nltk

                 
     <!-- /template/
    # compare.html
    # error.html
    # index.html
    # layout.html
    -->

---
## compare.html
``` html
{% extends "layout.html" %}

{% block body %}

    <!-- lefthand column -->
    <div class="col-6">
        <pre>{{ file1 | safe }}</pre>
    </div>

    <!-- righthand column -->
    <div class="col-6">
        <pre>{{ file2 | safe }}</pre>
    </div>

{% endblock %}
```

---
## error.html
``` html
{% extends "layout.html" %}

{% block body %}
    <div class="col">
        <div class="jumbotron">
            <h1 class="display-3">{{ error.code }}</h1>
            <p class="lead">{{ error.name }}</p>
            <hr class="my-4"/>
            <p>{{ error.description }}</p>
        </div>
    </div>
{% endblock %}
```

---
## index.html
``` html
<!-- cs50-2019 index.html
Nov 21, 2019 -->
{% extends "layout.html" %}

{% block body %}

    <div class="col">
        <form action="/compare" enctype="multipart/form-data" method="post">

           <!-- TODO = DONE --> 
   <div class="form-group">
         <input type="file" class="form-control-file" name="file1">
     </div>

     <div class="form-group">
         <input type="file" class="form-control-file" name="file2">
     </div>

     <div class="form-group">
         <div class="form-check">
             <label class="form-check-label">
             <input type="radio" class="form-check-input" name="algorithm"value="lines"> Compare lines
             </label>
         </div>

         <div class="form-check">
             <label class="form-check-label">
             <input type="radio" class="form-check-input" name="algorithm"value="sentences"> Compare sentences
             </label>
         </div>

         <div class="form-check">
             <label class="form-check-label">
             <input type="radio" class="form-check-input" name="algorithm"value="substrings"> Compare substrings

             <input type="number" class="form-control form-control-sm" name="length" min="1" placeholder="of length n">
             <!-- The placeholder attribute specifies a hint that describes the expected value of an input field -->
             </label>
         </div>
     </div>

        <button class="btn-primary" type="submit">Compare</button>           
           <!-- TODO = DONE -->

        </form>
    </div>

{% endblock %}
```

---
## layout.html 
``` html
<!DOCTYPE html>

<html lang="en">
    <head>

        <!-- Required meta tags -->
        <meta charset="utf-8"/>
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>

        <!-- Bootstrap CSS -->
        <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/static/styles.css" rel="stylesheet"/>

        <title>Similarities</title>

    </head>
    <body>

        <nav class="navbar fixed-top navbar-dark bg-dark">
            <a class="navbar-brand" href="/">Similarities</a>
        </nav>

        <div class="container-fluid">
            <div class="row">
                {% block body %}{% endblock %}
            </div>
        </div>

        <!-- Optional JavaScript -->
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.11.0/umd/popper.min.js"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta/js/bootstrap.min.js"></script>

    </body>
</html>
```  

---
## styles.css
``` css
/*/#####/static/styles.css */
/* Fill viewport, hide scroll bar */
html, body
{
    height: 100%;
    overflow: hidden;
}

/* Ensure content is below navbar */
div.container-fluid
{
    padding-top: 56px;
}

/* Fill viewport */
div.container-fluid, div.row, div.col, div.jumbotron
{
    height: 100%;
}

/* Remove padding within column */
div.col
{
    padding-left: 0;
    padding-right: 0;
}

/* Add padding around form */
form
{
    padding: 15px;
}

/* Wrap and scroll preformatted text */
pre
{
    height: 100%;
    overflow: auto;
    padding: 15px;
    white-space: pre-wrap;
}

/* Highlight spans */
span
{
    background-color: #ff0;
}
```
