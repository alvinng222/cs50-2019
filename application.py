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