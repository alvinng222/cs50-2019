Learning HTML
=============
This is extract from Pset5.

- [index.html](#indexhtml)

- [i_style.html](#i_stylehtml)

- [i_css.html](#i_csshtml)

- [i_boot.html](#i_boothtml)

- [i_jjs.html](#i_jjshtml)

- [i_dev.html](#i_devhtml)

---
## index.html
Home page
``` html
<!DOCTYPE html>
     <!-- You can immediately start a server to view the site by typing http-server -->
<html lang="en">
    <head>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
        <link href="styles.css" rel="stylesheet">
        <title>Learning HTML</title>
    </head>
    <body>
        <div class="container">
            <header>
                <h1>Learning HTML</h1>
            </header>

            <main>
                This web pages is my summary of learning html from CS50.

                <p>Contain at least four different .html pages. <br>
                Use at least ten (10) distinct HTML tags besides html, head, body.</p>

                <ul>
                    <li>This  <a href="index.html">home</a> page</li>
                    <li><a href="i_style.html">Learning style</a></li>
                    <li><a href="i_css.html">Link and CSS</a></li>
                    <li> Page on <a href="i_dev.html">Chrome Development tools</a></li>
                    <li> My note on <a href="i_boot.html">Bootstrap</a></li>
                    <li> My note on <a href="i_jjs.html">JavaScript</a></li>
                    <li> Example on <a href="dataTable.html">DataTables.net</a></li>
                </ul>
            </main>

            <footer>
            </footer>
        </div>
    </body>
</html>
```


---
## i_style.html
Style

#### description	symbol
  * **bold** < b >
  * *italic* < i >
  * **strong** < strong >
  * table, see exmaple above < table >
  * break < br >
  * quote < q >
  * h3
  * < h3 >
  * horizontal rule < hr >
  * ordered list < ol >
  * list < li >
  * image, see example below < img >


---
## i_css.html
CSS
``` html
<!-- You can immediately start a server to view the site by typing http-server -->
<!DOCTYPE html>
<!---
CSS stands for Cascading Style Sheets.
CSS describes how HTML elements are to be displayed on screen, paper, or in other media.
-->

<html lang="en">
    <head>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
        <link href="styles.css" rel="stylesheet">
        <style>
            /* comments on css  */
            h1 {
              color: white;
              /* text-shadow: 3px 2px red;*/
              text-shadow: 2px 2px 4px #000000;
            }
            small {
                  font-variant: small-caps;
            }
            .C::first-letter {
              color: #ff0000;
              font-size: xx-large;
            }

            input[type=text]:focus {
              width: 80%;
            }

            #bgdex {
              border: 10px dotted black;
              padding:35px;
              background: yellow;
              background-clip: padding-box;

              background-color: red; /* For browsers that do not support gradients */
  background-image: linear-gradient(to right, red , yellow); /* Standard syntax (must be last) */
            }
            .boxshadow {
              width: 300px;
              /* height: 100px;
              padding: 15px;*/
              background-color: yellow;
              box-shadow: 10px 10px 5px grey;
            }
            .button {
              background-color: #4CAF50; /* Green */
              border: none;
              color: white;
              padding: 15px 32px;
              text-align: center;
              text-decoration: none;
              display: inline-block;
              font-size: 16px;
              margin: 4px 2px;
              cursor: pointer;
            }

            .button2 {background-color: #008CBA;} /* Blue */
            .button3 {background-color: Coral;} /* Coral */
            .button4 {background-color: #e7e7e7; color: black;} /* Gray */
            .button5 {background-color: Indigo ;} /* Indigo  */

            .newspaper {
              /* Old Chrome, Safari, Opera */
              -webkit-column-count: 3;
              -webkit-column-width: 100px;

              /* Old Firefox */
              -moz-column-count: 3;
              -moz-column-width: 100px;

              /* Statndard syntax */
              column-count: 3;
              column-width: 100px;
            }

        </style>
            <!-- comments on html -->
        <title>Learning HTML - css</title>
    </head>
    <body>
        <header>
            This is header:
            <h1 class="boxshadow"><a href="index.html">Learning HTML</a></h1>
        </header>

        <main>
            <div class="newspaper">
            A CSS rule-set consists of a selector and a declaration block:<br>

            CSS selector<br>

            The selector points to the HTML element you want to style.<br>

            The declaration block contains one or more declarations separated by semicolons.<br>

            Each declaration includes a CSS property name and a value, separated by a colon.<br>

            A CSS declaration always ends with a semicolon, and declaration blocks are surrounded by curly braces.<br>
            </div>
            <br>
            <p>This is 'main'. </p>
            <small>This web page is my summary of learning html from CS50,<br>
            css. External file: i_css.css </small>

            <!-- class, id, span, div -->
<ul>
    <li>span - this is an inline span,
                <span style="border: 1px solid black"> Hello World</span> inside paragaph.</li>

            <h3 id="myID">id - using style #myID</h3>

            <div class="myClass">
                class - using style .myClass <br>
                all HTML elements with the same class attribute will get the same style.
            </div>

            <div style="border: 1px solid black">The DIV element is a block element.</div>

    <li>
        <form>
          <label for="fname">Form eg..</label>
          <input type="text" id="fname" name="fname">
        </form>
    </li>

    <li><a href="https://www.w3schools.com/colors/colors_names.asp">HTML Color Names </a></li>
    <li><button class="button">Green</button>
        <button class="button button2">Blue</button>
        <button>Default Button</button>
        <a href="#" class="button button3">Link Button</a>
        <button class="button button4">Button</button>
        <input type="button" class="button button5" value="Input Button"></li>

    <li>A pseudo-class is used to define a special state of an element.</li>
    <li class="C">You can use the ::first-letter pseudo-element to add a special effect to the first character of a text!</li>
    <li>The Flexible Box Layout Module, makes it easier to design flexible responsive layout structure without using float or positioning.
        Use flexbox to create a responsive website, containing a flexible navigation bar and flexible content:<br>
        .flex-container {
          display: flex;
          flex-flow: row wrap;
          justify-content: space-around;
          background-color: DodgerBlue;
        }
        .side {
          flex: 30%;
        }
        </li>
</ul>
        </main>

        <footer>
            <div id="bgdex">
                background-clip: padding-box <br>
                This is 'footer'.
            </div>
        </footer>
    </body>
</html>
```
  * Note of mystyles.css: Do not add a space between the property value and the unit (such as margin-left: 20 px;_). The correct way is: margin-left: 20px;
  * The CSS Box Model. All HTML elements can be considered as boxes. In CSS, the term "box model" is used when talking about design and layout.
  * The CSS box model is essentially a box that wraps around every HTML element. It consists of: margins, borders, padding, and the actual content. T
  * Use the "vw" unit when sizing the text. 10vw will set the size to 10% of the viewport width.
  * Using inline-block to Create Navigation Links: https://www.w3schools.com/css/css_inline-block.asp
  * The ::before pseudo-element can be used to insert some content before the content of an element
  * Horizontal Navigation Bar. There are two ways to create a horizontal navigation bar. Using inline or floating list items.
  * CSS [attribute] Selector. The [attribute] selector is used to select elements with a specified attribute.
  * A class selector beats any number of element selectors - a class selector such as .intro beats h1, p, div, etc.
  * The syntax of the var() function is as follows: var(custom-name, value)
  * Without the CSS box-sizing Property. By default, the width and height of an element is calculated like this:
```
    width + padding + border = actual width of an element
    height + padding + border = actual height of an element 
```
  * CSS2 Introduced Media Types. The @media rule, introduced in CSS2, made it possible to define different style rules for different media types. @media not|only mediatype and (expressions) { CSS-Code; }


---
## i_boot.html
BootStrap
``` html
<!DOCTYPE html>

<html lang="en">
    <head>
    <!-- Required meta tags -->
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

        <!-- Bootstrap CSS -->
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
        integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T"
        crossorigin="anonymous">

        <title>Learning HTML - Bootstrap</title>
    </head>
    <body>
        <div class="container">
            <header>
                <h1><a href="index.html">Learning HTML</a> - Bootstrap</h1>
            </header>
            <main>
                <p>This page is my note of learning bootstrap for CS50 Pset7<br>
                    some styles.<p>
            <div class="container">
                <p>The dl element indicates a description list:</p>
                <dl>
                    <dt>container classes</dt>
                    <!-- https://www.w3schools.com/bootstrap4/default.asp -->
                    <dd>There are two container classes to choose from:<br>
                        The .container class provides a responsive fixed width container<br>
                        The .container-fluid class provides a full width container, spanning the entire width of the viewport</dd>

                    <dt>Bootstrap grid system</dt>
                    <dd>Bootstrap4's grid system is built with flexbox and allows up to 12 columns across the page.<br>
                        The Bootstrap 4 grid system has five classes: .col-; .col-sm-; .col-md-; .col-lg-; .col-xl-<bt>
                        Bootstrap 4 uses a default font-size of 16px, and its line-height is 1.5.
                        The default font-family is "Helvetica Neue", Helvetica, Arial, sans-serif.</dd>


                    <dt> .pre-scrollable class</dt>
                        <dd>the pre element gets a max-height of 340px and provides a y-axis scrollbar:
                        <pre class="pre-scrollable">Text in a pre element
                        is displayed in a fixed-width
                        font, and it preserves
                        both      spaces and
                        line breaks.</pre></dd>

                    <dt>Colors</dt>
                        <dd>
                        The classes for text colors are: .text-muted, .text-primary, .text-success, .text-info, .text-warning, .text-danger, .text-secondary, .text-white, .text-dark, .text-body (default body color/often black) and .text-light:<br>
                        Contextual Link Colors. Hover over the links.
                        <a href="#" class="text-muted">Muted link.</a>
                        <a href="#" class="text-primary">Primary link.</a>
                        <a href="#" class="text-success">Success link.</a>
                        <a href="#" class="text-info">Info link.</a>
                        <a href="#" class="text-warning">Warning link.</a>
                        <a href="#" class="text-danger">Danger link.</a>
                        <a href="#" class="text-secondary">Secondary link.</a>
                        <a href="#" class="text-dark">Dark grey link.</a>
                        <a href="#" class="text-body">Body/black link.</a>
                        <a href="#" class="text-light">Light grey link.</a></dd>
                 </dl>

            </div>
            <ul class="list-group">
                <li class="list-group-item list-group-item-success">A basic Bootstrap 4 table has a light padding and horizontal dividers.<br>
                The .table class adds basic styling to a table<br>
                The .table-striped class adds zebra-stripes to a table</li>

                <li class="list-group-item">
                Alerts are created with the .alert class, followed by one of the contextual classes .alert-success, .alert-info, .alert-warning, .alert-danger, .alert-primary, .alert-secondary, .alert-light or .alert-dark<br>
                <div class="alert alert-success">
                <strong>Success!</strong> This alert box could indicate a successful or positive action.
                </div>
                </li>
                <li class="list-group-item">
                    Button Styles<br>
                    <button type="button" class="btn">Basic</button>
                    <button type="button" class="btn btn-primary">Primary</button>
                    <button type="button" class="btn btn-secondary">Secondary</button>
                    <button type="button" class="btn btn-success">Success</button>
                    <button type="button" class="btn btn-info">Info</button>
                    <button type="button" class="btn btn-warning">Warning</button>
                    <button type="button" class="btn btn-danger">Danger</button>
                    <button type="button" class="btn btn-dark">Dark</button>
                    <button type="button" class="btn btn-light">Light</button>
                    <button type="button" class="btn btn-link">Link</button>
                </li>
                <li class="list-group-item">
                    The button classes can be used on < a >, < button >, or < input > elements<br>
                    <a href="#" class="btn btn-info" role="button">Link Button</a>
                    <button type="button" class="btn btn-info">Button</button>
                    <input type="button" class="btn btn-info" value="Input Button">
                    <input type="submit" class="btn btn-info" value="Submit Button">
                </li>

                <li class="list-group-item">
                    A standard navigation bar is created with the .navbar class, followed by a responsive collapsing class: .navbar-expand-xl|lg|md|sm (stacks the navbar vertically on extra large, large, medium or small screens)<br>
                    <nav class="navbar navbar-expand-sm bg-light">
                    <!-- Links -->
                    <ul class="navbar-nav">
                    <li class="nav-item">
                      <a class="nav-link" href="#">Link 1</a>
                    </li>
                    <li class="nav-item">
                      <a class="nav-link" href="#">Link 2</a>
                    </li>
                    <li class="nav-item">
                      <a class="nav-link" href="#">Link 3</a>
                    </li>
                    </ul>
                    </nav>
                </li>
                <li class="list-group-item">
                    <b>Form controls</b> automatically receive some global styling with Bootstrap:<br>
                    All textual < input >, < textarea >, and < select > elements with class .form-control have a width of 100%. <br>
                    Bootstrap provides two types of form layouts:<br>
                    Stacked (full-width) form<br>
                    Inline form<br>
                </li>

                <li class="list-group-item">
                    Bootstrap Input <br>
                    Bootstrap supports all the HTML5 input types: text, password, datetime, datetime-local, date, month, time, week, number, email, url, search, tel, and color.<br>
                    <div class="form-group">
                      <label for="usr">Name:</label>
                      <input type="text" class="form-control" id="usr">
                    </div>
                    <div class="form-check">
                        <label class="form-check-label">
                        <input type="radio" class="form-check-input" name="optradio">Option 1
                        </label>
                    </div>
                    <div class="form-check">
                        <label class="form-check-label">
                        <input type="radio" class="form-check-input" name="optradio">Option 2
                        </label>
                    </div>
                        <div class="form-group">
                            <input type="file" class="form-control-file border" name="file">
                        </div>
                        <button type="submit" class="btn btn-primary">Submit</button>
                </li>

                <li class="list-group-item">
                    The <b>.input-group class</b> is a container to enhance an input by adding an icon, text or a button in front or behind the input field as a "help text".<br>
                    Use .input-group-prepend to add the help text in front of the input, and .input-group-append to add it behind the input.<br>
                    At last, add the .input-group-text class to style the specified help text.<br>
                    Put labels outside of the input group, and remember that the value of the for attribute should match the id of the input.<br>
                    <mark>Click on the label and it will bring focus to the input</mark><br>
                    <form>
                      <div class="input-group mb-3">
                        <div class="input-group-prepend">
                          <span class="input-group-text">@</span>
                        </div>
                        <input type="text" class="form-control" placeholder="Username">
                      </div>

                      <label for="demo">Write your email here:</label>
                        <div class="input-group mb-3">
                          <input type="text" class="form-control" placeholder="Email" id="demo" name="email">
                          <div class="input-group-append">
                            <span class="input-group-text">@example.com</span>
                          </div>
                        </div>
                    </form>
                    We use the .mb-3 utility class to ensure that the input group gets a proper margin bottom.
                </li>
                <li>
                    <div class="form-group">
    <label for="exampleFormControlFile1">Example file input</label>
    <input type="file" class="form-control-file" id="exampleFormControlFile1">
  </div>
                </li>
                <li><pre>
    Notation
    Spacing utilities that apply to all breakpoints, from xs to xl, have no breakpoint abbreviation in them. This is because those classes are applied from min-width: 0 and up, and thus are not bound by a media query. The remaining breakpoints, however, do include a breakpoint abbreviation.

    The classes are named using the format {property}{sides}-{size} for xs and {property}{sides}-{breakpoint}-{size} for sm, md, lg, and xl.

    Where property is one of:

    m - for classes that set margin
    p - for classes that set padding
    Where sides is one of:

    t - for classes that set margin-top or padding-top
    b - for classes that set margin-bottom or padding-bottom
    l - for classes that set margin-left or padding-left
    r - for classes that set margin-right or padding-right
    x - for classes that set both *-left and *-right
    y - for classes that set both *-top and *-bottom
    blank - for classes that set a margin or padding on all 4 sides of the element </pre>
                </li>
            </ul>
            </main>

            <footer>
                check out more on <a href="https://getbootstrap.com/docs/4.3/components/alerts/">
                    https://getbootstrap.com/docs/4.3/components/alerts/</a>
            </footer>

        </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>

    </body>
</html>

<!--

        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
        <link href="styles.css" rel="stylesheet">
-->
```

---
## i_jjs.html
#### JavaScript

JavaScript is the programming language of HTML and the Web.

* JavaScript Can Change HTML Content One of many JavaScript HTML methods is `getElementById()`.
Example:
```
< p id="demo">JavaScript can change HTML content.< /p>
< button type="button" onclick='document.getElementById("demo").innerHTML = "Hello JavaScript!"'>Click Me!< /button>
document.getElementById("demo").style.fontSize = "35px";
```
* A JavaScript `function` is a block of JavaScript code, that can be executed when "called" for.
Example:
```
    function myFunction() {
        document.getElementById("demo").innerHTML = "Paragraph changed.";
        }
        < p id="demo">A Paragraph< /p>
        < button type="button" onclick="myFunction()">Try it< /button>
```
* JavaScript can "display" data in different ways:
    * Writing into an HTML element, using `innerHTML`.
    * Writing into the HTML output using `document.write()`.
    * Writing into an alert box, using `window.alert()`.
    * Writing into the browser console, using `console.log()`.

* JavaScript Programs. In HTML, JavaScript programs are executed by the web browser.
    * Example: `a = 5; b = 6; c = a + b; var x = 10; x += 5;`
    * JavaScript syntax is the set of rules, how JavaScript programs are constructed
    * JavaScript Comments: `//` or `/* */`
    * JavaScript Comparison & Logical Operators: `== === != !== > < >= <= ? && || !`
    * JavaScript Type Operators: `typeof instanceof`
    * JavaScript Bitwise Operators: `& | ~ ^ << >> >>>`

* JavaScript Data Types
    * JavaScript Strings `var carName1 = "Volvo XC60";`
    * JavaScript Arrays `var cars = ["Saab", "Volvo", "BMW"];`
    * JavaScript Objects `var person = {firstName:"John", lastName:"Doe", age:50, eyeColor:"blue"};`
    * The typeof Operator
        * `typeof {name:'John', age:34}` // Returns "object"
        * `typeof [1,2,3,4]`           // Returns "object" (not "array", see note below)
        * `typeof null`                 // Returns "object"
        * `typeof function myFunc(){}`   // Returns "function"

* JavaScript Functions
  ```
      function myFunction(p1, p2) {
      return p1 * p2; // The function returns the product of p1 and p2
      }
  ```
  * The () Operator Invokes the Function
  * Accessing a function without () will return the function definition instead of the function result

* **JavaScript Objects**
Example
  ```
  var person = {
        firstName: "John",
        lastName : "Doe",
        id       : 5566,
        fullName : function() {
            return this.firstName + " " + this.lastName;
        }
    };
    ```
    * You access an object method with the following syntax: `objectName.methodName()`
    
* Common HTML Events
  * `onchange` An HTML element has been changed
  * `onclick` The user clicks an HTML element
  * `onmouseover` The user moves the mouse over an HTML element
  * `onmouseout` The user moves the mouse away from an HTML element
  * `onkeydown` The user pushes a keyboard key
  * `onload` The browser has finished loading the page
  ```
      < button onclick="displayDate()">The time is?
      < script>
      function displayDate() {
        document.getElementById("demo").innerHTML = Date();
      }
      < /script>
      < p id="demo">
  ```

* JS String
    * var txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    * var sln = txt.length;
  * Objects cannot be compared:
  * The search() method searches a string for a specified value and returns the position of the match:
     * var str = "Please locate where 'locate' occurs!";
     * var pos = str.search("locate");

  * There are 3 methods for extracting a part of a string:
      * slice(start, end)
      * substring(start, end)
      * substr(start, length)

  * A string is converted to upper case with `toUpperCase():`

  * A string is converted to lower case with `toLowerCase():`

  * The `charAt()` method returns the character at a specified index (position) in a string

  * The `charCodeAt()` method returns the unicode of the character at a specified index in a string:

  * A string can be converted to an array with the `split()` method:

* JS Number
  * You can use the global JavaScript function isNaN() to find out if a value is a number

  * Infinity (or -Infinity) is the value JavaScript will return if you calculate a number outside the largest possible number.

  * Number() can be used to convert JavaScript variables to numbers
  * parseInt() parses a string and returns a whole number. Spaces are allowed. Only the first number is returned
  * parseeFloat() parses a string and returns a number. Spaces are allowed. Only the first number is returned:

  * JavaScript NaN - Not a Number

  * Complete JavaScript Number Reference: https://www.w3schools.com/jsref/jsref_obj_number.asp

* JS Array
```
var array_name = [item1, item2, ...];

var cars = ["Saab", "Volvo", "BMW"];
document.getElementById("demo").innerHTML = cars[0];

The length property of an array returns the length of an array (the number of array elements).

When to Use Arrays. When to use Objects.
JavaScript does not support associative arrays.
You should use objects when you want the element names to be strings (text).
You should use arrays when you want the element names to be numbers.

The JavaScript method toString() converts an array to a string of (comma separated) array values.

The pop() method removes the last element from an array

The push() method adds a new element to an array (at the end)

The shift() method removes the first array element and "shifts" all other elements to a lower index.

The unshift() method adds a new element to an array (at the beginning), and "unshifts" older elements:

The splice() method can be used to add new items to an array:
var fruits = ["Banana", "Orange", "Apple", "Mango"];
fruits.splice(2, 0, "Lemon", "Kiwi");

The slice() method slices out a piece of an array into a new array.

Complete Array Reference: https://www.w3schools.com/jsref/jsref_obj_array.asp

Sorting an Array
The sort() method sorts an array alphabetically

The Compare Function. The purpose of the compare function is to define an alternative sort order.
function(a, b){return a - b}

JavaScript Array Iteration Methods
The forEach() method calls a function (a callback function) once for each array element.

The map() method creates a new array by performing a function on each array element.

The filter() method creates a new array with array elements that passes a test.

The reduce() method runs a function on each array element to produce (reduce it to) a single value.

The every() method check if all array values pass a test.

The some() method check if some array values pass a test.

The indexOf() method searches an array for an element value and returns its position.

The find() method returns the value of the first array element that passes a test function.
```

* The Boolean() Function
  * You can use the Boolean() function to find out if an expression (or a variable) is true

  * Everything Without a "Value" is False, The Boolean value of 0 (zero) is fals

* JavaScript Comparison and Logical Operators
  ```
    function myFunction() {
      var age, voteable;
      age = Number(document.getElementById("age").value);
      if (isNaN(age)) {
        voteable = "Input is not a number";
      } else {
        voteable = (age < 18) ? "Too young" : "Old enough";
      }
      document.getElementById("demo").innerHTML = voteable;
    }
  ```

* Conditional Statements
  * Use **if** to specify a block of code to be executed, if a specified condition is true
  * Use **else** to specify a block of code to be executed, if the same condition is false
  * Use **else if** to specify a new condition to test, if the first condition is false
  * Use **switch** to specify many alternative blocks of code to be executed
  
* The JavaScript Switch Statement
  ```
    switch(expression) {
      case x:
        // code block
        break;
      case y:
        // code block
        break;
      default:
        // code block
    }
  ```
  
* JavaScript For Loop, While Loop
  * for - loops through a block of code a number of times
  * for/in - loops through the properties of an object
  * for/of - loops through the values of an iterable object
  * while - loops through a block of code while a specified condition is true
  * do/while - also loops through a block of code while a specified condition is true
  ```
    for (statement 1; statement 2; statement 3) {
      // code block to be executed
    }

    while (condition) {
      // code block to be executed
    }
  ```

* JavaScript Break and Continue
  * The break statement "jumps out" of a loop.
  * The continue statement "jumps over" one iteration in the loop.

- JavaScript Data Types
    - In JavaScript there are 5 different data types that can contain values:
      - string
      - number
      - boolean
      - object
      - function

    - There are 6 types of objects:
      - Object
      - Date
      - Array
      - String
      - Number
      - Boolean

    - And 2 data types that cannot contain values:
      - null
      - undefined

    - You can use the **typeof** operator to find the data type of a JavaScript variable.

    - The **constructor** property returns the constructor function for all JavaScript variables.
    
- JSON
    - JSON: JavaScript Object Notation.
    - JSON is a syntax for storing and exchanging data.
    - JSON is text, written with JavaScript object notation.

    - The JSON format is almost identical to JavaScript objects.
    - In JSON, keys must be strings, written with double quotes:
        ```{ "name":"John" } ```

    - Values in JSON can be objects.
        ```
        {
            "employee":{ "name":"John", "age":30, "city":"New York" }
        }

    - JSON.parse()
      - Use the JavaScript function JSON.parse() to convert text into a JavaScript object:
        ```
        var obj = JSON.parse('{ "name":"John", "age":30, "city":"New York"}');

    - JSON.stringify()
      - Convert a JavaScript object into a string with JSON.stringify().
        ```
        var obj = { name: "John", age: 30, city: "New York" };
        var myJSON = JSON.stringify(obj);
        document.getElementById("demo").innerHTML = myJSON;


---
## i_dev.html
``` html
<!DOCTYPE html>

<html lang="en">
    <head>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" rel="stylesheet">
        <link href="styles.css" rel="stylesheet">
        <title>Learning HTML - tools</title>
    </head>
    <body>
        <div class="container">
            <header>
                <h1><a href="index.html">Learning HTML</a></h1>
            </header>
            <main>
                This web page is my summary of learning html from CS50,<br>
                Development tools.
                <p>link to <a href="https://developers.google.com/web/tools/chrome-devtools/">
                Google Development Tool</a> .</p>

                <p>Assess by Chrome Menu in the browser window, select View, Deveoper, and choose Developer Tools. Or <br>
                use the keyboard shortcut Command Option I (on Mac).</p>

                <p>Check if html is well form and valid:
                <a href="https://validator.w3.org/#validate_by_input"> W3School validator</a>.</p>
            </main>
            <footer>
            </footer>
        </div>
    </body>
</html>

<!-- learn vim
Vim [file_name.c] , ref to vim101: a beginner guide to Vim, ref: vimtutor
:q
:wq - write
:q! - just quit

some Cursor movement
h or left arrow - move left
j or down arrow  - move down
k or up arrow - move up
l or right arrow - move right
w - jump by start of words (punctuation considered words)
b - jump backward by words (punctuation considered words), eg [5b] go back 5 words

Search/Replace
/pattern - search for pattern
n - repeat search in same direction
N - repeat search in opposite direction

Insert Mode - Inserting/Appending text
i - start insert mode at cursor
Esc - exit insert mode

Exiting
:w - write (save) the file, but don't exit
:wq - write (save) and quit
:q - quit (fails if anything has changed)
:q! - quit and throw away changes

copy & paste
y - to copy few lines. mark line ma to y'a to copy, than p to place
c or C : to change and insert
d or D - delete the single line
p or P - 'put' paste it back after or before the cursor
x or X - delete character

ctrl-n - to go down screen
ctrl-u - to go up screen

https://www.fprintf.net/vimCheatSheet.html
-->
```


--- 
## [TOP](#learning-html)
