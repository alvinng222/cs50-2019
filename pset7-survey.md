pset7 /survey
=============
* application.py
* static/
* survey.csv
* templates/
* /static/styles.css
* /templates/error.html
* /templates/form.html
* /templates/layput.html
* /templates/sheet.html

Pset7 survey problem (https://docs.cs50.net/2019/x/psets/7/survey/survey.html)

---
## application.py
``` python
# Survey . dated Nov 2019
# Implement a web app that enables a user to
# fill out a form, a la Google Forms, the results of which are saved to a comma-separated-value (CSV) file on the server, and
# view a table of all of the submissions received, a la Google Sheets,

# This file represents your web app’s "controller,"

# to run the html by type: flask run
# ~/pset7/survey/ $ flask run

import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

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


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


# TODO
@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("surveyName")
    house = request.form.get("surveyHouse")
    option = request.form.get("surveyOption")

    # from cs50 lecture week7 froshims4
    if not name or not house or not option:
        return render_template("error.html", message="FAIL")
    with open("survey.csv", "a") as file:
        writer = csv.DictWriter(file, fieldnames=["name", "house", "option"])
        writer.writerow({"name": name, "house": house, "option": option})
    return redirect("/sheet")


# TODO
@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open("survey.csv", "r") as file:
        reader = csv.DictReader(file)
        slist = list(reader)
    return render_template("sheet.html", slist=slist)
    # note that survey.csv need to start with "name,house,option"
```

---
## style.css
    /* TODO */


---
## form.html
``` html
{% extends "layout.html" %}

{% block main %}

    <!-- http://getbootstrap.com/docs/4.1/content/typography/ -->
    <h1 class="mb-3">Form</h1>

    <!-- http://getbootstrap.com/docs/4.1/components/forms/ -->
    <form action="/form" method="post">

        <!-- TODO -->
        <!-- https://www.w3schools.com/bootstrap4/bootstrap_forms.asp -->
        <div class="form-group">
            <label class="mr-sm-2 sr-only" for="surveyName">Name</label>
            <input type="text" class="form-control col-sm-3" id="surveyName"
            placeholder="Name" name="surveyName" required >
        </div>

        <div class="form-group">
            <label class="mr-sm-2 sr-only" for="surveyHouse">House</label>
            <select name="surveyHouse" class="custom-select col-sm-2" id="surveyHouse" required >
                <option disabled selected value="">House</option>
                <option>Gryffindor</option>
                <option>Hufflepuff</option>
                <option>Ravenclaw</option>
                <option>Slytherin</option>
            </select>
        </div>

        <div class="form-group">
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="surveyOption"
                        value="Beater" required>Beater
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="surveyOption" value="Chaser">Chaser
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="surveyOption" value="Keeper">Keeper
                </label>
            </div>
            <div class="form-check">
                <label class="form-check-label">
                    <input type="radio" class="form-check-input" name="surveyOption" value="Seeker">Seeker
                </label>
            </div>
        </div>
        <!-- https://getbootstrap.com/docs/4.1/components/forms/#validation -->

        <!-- http://getbootstrap.com/docs/4.1/components/buttons/ -->
        <button class="btn btn-primary" type="submit">Submit</button>

    </form>

    <script>

        /* TODO */
        /* from cs50 lecture week7 froshims6 */
        document.querySelector('form').onsubmit = function() {
            if (!document.querySelector('input').value) {
                alert('You must provide your name!');
                return false;
            }
            else if (!document.querySelector('select').value) {
                alert('You must provide your house!');
                return false;
            }
            return true;
        };

    </script>

{% endblock %}
```

---
## layout.html
``` html
<!DOCTYPE html>

<html>

    <head>

        <meta name="viewport" content="initial-scale=1, width=device-width">

        <!-- http://getbootstrap.com/docs/4.1/ -->
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

        <link href="/static/styles.css" rel="stylesheet">

        <title>Survey</title>

    </head>

    <body>

        <!-- http://getbootstrap.com/docs/4.1/components/navbar/ -->
        <nav class="navbar navbar-expand-sm navbar-dark bg-dark">
            <a class="navbar-brand mb-1 h1" href="/">Survey</a>
            <button aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation" class="navbar-toggler" type="button" data-target="#navbarNav" data-toggle="collapse">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav">
                    <li class="nav-item">
                        <a class="nav-link" href="/form">Form</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="/sheet">Sheet</a>
                    </li>
                </ul>
            </div>
        </nav>

        <!-- http://getbootstrap.com/docs/4.1/layout/overview/#containers -->
        <main class="container-fluid p-5">
            {% block main %}{% endblock %}
        </main>

    </body>

</html>

```

---
## error.html
``` html
{% extends "layout.html" %}

{% block main %}

    <!-- http://getbootstrap.com/docs/4.1/components/alerts/ -->
    <div class="alert alert-danger" role="alert">
        <h4 class="alert-heading">Error</h4>
        <p>{{ message }}</p>
    </div>

{% endblock %}

```


---
## sheet.html
``` html
<!-- TODO: sheet.html, dated Nov 2019 -->
{% extends "layout.html" %}

{% block main %}

    <!-- https://datatables.net/examples/basic_init/table_sorting.html -->
    <link rel="stylesheet" type="text/css" href="https://cdn.datatables.net/1.10.20/css/jquery.dataTables.css">
    <script type="text/javascript" charset="utf8" src="https://cdn.datatables.net/1.10.20/js/jquery.dataTables.js"></script>

    <!-- http://getbootstrap.com/docs/4.1/content/typography/ -->
    <h1 class="mb-3">my Sheet</h1>

    <!-- http://getbootstrap.com/docs/4.1/components/tables/ -->
    <table id="myTable" class="table">
        <thead>
            <tr>
                <th scope="col">Name</th>
                <th scope="col">House</th>
                <th scope="col">Position</th>
            </tr>
        </thead>

        <tbody>
            {% for data in slist %}
                <tr>
                    <td>{{ data["name"]}}</td>
                    <td>{{data["house"]}}</td>
                    <td>{{data["option"] }}</td>
                </tr>
            {% endfor %}
        </tbody>
    </table>

    <!-- Initialising DataTables -->
    <script>
        $('#myTable').DataTable();
    </script>

{% endblock %}

<!--
from staff: Initialising Datables
$('table')['DataTable']({'info':![],'ordering':!![],'paging':![],'searching':![]});
 -- >
```

---
